unit uStub;

interface

uses Windows, SysUtils, Classes, Graphics, Controls, Forms, Dialogs, StdCtrls, Winsock, Sockets, Grids;

   type

    TNetworkHandler = class(TObject)
    private
       aErrorCode: DWORD;
       aErrorMsg: string;
       function _GetNameStruct(lpnr: PNETRESOURCE): string;
       function _EnumerateMachines(lpnr:PNetResource; var machines: TStringList): boolean;
    public
       constructor Create;
       function GetNetMachineNames: TStringList;
       function GetNetMachineIPs: TStringList;
       function GetMachineIP(machineName:string): string;
       function GetLocalMachineName:string;
       function GetLocalMachineIP:string;
       function GetLocalMachineUser:string;
       property ErrorMessage:string read aErrorMsg;
    end;

     TTCPSocket = class(TObject)
     private
        aReceiveMessageFile: string;
        aMessageBuffer: TStringList;
        aHasReceived: boolean;
        aTCPClient: TTCPClient;
        aTCPServer: TTCPServer;
        aNetSolver: TNetworkHandler;
        procedure _TCPServerAccept(Sender: TObject; ClientSocket: TCustomIpClient);
        function  _GetLocalClientPort: string;
        function  _GetLocalHost: string;
        function  _GetLocalServerPort: string;
        procedure _SetLocalServerPort(const Value: string);
     public
        constructor Create(sender: TComponent; serverPort: string);
        function Send(hostname, portnumber, filename:string): boolean;
        function Receive(filename:string): boolean;
        property HasReceived:boolean       read aHasReceived;
        property LocalHost:string          read _GetLocalHost;
        property LocalClientPort:string    read _GetLocalClientPort;
        property LocalServerPort:string    read _GetLocalServerPort write _SetLocalServerPort;
        property MessageBuffer:TStringList read aMessageBuffer;
        property NetSolver:TNetworkHandler read aNetSolver;
     published
     end;

    TClientDataThread = class(TThread)
    private
    public
      aListBuffer: TStringList;
      aFilename: string;
      procedure synchAddDataToControl;
      constructor Create(CreateSuspended: Boolean);
      procedure Execute; override;
      procedure Terminate;
      property  Filename:string read aFilename write aFilename;
    end;

{------------------------------------------------------------------------------}
implementation
{------------------------------------------------------------------------------}

{ TNetworkHandler }

function TNetworkHandler._GetNameStruct(lpnr: PNETRESOURCE): string;
var p : PChar;
begin
    p := lpnr^.lpRemoteName;
    if (p[0] = '\') and (p[1] = '\') then
        p := p + 2;
    result := string(p);
end;

constructor TNetworkHandler.Create;
begin
   aErrorCode := NO_ERROR;
   aErrorMsg := '';
end;

function TNetworkHandler.GetMachineIP(machineName: string): string;
var wsdata: TWSAData;
    he    : PHostEnt;
    ss    : pchar;
    ip    : TInAddr;
begin
  aErrorMsg :='';
  WSAStartup(MakeWord(1, 1), wsdata);
  he := gethostbyname(pchar(machineName));
  if he <> nil then begin
     ip.S_addr := integer(pointer(he^. h_addr_list^)^);
     ss := inet_ntoa(ip);
     Result := string(ss);
  end;
  WSACleanup();
end;

function TNetworkHandler.GetLocalMachineIP: string;
begin
   result := GetMachineIP(GetLocalMachineName);
end;

function TNetworkHandler.GetLocalMachineName: string;
var i: cardinal;
    auxResult: string;
begin
   i := 255;
   SetLength(auxResult,i);
   GetComputerName(PChar(auxResult),i);
   SetLength(auxResult,(i));
   result := auxResult;
end;

function TNetworkHandler.GetLocalMachineUser: string;
var i: cardinal;
    auxResult: string;
begin
   i := 255;
   SetLength(auxResult,i);
   GetUserName(PChar(auxResult),i);
   SetLength(auxResult,(i));
   result := auxResult;
end;

function TNetworkHandler.GetNetMachineIPs: TStringList;
var auxResult: TStringList;
    i: integer;
begin
   aErrorMsg :='';
   auxResult := TStringList.Create;
   auxResult.Sorted := false;
   _EnumerateMachines(nil, auxResult);
   for i := 0 to auxResult.Count-1 do begin
      auxResult.Strings[i] := GetMachineIP(auxResult.Strings[i]);
   end;
   result := auxResult;
end;

function TNetworkHandler._EnumerateMachines(lpnr:PNetResource; var machines: TStringList): boolean;
var
    dwResult     : DWORD;
    dwResultEnum : DWORD;
    hEnum        : THandle;
    cbBuffer     : DWORD;             // 16K is a good size
    cEntries     : DWORD;             // enumerate all possible entries
    lpnrLocal    : PNETRESOURCE;      // pointer to enumerated structures
    PtrResource  : PNetResource;
    i            : DWORD;
begin
    cbBuffer := 16384;
    cEntries := DWORD(-1);
    if Application.Terminated then begin
        Result := FALSE;
        Exit;
    end;
    dwResult := WNetOpenEnum(RESOURCE_GLOBALNET,
                             RESOURCETYPE_ANY,
                             RESOURCEUSAGE_CONTAINER, // enumerate allresources
                             lpnr,                    // NULL first timethis function is called
                             hEnum);                  // handle to resource
    if dwResult <> NO_ERROR then begin
        aErrorCode := dwResult;
        aErrorMsg := 'WNetOpenEnum';
        Result := FALSE;
        Exit;
    end;
    repeat
        // Allocate memory for NETRESOURCE structures.
        GetMem(lpnrLocal, cbBuffer);
        dwResultEnum := WNetEnumResource(hEnum,       // resource handle
                                         cEntries,    // defined locally as0xFFFFFFFF
                                         lpnrLocal,   // LPNETRESOURCE
                                         cbBuffer);   // buffer size
        if dwResultEnum = NO_ERROR then begin
            for i := 0 to cEntries - 1 do begin
                PtrResource := PNETRESOURCE(PChar(lpnrLocal) + i *SizeOf(lpnrLocal^));
                if PtrResource^.dwDisplayType = RESOURCEDISPLAYTYPE_SERVER then
                    machines.Add(_GetNameStruct(PtrResource));
                Application.ProcessMessages;
                // If this NETRESOURCE is a container, call the function
                // recursively.
                if (RESOURCEUSAGE_CONTAINER = (PtrResource^.dwUsage and RESOURCEUSAGE_CONTAINER)) and
                   (PtrResource^.dwDisplayType <>RESOURCEDISPLAYTYPE_SERVER) then begin
                    if (not _EnumerateMachines(PtrResource, machines)) then begin
                        // TextOut(HandleDC, 10, 10, 'EnumerateFunc returned FALSE.', 29);
                    end;
                end;
            end;
        end
        else if dwResultEnum <> ERROR_NO_MORE_ITEMS then begin
            aErrorCode := dwResultEnum;
            aErrorMsg := 'WNetEnumResource';
            break;
        end;
    until dwResultEnum = ERROR_NO_MORE_ITEMS;
    FreeMem(lpnrLocal);
    dwResult := WNetCloseEnum(hEnum);
    if dwResult <> NO_ERROR then begin
        aErrorCode := dwResult;
        aErrorMsg := 'WNetCloseEnum';
        Result := FALSE;
        Exit;
    end;
    Result := TRUE;
end;

function TNetworkHandler.GetNetMachineNames: TStringList;
var auxResult: TStringList;
begin
   aErrorMsg :='';
   auxResult := TStringList.Create;
   auxResult.Sorted := false;
   _EnumerateMachines(nil, auxResult);
   result := auxResult;
end;

{ TClientDataThread }

constructor TClientDataThread.Create(CreateSuspended: Boolean);
begin
   inherited Create(CreateSuspended);
   FreeOnTerminate := true;
   aListBuffer := TStringList.Create;
   aListBuffer.Sorted := false;
end;

procedure TClientDataThread.Terminate;
begin
   aListBuffer.Free;
   inherited;
end;

procedure TClientDataThread.Execute;
begin
   Synchronize(synchAddDataToControl);
end;

procedure TClientDataThread.synchAddDataToControl;
var f: text;
    oneline: string;
    i: integer;
begin
   try
      AssignFile(f, aFilename);
      Rewrite(f);
      for i := 0 to aListBuffer.Count-1 do begin
         writeln(f, aListBuffer.Strings[i]);
      end;
      CloseFile(f);
   except
   end;
end;


{ TTCPSocket }

constructor TTCPSocket.Create(sender: TComponent; serverPort: string);
begin
   inherited Create;
   aReceiveMessageFile := '';
   aHasReceived := false;
   aMessageBuffer := TStringList.Create;
   aMessageBuffer.Sorted := false;
   aTCPClient := TTCPClient.Create(sender);
   aTCPServer := TTCPServer.Create(sender);
   aTCPServer.OnAccept := _TCPServerAccept;
   aNetSolver := TNetworkHandler.Create;
   aTCPServer.LocalHost := aNetSolver.GetLocalMachineName;
   aTCPServer.LocalPort := serverPort;
   aTCPClient.LocalHost := aTCPServer.LocalHost;
end;

procedure TTCPSocket._TCPServerAccept(Sender: TObject; ClientSocket: TCustomIpClient);
var s: string;
    DataThread: TClientDataThread;
begin
   DataThread:= TClientDataThread.Create(true);
   DataThread.aFilename := aReceiveMessageFile;
   s := ClientSocket.Receiveln;
   while s <> '' do begin
     DataThread.aListBuffer.Add(s);
     s := ClientSocket.Receiveln;
   end;
   DataThread.Resume;
end;


function TTCPSocket.Receive(filename: string): boolean;
begin
   aReceiveMessageFile := filename;
   aTCPServer.Active := true;
   result := true; //always?
end;


function TTCPSocket.Send(hostname, portnumber, filename: string): boolean;
var f: text;
    oneline: string;
    i: integer;
begin
   result := false;
   if FileExists(filename) then begin
      try
         aMessageBuffer.Clear;
         AssignFile(f, filename);
         Reset(f);
         while not EOF(f) do begin
            readln(f, oneline);
            if oneline <> '' then begin
               aMessageBuffer.Add(oneline);
            end;
         end;
         CloseFile(f);
         aTCPClient.Active := false;
         aTCPClient.RemoteHost := hostname;
         aTCPClient.RemotePort := portnumber;
         try
            if aTCPClient.Connect then begin
               for i := 0 to aMessageBuffer.Count - 1 do begin
                  aTCPClient.Sendln(aMessageBuffer.Strings[i]);
               end;
               result := true;
            end;
         finally
            aTCPClient.Disconnect;
         end;
      except
      end;
   end;
end;


function TTCPSocket._GetLocalClientPort: string;
begin
   result := aTCPClient.LocalPort;
end;

function TTCPSocket._GetLocalHost: string;
begin
   result := aTCPClient.LocalHost;
end;

function TTCPSocket._GetLocalServerPort: string;
begin
   result := aTCPServer.LocalPort;
end;

procedure TTCPSocket._SetLocalServerPort(const Value: string);
begin
   aTCPServer.LocalPort := value;
end;

end.
