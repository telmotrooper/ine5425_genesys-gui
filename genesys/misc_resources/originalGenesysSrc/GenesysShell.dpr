
program GenesysShell;
{$APPTYPE CONSOLE}

uses
  classes,
  SysUtils,
  stdCtrls,
  Forms,
  uStub,
  uDelphiCompiler,
  GenesysKernel;

type
    TAnyClass = class(TObject)
    private
    public
        constructor Create;
        //handlers for kernel events
        procedure BeginSim;
        procedure EndSim;
        procedure BeginRep;
        procedure EndRep;
        procedure OpenDoc;
        procedure SaveDoc;
        procedure CloseDoc;
        procedure EntMove;
        procedure NewEvent;
    end;

    TTrace = class(TObject)
    private
        aShellFileName,
        aKernelFileName,
        aSimulFileName,
        aReportFileName: string;
        procedure _SaveFile(fileName, texto:string);
    public
        constructor Create;
        procedure ScreenShow(texto:string);
        procedure ShellFileShow(texto:string);
        procedure KernelFileShow(texto:string);
        procedure SimulFileShow(texto:string);
        procedure ReportFileShow(texto:string);
    end;

    TShellManager = class(TObject)
    private
        aCommandLine: boolean;
        aCommandWords: TStringList;
        aCommandPos: integer;
        aVerbose: boolean;
        aTrace: TTrace;
        aTraceHandler: TProcTrace;
        aMyEventHandler: TAnyClass;
        aSock: TTCPSocket;
        procedure Trace(text:string);
    public
        constructor Create;
        procedure ShowHelp;
        procedure OpenModel(fileName: string);
        procedure SaveModelAs(fileName: string);
        procedure SaveModel;
        procedure ListStructures;
        procedure ListModules;
        procedure ListHosts;
        procedure ListPlugins;
        procedure DeleteTraceFiles;
        procedure TraceLevel(level:string);
        procedure AddPlugin(fileName: String);
        procedure AddFromFile(fileName:string);
        procedure ReadCommandsFromFile(fileName:string);
        procedure RedirectTrace(trace,dest,filename:string);
        procedure CloseModel;
        procedure CreateModel;
        procedure ExecDOSCommand(command:string);
        procedure VerboseMode(turn:string);
        procedure Verify;
        procedure GetGenesysInfo;
        procedure GetCommandLine;
        procedure SendFile(filename, hostname, portname:string);
        procedure SetActivationCode(code: string);
        procedure ReceiveFile(filename:string);
        procedure RunSimulation;
        procedure Show_Init;
        procedure ShowHostName;
        procedure Execute;
        property  TraceHandler:TProcTrace write aTraceHandler;
    end;

var manager: TShellManager;

{ TAnyClass }

constructor TAnyClass.Create;
begin
   inherited;
end;

procedure TAnyClass.BeginSim;
begin
   Application.MessageBox('The Simulation is Beginning', 'Interface',0);
end;

procedure TAnyClass.BeginRep;
begin
   Application.MessageBox('The Replication is Beginning', 'Interface',0);
end;

procedure TAnyClass.EndSim;
begin
   Application.MessageBox('The Simulation is Finishing', 'Interface',0);
end;

procedure TAnyClass.EndRep;
begin
   Application.MessageBox('The Replication is Finishing', 'Interface',0);
end;

procedure TAnyClass.EntMove;
begin
   Application.MessageBox('The Entity is Moving', 'Interface',0);
end;

procedure TAnyClass.Newevent;
begin
   Application.MessageBox('An event is beeing processed', 'Interface',0);
end;

procedure TAnyClass.OpenDoc;
begin
   Application.MessageBox('The Document is beeing opened', 'Interface',0);
end;

procedure TAnyClass.SaveDoc;
begin
   Application.MessageBox('The Document is beeing saved', 'Interface',0);
end;

procedure TAnyClass.CloseDoc;
begin
   Application.MessageBox('The Document is beeing closed', 'Interface',0);
end;

{ TShellManager }

procedure TShellManager.ShowHelp;
begin
   Trace ('-ac  ACTIVATIONCODE <code> : Set the activation code');
   Trace ('-ap  ADDPLUGIN <filename>  : Add a new plug-in');
   Trace ('-af  ADDFROMFILE <filename>: Add plug-ins that are listed in the <filename>');
   Trace ('-ch  CHECK                 : Verify the current model');
   Trace ('-cm  COMMANDS <filename>   : Read a list of consecutive commands from <filename>');
   Trace ('-cr  CREATE                : Create an empty model');
   Trace ('-cl  CLOSE                 : Close current model');
   Trace ('-dos DOS <command>         : Execute a DOS command');
   Trace ('-dt  DELETETRACE           : Delete the trace files');
   Trace ('-g   GO                    : Begin simulation');
   Trace ('-ggi GETGENESYSINFO        : Return information about genesys kernel');
   Trace ('-h   HELP                  : Shows this list');
   Trace ('-lh  LISTHOSTS             : List all hosts in the intranet');
   Trace ('-lm  LISTMODULES           : List all modules in the model');
   Trace ('-lp  LISTPLUGINS           : List all known plug-ins');
   Trace ('-ls  LISTSTRUCTURES        : List all strucutres in the model');
   Trace ('-o   OPEN <filename>       : Open the file <filename> with a model');
   Trace ('-rcv RECEIVE <filename>    : Receive a message and save into filename');
   Trace ('-rgo REMOTEGO <host> <port>: Begin simulation on remote host');
   Trace ('-s   SAVE                  : Save a file with the current model');
   Trace ('-sa  SAVEAS <filename>     : Save a file with the current model in <filename>');
   Trace ('-shn SHOWHOSTNAME          : Show the name of this host');
   Trace ('-snd SEND <filename> <host> <port>: Sends the filename to the host');
   Trace ('-st  STEP                  : Run a step of simulation');
   Trace ('-tl  TRACELEVEL <value>    : Set the trace level as <value> (greater means more details)');
   Trace ('-tr  TRACEREDIR <SHL|KER|SIM|REP> <SCR|FILE <filename>> : Redirect trace (shell, kernel, simulation or reports) output to screen or the <filename> file');
   Trace ('-v   VERBOSE <ON|OFF>      : Turn on or off the verbose mode');
   Trace ('-wu  WAITUSER              : Do nothing but start waiting user commands');
   Trace ('-x   EXIT                  : Leave Genesys. Same as QUIT');
   Trace ('');
end;

procedure TShellManager.RedirectTrace(trace,dest,filename:string);
begin
   if trace = 'SHL' then begin
      if dest = 'SCR' then begin
         Self.TraceHandler := self.aTrace.ScreenShow;
      end else begin
         self.aTrace.aShellFileName := filename;
         Self.TraceHandler := self.aTrace.ShellFileShow;
      end;
   end else if trace = 'KER' then begin
      if dest = 'SCR' then begin
         Genesys.Model.TraceHandler := self.aTrace.ScreenShow;
      end else begin
         self.aTrace.aKernelFileName := filename;
         Genesys.Model.TraceHandler := self.aTrace.KernelFileShow;
      end;
   end else if trace = 'SIM' then begin
      if dest = 'SCR' then begin
         Genesys.Model.TraceSimulationHandler := self.aTrace.ScreenShow;
      end else begin
         self.aTrace.aSimulFileName := filename;
         Genesys.Model.TraceSimulationHandler := self.aTrace.SimulFileShow;
      end;
   end else if trace = 'REP' then begin
      if dest = 'SCR' then begin
         Genesys.Model.TraceReportsHandler := self.aTrace.ScreenShow;
      end else begin
         self.aTrace.aReportFileName  := filename;
         Genesys.Model.TraceReportsHandler := self.aTrace.ReportFileShow;
      end;
   end;
end;


procedure TShellManager.OpenModel(fileName: string);
var res: integer;
begin
   if Genesys.ModelActivedModel = -1 then
      Genesys.ModelCreate;
   res := Genesys.Model.Load(fileName);
   if aVerbose then begin
      if res >= 0 then
         Trace ('::File opened sucessfully')
      else
         Trace ('::File could not be opened');
   end;
end;

procedure TShellManager.SaveModelAs(fileName: string);
begin
   Genesys.Model.SaveAs(fileName, true);
   if aVerbose then begin
      Trace ('::File saved sucessfully');
   end;
end;

procedure TShellManager.SaveModel;
begin
   Genesys.Model.Save;
   if aVerbose then begin
      Trace ('::File saved sucessfully');
   end;
end;

procedure TShellManager.DeleteTraceFiles;
begin
   if FileExists(aTrace.aShellFileName) then begin
      DeleteFile(aTrace.aShellFileName);
   end;
   if FileExists(aTrace.aKernelFileName) then begin
      DeleteFile(aTrace.aKernelFileName);
   end;
   if FileExists(aTrace.aSimulFileName) then begin
      DeleteFile(aTrace.aSimulFileName);
   end;
   if FileExists(aTrace.aReportFileName) then begin
      DeleteFile(aTrace.aReportFileName);
   end;
end;

procedure TShellManager.TraceLevel(level:string);
begin
   if level <> '' then begin
      Genesys.Model.TraceLevel := StrToInt(level);
      Trace ('::TraceLevel seted');
      end
   else begin
      Trace ('TraceLevel is '+IntToSTr(Genesys.Model.TraceLevel));
   end;
end;

procedure TShellManager.ListStructures;
var i,j, k,l: integer;
    structs, alist: TStringList;
    thisStruct: TModuleStructure;
    thisVariable: TVariable;
    texto: string;
begin
//   structs := 0;
   structs := Genesys.Model.SIMAN.Structures;
   for i := 0 to structs.Count - 1 do begin
      Trace('  :: Label:'+structs.Strings[i]);
      alist := TStringList(structs.Objects[i]);
      for j := 0 to alist.Count - 1 do begin
         thisStruct := TModuleStructure(alist.Objects[j]);
         if thisStruct <> nil then begin
            texto := 'Kind:'+thisStruct.Kind+' - ID:'+IntToStr(thisStruct.ID) + ' - Name:'+thisStruct.Name;
            if (thisStruct.Kind = cVARIABLE) or (thisStruct.Kind = cFORMULA) then begin
               //show variable values
               texto := texto + ' - Value:';
               thisVariable := TVariable(aList.Objects[j]);
               for k := 1 to thisVariable.Dimension1 do begin
                  for l := 1 to thisVariable.Dimension2 do begin
                     texto := texto + ' ['+IntToStr(k)+','+IntToStr(l)+']='+thisVariable.Values.Strings[(k-1)*thisVariable.Dimension2+(l-1)];
                  end;
               end;
            end;
         end else begin
            texto := 'Value:'+aList.Strings[j];
         end;
         Trace('        :: '+texto);
      end;
   end;
   if aVerbose then begin
      Trace ('::Structures listed');
   end;
end;

procedure TShellManager.ListModules;
var i,k: integer;
    thismodule: TModule;
    lastKind, texto, next: string;
begin
   lastKind := '';
   for i := 0 to Genesys.Model.ModuleCount - 1 do begin
      if lastKind <> Genesys.Model.ModuleType(i) then begin
         Trace('  :: Label:'+ Genesys.Model.ModuleType(i));
         lastKind := Genesys.Model.ModuleType(i);
      end;
      thisModule := Genesys.Model.Module(i);
      next := IntToStr(thisModule.NextID[0]);
      for k := 1 to thisModule.NextCount - 1 do begin
         next := next + ', '+IntToStr(thisModule.NextID[k]);
      end;
      texto := 'Kind:'+thisModule.Kind+' - ID:'+IntToStr(thisModule.ID) + ' - Next:' + next + ' - Name:'+thisModule.Name;
      Trace('        :: '+texto);
   end;
   if aVerbose then begin
      Trace ('::Modules listed');
   end;
end;

procedure TShellManager.ListPlugins;
var i: integer;
    umPlugIn: TPlugIn;
    texto: string;
begin
  for i := 0 to Genesys.PlugInCount -1  do begin
      umPlugIn := Genesys.PlugIn[i];
      texto := 'Name: '+ umPlugIn.Kind;
      //texto := texto + ' - Author: '+umPlugIn.Author;
      //texto := texto + ' - Description: '+umPlugIn.Description;
      if UmPlugIn.Dependences <> '' then texto := texto + ' - Dependences: '+UmPlugIn.Dependences;
      if UmPlugIn.Source then texto := texto + ' - Source';
      if UmPlugIn.Dreno then texto := texto + ' - Dreno';
      if UmPlugIn.Visual then texto := texto + ' - Visual';
////////      texto := texto +  ' - Saved:'+ DateTimeToStr(FileDateToDateTime(FileAge(umPlugin.DLL)));
      Trace('    ::'+texto);
   end;
   Trace('');
   if aVerbose then begin
      Trace ('::Plugins listed');
   end;
end;

procedure TShellManager.AddPlugin(fileName: String);
var res: string;
begin
   res := Genesys.PlugInAdd(fileName);
   if aVerbose then begin
      if res <> '' then
         Trace ('::Plug-in sucessfully added as kind "'+res+'"')
      else
         Trace ('::Plug-in "'+filename+'" could not be added');
   end;
end;


procedure TShellManager.CloseModel;
begin
   Genesys.Model.Close;
   if aVerbose then begin
      Trace ('::Model was closed');
   end;
end;

procedure TShellManager.CreateModel;
begin
   Genesys.ModelCreate;
   if aVerbose then begin
      Trace ('::Model was created');
   end;
end;


procedure TShellManager.VerboseMode(turn:string);
begin
   if UpperCase(turn) = 'ON' then begin
      aVerbose := true;
      Trace('::Verbose mode on');
      end
   else begin
      aVerbose := false;
   end
end;


procedure TShellManager.Verify;
var res: integer;
begin
   res := Genesys.Model.Check;
   if aVerbose then begin
      if res >= 0 then
         Trace('::The model is Ok')
      else
         Trace ('::The model has errors');
   end;
end;

procedure TShellManager.RunSimulation;
begin
   if aVerbose then Trace('::Executing...');
   Genesys.Model.Go;
   if aVerbose then Trace('::End of simulation');
end;

procedure TShellManager.Show_Init;
begin
   //show infos
   Trace ('Genesys - Generic Expansible Systems Simulator');
   Trace('');
   Trace ('ZeroUm Assessoria e Informatica LTDA');
   Trace ('cancian@inf.ufsc.br');
   Trace('');
   Trace('');
   Trace ('Type HELP to show a list of possible commands');
   Trace('');
   Trace('');
end;

procedure TShellManager.Trace(text:string);
begin
   self.aTraceHandler(text);
end;

procedure TShellManager.ReadCommandsFromFile(fileName: string);
var f:text;
    text:string;
    i: integer;
    auxList:TStringList;
begin
   if FileExists(fileName) then begin
      AssignFile(f, fileName);
      FileMode := 0;
      Reset(f);
      auxList := TStringList.Create;
      while (not EOF(f)) do begin
         readln(f, text);
         if (text <> '') then begin
            if (text[1] <> '#') then begin
               Genesys.AuxFunctions.SeparateWords(text, ' ', auxList);
               for i:= 0 to auxList.Count-1 do begin
                  aCommandWords.Add(auxList.Strings[i]);
               end;
            end;
         end;
      end;
      CloseFile(f);
   end else begin
      if aVerbose then begin
         Trace('::File could not be read');
      end;
   end;
end;

procedure TShellManager.AddFromFile(fileName: string);
var f:text;
    text:string;
begin
   if FileExists(fileName) then begin
      AssignFile(f, fileName);
      FileMode := 0;
      Reset(f);
      while (not EOF(f)) do begin
         readln(f, text);
         if (text <> '') then begin
            AddPlugin(text);
         end;
      end;
      CloseFile(f);
   end else begin
      if aVerbose then begin
         Trace('::File could not be read');
      end;
   end;
end;

procedure TShellManager.GetCommandLine;
var i: integer;
begin
   for i := 1 to ParamCount do begin
      aCommandWords.Add(ParamStr(i))
   end;
end;

procedure TShellManager.ReceiveFile(filename: string);
var res: boolean;
begin
   res := aSock.Receive(filename);
end;

procedure TShellManager.SendFile(filename,hostname, portname: string);
var res: boolean;
begin
  res := aSock.Send(hostname, portname, filename);
  if aVerbose then begin
     if res then begin
        Trace('File was sucessfully sent.');
     end else begin
        Trace('File could not be sent.');
     end;
  end;
end;

constructor TShellManager.Create;
begin
   inherited;
   //initialize agregated classes
   aMyEventHandler := TAnyClass.Create;
   aTrace := TTrace.Create;
   self.TraceHandler := aTrace.ScreenShow;
   self.aSock := TTCPSocket.Create(nil, '5005');
   //initializes attributes and command line
   aCommandPos := 0;
   aCommandWords := TStringList.Create;
   aCommandWords.Sorted := false;
   if ParamCount = 0 then begin
      //executing with no parameters, so show interface
      aVerbose := true;
      aCommandLine := false;
      Show_Init;
   end else begin
      aVerbose := false;
      aCommandLine := true;
      GetCommandLine;
   end;
   //initialize Genesys Kernel
   Genesys := TGenesysApplication.Create;
   Genesys.ModelCreate;
   Genesys.Model.TraceHandler := aTrace.ScreenShow;
   Genesys.Model.TraceSimulationHandler := aTrace.ScreenShow;
   Genesys.Model.TraceReportsHandler := aTrace.ScreenShow;
end;

procedure TShellManager.ShowHostName;
begin
   if aVerbose then begin
      Trace('::Hostname: "'+aSock.LocalHost+'" IP: '+aSock.NetSolver.GetMachineIP(aSock.LocalHost));
   end;
end;

procedure TShellManager.ExecDOSCommand(command: string);
begin
   
end;


procedure TShellManager.ListHosts;
var i: integer;
    hosts: TStringList;
    ip: string;
begin
   hosts := aSock.NetSolver.GetNetMachineNames;
   for i := 0 to hosts.Count-1 do begin
      if aVerbose then begin
         ip := aSock.NetSolver.GetMachineIP(hosts.Strings[i]);
         Trace('  '+ip+' ('+hosts.Strings[i]+')');
      end;
   end;
   if aVerbose then begin
      Trace('::Hosts listed');
   end;
end;

procedure TShellManager.SetActivationCode(code: string);
var res: boolean;
begin
   res := Genesys.SetActivationCode(code);
   if aVerbose then begin
      if res then
         Trace('::Activation code was sucessfuly inserted.')
      else
         Trace('::Activation code is invalid.');
   end;
end;

procedure TShellManager.GetGenesysInfo;
begin
   if aVerbose then begin
      Trace('::Kernel version: '+Genesys.Version);
      Trace('::Serial Number : '+Genesys.SerialNumber);
      Trace('::Licence Type  : '+Genesys.LicenseType);
   end;
end;

procedure TShellManager.Execute;
var thisCommand: string;
begin
   try
      //main loop
      repeat
         if (not aCommandLine) then begin
            if (aCommandWords.Count = 0) then begin
               //waits the user to insert a new command
               Trace('');
               write('Genesys Shell> ');
               readln(thisCommand);
               Genesys.AuxFunctions.SeparateWords(thisCommand, ' ', aCommandWords);
            end;
         end else begin
         end;
         try
            thisCommand := aCommandWords.Strings[aCommandPos];
            thisCommand := UpperCase(thisCommand);
         except
            write('::type a command...');
            aCommandWords.Add('#');
            thisCommand := '#';
         end;
         if thisCommand[1] = '#' then begin
            //only a commentary
            thisCommand := '';
         end;
         //executes the curruent command
         if      (thisCommand = 'HELP') OR (thisCommand = '-H')            then ShowHelp
         else if (thisCommand = 'CLOSE') OR (thisCommand = '-CL')          then CloseModel
         else if (thisCommand = 'CREATE') OR (thisCommand = '-CR')         then CreateModel
         else if (thisCommand = 'CHECK') OR (thisCommand = '-CH')          then Verify
         else if (thisCommand = 'GO') OR (thisCommand = '-G')              then RunSimulation
         else if (thisCommand = 'GETGENESYSINFO') OR (thisCommand = '-GGI')then GetGenesysInfo
         else if (thisCommand = 'DELETETRACE') OR (thisCommand = '-DT')    then DeleteTraceFiles
         else if (thisCommand = 'STEP') OR (thisCommand = '-ST')           then Genesys.Model.Step
         else if (thisCommand = 'SHOWHOSTNAME') OR (thisCommand = '-SHN')  then ShowHostName
         else if (thisCommand = 'LISTMODULES') OR (thisCommand = '-LM')    then ListModules
         else if (thisCommand = 'LISTHOSTS') OR (thisCommand = '-LH')      then ListHosts
         else if (thisCommand = 'LISTPLUGINS') OR (thisCommand = '-LP')    then ListPlugins
         else if (thisCommand = 'LISTSTRUCTURES') OR (thisCommand = '-LS') then ListStructures
         else if (thisCommand = 'SAVE') OR (thisCommand = '-S')            then SaveModel
         else if (thisCommand = 'COMMANDS') OR (thisCommand = '-CM')       then begin ReadCommandsFromFile(aCommandWords.Strings[aCommandPos+1]); inc(aCommandPos); end
         else if (thisCommand = 'OPEN') OR (thisCommand = '-O')            then begin OpenModel(aCommandWords.Strings[aCommandPos+1]);            inc(aCommandPos); end
         else if (thisCommand = 'SAVEAS') OR (thisCommand = '-SA')         then begin SaveModelAs(aCommandWords.Strings[aCommandPos+1]);          inc(aCommandPos); end
         else if (thisCommand = 'ADDPLUGIN')  OR (thisCommand = '-AP')     then begin AddPlugin(aCommandWords.Strings[aCommandPos+1]);            inc(aCommandPos); end
         else if (thisCommand = 'ADDFROMFILE')  OR (thisCommand = '-AF')   then begin AddFromFile(aCommandWords.Strings[aCommandPos+1]);          inc(aCommandPos); end
         else if (thisCommand = 'VERBOSE') OR (thisCommand = '-V')         then begin VerboseMode(aCommandWords.Strings[aCommandPos+1]);          inc(aCommandPos); end
         else if (thisCommand = 'EXIT') OR (thisCommand = '-X')            then Trace ('::Leaving Genesys...')
         else if (thisCommand = 'ACTIVATIONCODE') OR (thisCommand = '-AC') then begin
                                                                              if (aCommandPos+1)<aCommandWords.Count then begin
                                                                                 SetActivationCode(aCommandWords.Strings[aCommandPos+1]);
                                                                                 aCommandPos := aCommandPos + 1;
                                                                              end;
                                                                           end
         else if (thisCommand = 'REMOTEGO') OR (thisCommand = '-RGO')      then begin
                                                                              if (aCommandPos+2)<aCommandWords.Count then begin
                                                                                 aCommandPos := aCommandPos + 2;
                                                                              end;
                                                                           end
         else if (thisCommand = 'SEND') OR (thisCommand = '-SND')          then begin
                                                                              if (aCommandPos+3)<aCommandWords.Count then begin
                                                                                 SendFile(aCommandWords.Strings[aCommandPos+1], aCommandWords.Strings[aCommandPos+2], aCommandWords.Strings[aCommandPos+3]);
                                                                                 aCommandPos := aCommandPos + 3;
                                                                              end;
                                                                           end
         else if (thisCommand = 'RECEIVE') OR (thisCommand = '-RCV')       then begin
                                                                              if (aCommandPos+1)<aCommandWords.Count then begin
                                                                                 ReceiveFile(aCommandWords.Strings[aCommandPos+1]);
                                                                                 inc(aCommandPos);
                                                                              end;
                                                                           end
         else if (thisCommand = 'TRACEREDIR') OR (thisCommand = '-TR')     then begin
                                                                               if (aCommandPos+2)<aCommandWords.Count then begin
                                                                                  if ((UpperCase(aCommandWords.Strings[aCommandPos+2]) = 'FILE') and ((aCommandPos+3)<aCommandWords.Count)) then begin
                                                                                     RedirectTrace(UpperCase(aCommandWords.Strings[aCommandPos+1]), UpperCase(aCommandWords.Strings[aCommandPos+2]), UpperCase(aCommandWords.Strings[aCommandPos+3]));
                                                                                     aCommandPos := aCommandPos + 3;                                                                                  end else if (UpperCase(aCommandWords.Strings[aCommandPos+2]) = 'SCR') then begin
                                                                                     RedirectTrace(UpperCase(aCommandWords.Strings[aCommandPos+1]), UpperCase(aCommandWords.Strings[aCommandPos+2]), '');
                                                                                     aCommandPos := aCommandPos + 2;
                                                                                  end;
                                                                               end;
                                                                           end
         else if (thisCommand = 'DOS') OR (thisCommand = '-DOS')           then begin
                                                                               if (aCommandPos+1)<aCommandWords.Count then begin
                                                                                  ExecDOSCommand(aCommandWords.Strings[aCommandPos+1]);
                                                                                  inc(aCommandPos);
                                                                               end;
                                                                           end
         else if (thisCommand = 'TRACELEVEL') OR (thisCommand = '-TL')     then begin
                                                                               if (aCommandPos+1)<aCommandWords.Count then begin
                                                                                  TraceLevel(aCommandWords.Strings[aCommandPos+1]);
                                                                                  inc(aCommandPos);
                                                                               end else
                                                                                  TraceLevel('1');
                                                                               end
         else if (thisCommand = 'WAITUSER') OR (thisCommand = '-WU')       then aCommandLine := false
         else if (thisCommand <> '')                                       then Trace ('Unknown command');
         //atualize command words and pos
         inc(aCommandPos);
         while (aCommandPos > 0) do begin
            aCommandWords.Delete(0);
            dec(aCommandPos);
         end;
     until (thisCommand = 'QUIT') OR (thisCommand = 'EXIT') OR (thisCommand = '-X') OR (aCommandLine AND (aCommandWords.Count=0));
   except
      Trace('Error executing command. Aborting.');
   end;
end;

{ TTrace }

constructor TTrace.Create;
begin
   inherited;
end;

procedure TTrace._SaveFile(fileName,texto:string);
var f:text;
begin
   AssignFile(f, fileName);
   if FileExists(fileName) then begin
      append(f);
   end else begin
      rewrite(f);
   end;
   writeln(f, texto);
   CloseFile(f);
end;

procedure TTrace.ScreenShow(texto:string);
begin
   writeln(texto);
end;

procedure TTrace.ShellFileShow(texto:string);
begin
   _SaveFile(aShellFileName, texto);
end;

procedure TTrace.KernelFileShow(texto:string);
begin
   _SaveFile(aKernelFileName, texto);
end;

procedure TTrace.SimulFileShow(texto:string);
begin
   _SaveFile(aSimulFileName, texto);
end;

procedure TTrace.ReportFileShow(texto:string);
begin
   _SaveFile(aReportFileName, texto);
end;

begin
   manager := TShellManager.Create;
   manager.Execute;
   manager.Destroy;
   Application.Terminate;
end.