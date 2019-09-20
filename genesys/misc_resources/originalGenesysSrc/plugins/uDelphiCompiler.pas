unit uDelphiCompiler;


{*******************************************************************************
                                                                               *
                     SISTEMA DE SIMULAÇÃO DISCRETA                             *
                           COMPILADOR DELPHI                                   *
                                                                               *
                                                                               *
                                                                               *
                                                                               *
 Autor: Thiago Augusto Flessak, 10/2003                                        *
                                                                               *
                                                                               *
*******************************************************************************}


interface

uses
  Windows, Classes, Dialogs, RegExpr, Registry, SysUtils;

type
  // Define os tipos de mensagens
  TCompilerMsgInfos = set of (cmError, cmWarning, cmHint, cmFatal);

  TDelphiCompiler = class(TObject)
  public
    constructor Create;
    destructor Destroy; override;

    function Execute(FileName: string) : boolean;
  private
    aCompParams,
    aCompSwitches,
    aOutPutDir: string;
    aMessages: TStringList;
    aMessagesInfo: TCompilerMsgInfos;
    bHasError,
    bHasWarning: boolean;
    aCompDelphi: string;
    aFirstError: integer;

    function GetConsoleOutPut(const Command: string): boolean;
  public
    property CompParams: string               read aCompParams   write aCompParams;
    property CompSwitches: string             read aCompSwitches write aCompSwitches;
    property OutPutDir: string                read aOutPutDir    write aOutPutDir;
    property Messages: TStringList            read aMessages;
    property MessagesInfo: TCompilerMsgInfos  read aMessagesInfo;
    property FirstError: integer              read aFirstError;
  end;

implementation

{ TDelphiCompiler }

constructor TDelphiCompiler.Create;
var
   Registry: TRegistry;
   i: byte;
begin
   // Inicializa os parametros de compilacao
   aCompParams := '-H -W -Q -U'+ExtractFilePath(ExtractShortPathName(ParamStr(0)));
   aCompSwitches := '-$O+ -$A+ -$V+ -$X+ -$P+ -$I+';
   //aOutPutDir := '.';

   aMessages := TStringList.Create;
   bHasError := False;
   bHasWarning := False;

   aFirstError := -1;

   // Procura no registro o diretorio do Delphi
   Registry := TRegistry.Create;
   try
      Registry.RootKey := HKEY_LOCAL_MACHINE;

      for i:=5 to 7 do begin
         if Registry.KeyExists('Software\Borland\Delphi\'+IntToStr(i)+'.0') then begin
            Registry.OpenKey('Software\Borland\Delphi\'+IntToStr(i)+'.0', False);
            aCompDelphi := ExtractShortPathName(Registry.ReadString('RootDir')+'\bin\dcc32.exe');

            if FileExists(aCompDelphi) then
               break
            else
               Registry.CloseKey;
         end;
      end;
   finally
      Registry.Free;
   end;
end;

destructor TDelphiCompiler.Destroy;
begin
     aMessages.Free;

     inherited Destroy;
end;

function TDelphiCompiler.Execute(FileName: string) : boolean;
var
   i,j: integer;
   r: TRegExpr;
   VerInfo: TOsversionInfo;
   CmdShell: string;
begin
   aMessages.Clear;
   bHasError := False;
   bHasWarning := False;
   aFirstError := -1;
   aMessagesInfo := [];
   aOutPutDir := ExtractFilePath(FileName);
   if aOutPutDir = '' then
      aOutPutDir := '.';

   // Verifica a versao do Windows para saber qual Shell utilizar
   VerInfo.dwOSVersionInfoSize := SizeOf(VerInfo);
   GetVersionEx(VerInfo);
   case VerInfo.dwPlatformId of
     VER_PLATFORM_WIN32_WINDOWS: CmdShell := 'command';
     VER_PLATFORM_WIN32_NT:      CmdShell := 'cmd';
   else
     Result := False;
     Exit;
   end;

   Result := GetConsoleOutPut(CmdShell+' /c '+aCompDelphi+' '+aCompParams+' -E'+ExtractShortPathName(aOutPutDir)+' '+ExtractShortPathName(ExtractFilePath(FileName))+ExtractFileName(FileName)+' '+aCompSwitches);

   if not Result then
      Exit;

   // Retira o cabecalho
   for i:=1 to 3 do
      aMessages.Delete(0);

   with TStringList.Create do begin
      r := TRegExpr.Create;
      j := -1;
      for i:=0 to aMessages.Count-1 do begin
         // Retira as linhas em branco
         if aMessages.Strings[i] = '' then
            continue;

         // Verifica se eh uma mensagem de erro
         //r.Expression := '^[_a-zA-Z\d\-\.]+\([\d]+\) (Error|Warning|Hint|Fatal):';
         r.Expression := '^(.*?)\([\d]+\) (Error|Warning|Hint|Fatal):';
         if r.Exec(aMessages.Strings[i]) then begin
            inc(j);

            if not (cmError in aMessagesInfo) and (r.Match[2] = 'Error') then begin
               Include(aMessagesInfo, cmError);
               aFirstError := j;
            end;

            if r.Match[2] = 'Warning' then
              Include(aMessagesInfo, cmWarning);

            if r.Match[2] = 'Hint' then
               Include(aMessagesInfo, cmHint);

            if r.Match[2] = 'Fatal' then
               Include(aMessagesInfo, cmFatal);

            Add(aMessages.Strings[i]);
         end;
      end;

      r.Free;
      aMessages.Text := Text;
   end;
end;

function TDelphiCompiler.GetConsoleOutPut(const Command: string): Boolean;
var
   StartupInfo: TStartupInfo;
   ProcessInfo: TProcessInformation;
   SecurityAttr: TSecurityAttributes;
   PipeOutputRead: THandle;
   PipeOutputWrite: THandle;
   PipeErrorsRead: THandle;
   PipeErrorsWrite: THandle;
   Buffer: array [0..255] of Char;
   NumberOfBytesRead: DWORD;
   Stream: TMemoryStream;
begin
   //Inicializa ProcessInfo
   FillChar(ProcessInfo, SizeOf(TProcessInformation), 0);

   //Inicializa SecurityAttr
   FillChar(SecurityAttr, SizeOf(TSecurityAttributes), 0);
   SecurityAttr.nLength := SizeOf(SecurityAttr);
   SecurityAttr.bInheritHandle := true;
   SecurityAttr.lpSecurityDescriptor := nil;

   //Cria Pipes
   CreatePipe(PipeOutputRead, PipeOutputWrite, @SecurityAttr, 0);

   //Inicializa StartupInfo
   FillChar(StartupInfo, SizeOf(TStartupInfo), 0);
   with StartupInfo do begin
      cb := SizeOf(StartupInfo);
      hStdInput := 0;
      hStdOutput := PipeOutputWrite;
      wShowWindow := SW_HIDE;
      dwFlags := STARTF_USESHOWWINDOW or STARTF_USESTDHANDLES;
   end;

   if CreateProcess(nil, PChar(command), nil, nil, true, 0, nil, nil, StartupInfo, ProcessInfo) then begin
      SetPriorityClass(ProcessInfo.hProcess, Idle_Priority_Class);
      WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
      result := true;

      CloseHandle(PipeOutputWrite);

      Stream := TMemoryStream.Create;
      try
         PeekNamedPipe(PipeOutputRead, nil, 0, nil, @NumberOfBytesRead, nil);
         if NumberOfBytesRead > 0 then begin
            while true do begin
               ReadFile(PipeOutputRead, Buffer, 255, NumberOfBytesRead, nil);
               Stream.Write(Buffer, NumberOfBytesRead);
               if (NumberOfBytesRead < 255) then break;
            end;
         end;
         Stream.Position := 0;
         aMessages.LoadFromStream(Stream);
      finally
         Stream.Free;
      end;
      CloseHandle(PipeOutputRead);

      WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
      CloseHandle(ProcessInfo.hProcess);
      end
   else begin
      result := false;
      CloseHandle(PipeOutputRead);
      CloseHandle(PipeOutputWrite);
      CloseHandle(PipeErrorsRead);
      CloseHandle(PipeErrorsWrite);
   end;
end;

end.
