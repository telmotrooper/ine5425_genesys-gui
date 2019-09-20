{Comment the next line ($UNDEF IsDllPlugin) if you intend to generate a DLL file}
{Uncomment it to generate a DCU file}
{$UNDEF IsDllPlugin}
{$IFDEF IsDllPlugin}
library WAITSIGNAL;
{$ELSE}
unit WAITSIGNAL;
   interface
{$ENDIF}
{TemplateVersion=4.0}

{                                                                              }
{                GENESYS - GENERIC EXPANSIBLE SYSTEMS SIMULATOR                }
{                    ZEROUM ASSESSORIA E INFORMÁTICA LTDA                      }
{                             RAFAEL LUIZ CANCIAN                              }
{                                                                              }
{                     ------------------------------------                     }
{                             GENESYS PLUG-IN FILE                             }
{                     ------------------------------------                     }
{                                                                              }
{                                                                              }
{                                  ATTENTION                                   }
{                     CHANGE ONLY THE MARKED/LABELED CODES,                    }
{                           KEEPPING THE REST INTACT.                          }
{                        WATCH OUT THE COMMENTS/LABELS                         }
{                                                                              }
{                          BE CAREFUL ABOUT YOUR CODE,                         }
{               THE STABILITY OF GENESYS DEPENDS ON ITS CORRECTNESS            }
{                                                                              }
{                                                                              }
{     Contact the project Leader Rafael Luiz Cancian throught the emails:      }
{                     cancian@inf.ufsc.br; cancian@univali.br                  }
{                                                                              }

uses
  ShareMem,
  SysUtils,
  Classes,
  Forms,
  extctrls,
  Dialogs,
  graphics,
  YaccLib,
  GenesysKernel;

type
    TWaitSignalType = (tpWAIT, tpSIGNAL);
    TWaitSignalModule = Class(TModule)
    private
         {place here the attributes of your new module}
         {Examples:}
         {attribute1: type1;}
         {attribute2: type2;}
         {... YOUR CODE HERE ...}
         aType:TWaitSignalType;
         aSignal: string;
         aLimit: string;
         aQueueName: string;
         {place here the methods of your new module}
         {Examples:}
         {procedure Methode1;}
         {function Methode2(param1:type1);}
         {... YOUR CODE HERE ...}

          procedure UserCreate(novoId: word; novoNome, novoKind: string);
      public
         constructor Create(novoId: word; novoNome, novoKind: string); override;
      published
         {place in this region the property of this module that can be edit by the user}
         {Examples:}
         {property MyProperty1:type1  read attribute1  write attribute1;}
         {property MyProperty2:type2  read attribute2  write attribute2;}
         {... YOUR CODE HERE ...}
         property WSType:TWaitSignalType read aType      write aType;
         property Signal:string          read aSignal    write aSignal;
         property Limit:string           read aLimit     write aLimit;
         property QueueName:string       read aQueueName write aQueueName;
      end;

      TWaitSignalManager = class(TObject)
      private
         function  AddModule: TWaitSignalModule;
         procedure ReadModule(palavra: TStringList);
         procedure SaveModule(generalModule: TModule; var palavra: TStringList);
         procedure Execute(var thisModule: TWaitSignalModule; entidade: word); virtual;
         function  VerifySymbols(blocoGeral: TModule): string;
         procedure UserExecute(var thisModule: TWaitSignalModule; entity: word);
         procedure UserRead(var thisModule: TWaitSignalModule; words: TStringList);
         procedure UserSave(thisModule: TWaitSignalModule; var words: TStringList);
         procedure UserVerifySymbols(thisModule: TWaitSignalModule; var verifyList: TStringList);
      public
         constructor Create;
         procedure ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
      end;

   var
      PlugInWaitSignal: TWaitSignalManager;
{$IFDEF IsDLLPlugin}
      Genesys: TGenesysAppPtr;
{$ELSE}
implementation
{$ENDIF}

   const
      {fill up the following informations about your new module}
      MODULE_KIND        = 'WAITSIGNAL';            {... YOUR INFOS HERE ...}
      MODULE_AUTHOR      = 'Rafael Luiz Cancian';   {... YOUR INFOS HERE ...}
      MODULE_VERSION     = '1.1.0 in 15/05/2005';   {... YOUR INFOS HERE ...}
      MODULE_DESCRIPTION = 'Wait for signal or Send a signal';       {... YOUR INFOS HERE ...}
      MODULE_IS_VISUAL   = true;                    {... YOUR INFOS HERE ...}
      MODULE_IS_SOURCE   = false;                   {... YOUR INFOS HERE ...}
      MODULE_IS_DISPOSE  = false;                   {... YOUR INFOS HERE ...}
      MODULE_DEPENDENCES = '';                      {... YOUR INFOS HERE ...}
      {example:  MODULE_DEPENDENCES = 'assign.dll;batch.dll' }


procedure TWaitSignalModule.UserCreate(novoId: word; novoNome, novoKind: string);
begin
   {initialize here the necessary attributes of your new module}
   {Examples:}
   {attribute1 := '';}
   {attribute2 := 0;}
   {... YOUR CODE HERE ...}
   aType := tpSignal;
   aSignal := '1';
   aLimit := '';
   aQueueName := '';
end;

procedure TWaitSignalManager.UserRead(var thisModule:TWaitSignalModule; words:TStringList);
begin
    {Place here the code for reading the attributes of your new component}
    {The values readed from the model file are in the "words.Strings[]" vector}
    {Examples:}
    {thisModule.attribute1 := words.Strings[0];}
    {thisModule.attribute2 := StrToInt(words.Strings[1]);}
    {... YOUR CODE HERE ...}
    if StrToInt(words.Strings[0]) = 0 then
       thisModule.aType := tpWait
    else
       thisModule.aType := tpSignal;
    thisModule.aSignal := words.Strings[1];
    thisModule.aLimit := words.Strings[2];
    if thisModule.WSType = tpWait then begin
       thisModule.aQueueName := Genesys.AuxFunctions.Underscore(words.Strings[3]);
    end else begin
       thisModule.aQueueName := '';
    end;
end;

procedure TWaitSignalManager.UserSave(thisModule:TWaitSignalModule; var words: TStringList);
begin
    {Place here the code for saving the attributes of your new component}
    {The values to be saved in the model file need to be added to the "words" list}
    {Examples:}
    {words.Add(thisModule.attribute1);}
    {words.Add(IntToStr(thisModule.attribute2));}
    {... YOUR CODE HERE ...}
    if thisModule.aType = tpWait then
       words.Add('0')
    else
       words.Add('1');
    words.Add(thisModule.aSignal);
    words.Add(thisModule.aLimit);
    words.Add(thisModule.aQueueName);
end;

procedure TWaitSignalManager.UserVerifySymbols(thisModule:TWaitSignalModule; var verifyList:TStringList);
begin
   {Place here the list of string attributes that parses to expression, attributes,}
   {variables, etc and need to be evaluated - just like "int(Norm(3,1))+Entity.JobStep"}
   {Place that as a list of calls to the "VerifySymbol" procedure, as shown bellow:}
   {Genesys.AuxFunctions.VerifySymbol(moduleName, description, expression, resultType, mandatory}
   {Examples:}
   {Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'The first attribute', thisModule.Attribute1, cEXPRESSION, true);}
   {... YOUR CODE HERE ...}
   Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'Signal', thisModule.aSignal, cEXPRESSION, true);
   Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'Limit', thisModule.aLimit, cEXPRESSION, false);
   if thisModule.aType = tpWait then
      Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'Queue Name', thisModule.aQueueName, cQUEUE, true);
end;

procedure TWaitSignalManager.UserExecute(var thisModule:TWaitSignalModule; entity:word);
var index, i,j, numEnts: integer;
    element: TWaiting;
    signal: double;
    enqueuedEntity: word;
    limit, waitLimit: integer;
    waitList:TStringList;
    signalized, setsFree: integer;
    thisWait: TWaitSignalModule;
begin
   {Place here the main code of your new component. This code will be executed every}
   {time an entity arrivals to modules of your component}
   {You can use "Genesys." to get access to the simulator's public methods}
   {It's important to verify the logic and consistency of your code to avoid unexpected}
   {behaviours in the simulator}
   {Example: (The following code just prints the ID of the entity and sends it to the}
   {next module in the model)}
   {Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'The entity ID '+IntToStr(entity) + 'is in this module');}
   {Genesys.Model.SIMAN.EntitySendToModuleNumber(entity, thisModule.NextID[0], 0);}
   {... YOUR CODE HERE ...}
   signal := Genesys.Model.SIMAN.StringEvaluateFormula(thisModule.aSignal);
   if thisModule.aLimit <> '' then
      limit := trunc(Genesys.Model.SIMAN.StringEvaluateFormula(thisModule.aLimit))
   else
      limit := 65535; {unlimited}
   if thisModule.aType = tpWAIT then begin
      index := Genesys.Model.SIMAN.QueueIndex(thisModule.aQueueName);
      if index >=0 then begin
         Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Entity waits for signal "'+FloatToStr(signal)+'" in the queue "'+thisModule.aQueueName+'"');
         element := TWaiting.Create(entity, thisModule.NextID[0]);
         Genesys.Model.SIMAN.Queue[index].InsertElement(element);
      end else begin
         Genesys.Model.Trace(cTLError, 'Error: Queue "' + thisModule.aQueueName + '" not found');
      end;
   end else begin
      {SIGNAL}
      signalized := 0;
      Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Sending signal "'+FloatToStr(signal)+'"');
      waitList := Genesys.Model.ModulesOfKind[MODULE_KIND];
      i := 0;
      while (i < waitList.Count) and ((limit = -1) or ((limit >= 0) and (signalized < limit))) do begin
         thisWait := TWaitSignalModule(waitList.Objects[i]);
         if thisWait.aType = tpWAIT then begin
            {is a wait}
            if Genesys.Model.SIMAN.StringEvaluateFormula(thisWait.aSignal) = signal then begin
               {and is waiting for this signal}
               if thisWait.aLimit <> '' then
                  waitLimit := trunc(Genesys.Model.SIMAN.StringEvaluateFormula(thisWait.aLimit))
               else
                  waitLimit := 65535;
               {signal some entities that are waiting - the smallest number from limit and waitlimit}
               if waitLimit < limit - signalized then
                  setsFree := waitLimit
               else begin
                  setsFree := limit;
                  if limit < 65535 then
                     setsFree := setsFree - signalized;
               end;
               {try to signal these entities}
               index := Genesys.Model.SIMAN.QueueIndex(thisWait.aQueueName);
               index := Genesys.Model.SIMAN.QueueNumber(index);  {index has QueueID}
               numEnts := Genesys.Model.SIMAN.QueueNumberOfEntities(index);
               if numEnts < setsFree then begin
                  setsFree := numEnts;
               end;
               {signal the entities into the queue}
               for j := 1 to setsFree do begin
                  enqueuedEntity := Genesys.Model.SIMAN.QueueEntityRank(index, 0);
                  Genesys.Model.SIMAN.QueueRemoveEntity(enqueuedEntity, index);
                  Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Removing entity '+IntToStr(enqueuedEntity)+' from queue "'+thisWait.aQueueName+'"');
                  signalized := signalized + 1;
                  Genesys.Model.SIMAN.EntitySendToModuleNumber(enqueuedEntity, thisWait.NextID[0], 0);
               end;
            end;
         end;
         i := i + 1;
      end;
      Genesys.Model.SIMAN.EntitySendToModuleNumber(entity, thisModule.NextID[0], 0);
   end;
end;



{******************************************************************************}
{******************************************************************************}
{                                                                              }
{              END OF EDITABLE AREA                                            }
{              THERE IS NO MORE CHANGES TO DO IN THIS FILE                     }
{                                                                              }
{******************************************************************************}
{                                                                              }
{              TO GENERATE THE PLUG-IN, COMPILE THIS PROJECT (CTRL+F9).        }
{              IF THE FILE HAS NO SYNTAX ERRORS, A DLL FILE IS GENERATED.      }
{              TO INCLUDE THE PLUGIN (DLL) IN THE GENESYS APPLICATION,         }
{              INVOQUE THE METHODE GENESYS.PLUGINADD                           }
{                                                                              }
{******************************************************************************}
{******************************************************************************}




































































{ The code bellow MUST NOT BE CHANGED. They are needded to interface with Genesys Kernel }

constructor TWaitSignalModule.Create(novoId: word; novoNome, novoKind: string);
begin
   try
      inherited;
      UserCreate(novoId, novoNome, novoKind);
   except
      Genesys.Model.Trace(cTLError, 'Plugin "' + MODULE_KIND + '" could not create module ' + self.Name);
   end;
end;

procedure TWaitSignalManager.ReadModule(palavra: TStringList);
var thisModule: TWaitSignalModule;
    newID: word;
 begin
    try
       newID := Genesys.Model.ModuleAdd(MODULE_KIND);
       thisModule := TWaitSignalModule(Genesys.Model.ModuleByID(newID));
       Genesys.AuxFunctions.ReadInitialModule(MODULE_KIND, TModule(thisModule), palavra);
       UserRead(thisModule, palavra);
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not read module: ' + thisModule.Name);
   end;
end;

procedure TWaitSignalManager.SaveModule(generalModule: TModule; var palavra: TStringList);
var thisModule: TWaitSignalModule;
begin
   try
       thisModule := TWaitSignalModule(generalModule);
       Genesys.AuxFunctions.SaveInitialModule(MODULE_KIND, thisModule, palavra);
       UserSave(thisModule, palavra);
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not save module: ' + thisModule.Name);
   end;
end;

function TWaitSignalManager.VerifySymbols(blocoGeral: TModule): string;
var listaVerificacoes: TStringList;
    thisModule: TWaitSignalModule;
begin
   try
      thisModule := TWaitSignalModule(blocoGeral);
      GenesysErrorMessage := '';
      UserVerifySymbols(thisModule, listaVerificacoes);
      result := GenesysErrorMessage;
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not verify symbols of module: ' + thisModule.Name);
   end;
end;

procedure TWaitSignalManager.Execute(var thisModule: TWaitSignalModule; entidade: word);
begin
   try
      Genesys.Model.TraceSimulation(3, thisModule.ID, entidade, 'Entity arrives at "' +thisModule.Name+ '" module');
      UserExecute(thisModule, entidade);
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not execute module: ' + thisModule.Name);
   end;
end;

constructor TWaitSignalManager.Create;
begin
   inherited Create;
end;



function TWaitSignalManager.AddModule: TWaitSignalModule;
var newModule: TWaitSignalModule;
begin
   try
      newModule := TWaitSignalModule.Create(0,'', MODULE_KIND);
      result := newModule;
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not add a new module');
   end;
end;

procedure TWaitSignalManager.ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
var auxStr: string;
    auxBool: boolean;
    ptrBloco: ^TModule;
    ptrStrList: ^TStringList;
    umComponente : TWaitSignalModule;
    umaEntidade : Word;
begin
   try
      if metodo = pmREADMODULE  then begin
         //in: pointer1: FileName
         ptrStrList := umPonteiro1;
         PlugInWaitSignal.ReadModule(ptrStrList^);
      end else if metodo = pmSAVEMODULE then begin
         //in: pointer1: a Module
         //out: TStringList with the attributes'values
         ptrBloco := umPonteiro1;
         ptrStrList := umPonteiro2;
         PlugInWaitSignal.SaveModule(ptrBloco^, ptrStrList^);
         umPonteiro2 := ptrStrList;
         //TStringList(umPonteiro2^) := ptrStrList^;
      end else if metodo = pmGETTYPE then begin
         auxStr := MODULE_KIND;
         GetMem(umPonteiro1, SizeOf(auxStr));
         string(umPonteiro1^) := auxStr;
      end else if metodo = pmGETAUTHOR then begin
         auxStr := MODULE_AUTHOR;
         GetMem(umPonteiro1, SizeOf(auxStr));
         string(umPonteiro1^) := auxStr;
      end else if metodo = pmGETVERSION then begin
         auxStr := MODULE_VERSION;
         GetMem(umPonteiro1, SizeOf(auxStr));
         string(umPonteiro1^) := auxStr;
      end else if metodo = pmGETDESCRIP then begin
         auxStr := MODULE_DESCRIPTION;
         GetMem(umPonteiro1, SizeOf(auxStr));
         string(umPonteiro1^) := auxStr;
      end else if metodo = pmGETDEPENDENCES then begin
         auxStr := MODULE_DEPENDENCES;
         GetMem(umPonteiro1, SizeOf(auxStr));
         string(umPonteiro1^) := auxStr;
      end else if metodo = pmGETINFOS then begin
         Genesys := TGenesysApplication(umPonteiro1^); //// NEW FOR PlugInMicrocontroller 3.1 ////
         auxStr := MODULE_KIND+';'+MODULE_AUTHOR+';'+MODULE_VERSION+';'+MODULE_DESCRIPTION+';';
         if MODULE_IS_SOURCE then auxStr := auxStr+'1;' else auxStr := auxStr+'0;';
         if MODULE_IS_DISPOSE then auxStr := auxStr+'1;' else auxStr := auxStr+'0;';
         if MODULE_IS_VISUAL    then auxStr := auxStr+'1;' else auxStr := auxStr+'0;';
         auxStr := auxStr + MODULE_DEPENDENCES;
         GetMem(umPonteiro1, SizeOf(auxStr));
         string(umPonteiro1^) := auxStr;
      end else if metodo = pmGetSOURCE then begin
         auxBool := MODULE_IS_SOURCE;
         GetMem(umPonteiro1, SizeOf(auxBool));
         boolean(umPonteiro1^) := auxBool;
      end else if metodo = pmGetDRENO then begin
         auxBool := MODULE_IS_DISPOSE;
         GetMem(umPonteiro1, SizeOf(auxBool));
         boolean(umPonteiro1^) := auxBool;
      end else if metodo = pmGetVISUAL then begin
         auxBool := MODULE_IS_VISUAL;
         GetMem(umPonteiro1, SizeOf(auxBool));
         boolean(umPonteiro1^) := auxBool;
      end else if metodo = pmVERIFYSYMBOLS then begin
         ptrBloco := umPonteiro1;
         auxStr := PlugInWaitSignal.VerifySymbols(ptrBloco^);
         GetMem(umPonteiro1, SizeOf(auxStr));
         string(umPonteiro1^) := auxStr;
      end else if metodo = pmINCLUDEMODULE then begin
         umComponente := PlugInWaitSignal.AddModule;
         GetMem(umPonteiro1, SizeOf(umComponente));
         TWaitSignalModule(umPonteiro1) := umComponente;
      end else if metodo = pmExecute then begin
         umComponente := TWaitSignalModule(umPonteiro1^);
         umaEntidade := Word(umPonteiro2^);
         PlugInWaitSignal.Execute(umComponente,umaEntidade);
      end else begin
         auxStr := 'Error: Unknown command';
         GetMem(umPonteiro1, SizeOf(auxStr));
         string(umPonteiro1^) := auxStr;
      end;
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not execute such function');
   end;
end;

procedure GetComponentMethods(thisSimulator: TGenesysAppPtr; var exportedMethods: TPlugInAccess);
begin
{$IFDEF IsDllPlugin}
   Genesys := thisSimulator;
{$ENDIF}
   exportedMethods := PlugInWaitSignal.ExportedMethodsAccess;
end;

{ Exports the method that gives access to all module's functions }
exports GetComponentMethods;

{ Initialization }
begin
   PlugInWaitSignal := TWaitSignalManager.Create;
end.

finalization
   PlugInWaitSignal.Destroy;
