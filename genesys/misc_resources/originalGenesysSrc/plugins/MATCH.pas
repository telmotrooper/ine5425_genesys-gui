{Comment the next line ($UNDEF IsDllPlugin) if you intend to generate a DLL file}
{Uncomment it to generate a DCU file}
{$UNDEF IsDllPlugin}
{$IFDEF IsDllPlugin}
library MATCH;
{$ELSE}
unit MATCH;
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
    TMatch = Class(TModule)
    private
         {place here the attributes of your new module}
         {Examples:}
         {attribute1: type1;}
         {attribute2: type2;}
         {... YOUR CODE HERE ...}
         aAttribute: string;
         aQueues: TStringList; {list of queue names}
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
         property Attribute:string                read aAttribute    write aAttribute;
      end;

      TMatchManager = class(TObject)
      private
         function  AddModule: TMatch;
         procedure ReadModule(palavra: TStringList);
         procedure SaveModule(generalModule: TModule; var palavra: TStringList);
         procedure Execute(var thisModule: TMatch; entidade: word); virtual;
         function  VerifySymbols(blocoGeral: TModule): string;
         procedure UserExecute(var thisModule: TMatch; entity: word);
         procedure UserRead(var thisModule: TMatch; words: TStringList);
         procedure UserSave(thisModule: TMatch; var words: TStringList);
         procedure UserVerifySymbols(thisModule: TMatch; var verifyList: TStringList);
      public
         constructor Create;
         procedure ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
      end;

   var
      PlugInMatch : TMatchManager;
{$IFDEF IsDLLPlugin}
      Genesys: TGenesysAppPtr;
{$ELSE}
implementation
{$ENDIF}

   const
      {fill up the following informations about your new module}
      MODULE_KIND        = 'MATCH';                 {... YOUR INFOS HERE ...}
      MODULE_AUTHOR      = 'Rafael Luiz Cancian';   {... YOUR INFOS HERE ...}
      MODULE_VERSION     = '1.1.0 in 06/06/2005';   {... YOUR INFOS HERE ...}
      MODULE_DESCRIPTION = 'Match entities';        {... YOUR INFOS HERE ...}
      MODULE_IS_VISUAL   = true;                    {... YOUR INFOS HERE ...}
      MODULE_IS_SOURCE   = false;                   {... YOUR INFOS HERE ...}
      MODULE_IS_DISPOSE  = false;                   {... YOUR INFOS HERE ...}
      MODULE_DEPENDENCES = '';                      {... YOUR INFOS HERE ...}
      {example:  MODULE_DEPENDENCES = 'assign.dll;batch.dll' }


procedure TMatch.UserCreate(novoId: word; novoNome, novoKind: string);
begin
   {initialize here the necessary attributes of your new module}
   {Examples:}
   {attribute1 := '';}
   {attribute2 := 0;}
   {... YOUR CODE HERE ...}
   aAttribute := '';
   aQueues := TStringList.Create;
   aQueues.Sorted := false;
end;

procedure TMatchManager.UserRead(var thisModule:TMatch; words:TStringList);
var i,numQ: integer;
begin
    {Place here the code for reading the attributes of your new component}
    {The values readed from the model file are in the "words.Strings[]" vector}
    {Examples:}
    {thisModule.attribute1 := words.Strings[0];}
    {thisModule.attribute2 := StrToInt(words.Strings[1]);}
    {... YOUR CODE HERE ...}
    thisModule.aAttribute := words.Strings[0];
    numQ := StrToInt(words.Strings[1]);
    for i := 1 to numQ do begin
       thisModule.aQueues.Add(words.Strings[i+1]);
    end;
end;

procedure TMatchManager.UserSave(thisModule:TMatch; var words: TStringList);
var i: integer;
begin
    {Place here the code for saving the attributes of your new component}
    {The values to be saved in the model file need to be added to the "words" list}
    {Examples:}
    {words.Add(thisModule.attribute1);}
    {words.Add(IntToStr(thisModule.attribute2));}
    {... YOUR CODE HERE ...}
    words.Add(thisModule.aAttribute);
    words.Add(IntToStr(thisModule.aQueues.Count));
    for i := 0 to thisModule.aQueues.Count-1 do begin
       words.Add(thisModule.aQueues.Strings[i]);
    end;
end;

procedure TMatchManager.UserVerifySymbols(thisModule:TMatch; var verifyList:TStringList);
var i: integer;
begin
   {Place here the list of string attributes that parses to expression, attributes,}
   {variables, etc and need to be evaluated - just like "int(Norm(3,1))+Entity.JobStep"}
   {Place that as a list of calls to the "VerifySymbol" procedure, as shown bellow:}
   {Genesys.AuxFunctions.VerifySymbol(moduleName, description, expression, resultType, mandatory}
   {Examples:}
   {Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'The first attribute', thisModule.Attribute1, cEXPRESSION, true);}
   {... YOUR CODE HERE ...}
   Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'Attribute', thisModule.aAttribute, cATTRIBUTE, false);
   for i := 0 to thisModule.aQueues.Count-1 do begin
      Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'Queue['+IntToStr(i)+']', thisModule.aQueues.Strings[i], cQUEUE, true);
   end;
end;

procedure TMatchManager.UserExecute(var thisModule:TMatch; entity:word);
var i,j, input: integer;
    queuePos: TStringList;
    inAllQueues: boolean;
    queueindex, queueNumber, queuedEntity, attribNum: word;
    attribValue, thisAttribValue: double;
    thisQueue: TQueue;
    thisWait:TWaiting;
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
   {puts entity into corresponding queue}
   input := trunc(Genesys.Model.SIMAN.AttributeValue['Entity.InputNumber']);
   queueindex := Genesys.Model.SIMAN.QueueIndex(thisModule.aQueues.Strings[input-1]);
   thisQueue := Genesys.Model.SIMAN.Queue[queueindex];
   thisWait := TWaiting.Create(entity, thisModule.NextID[input]);
   thisQueue.InsertElement(thisWait);
   {search all queues if entities match}
   queuePos := TStringList.Create;
   i := 0;
   inAllQueues := true;
   while (i < thisModule.aQueues.Count) and inAllQueues do begin
      queueindex := Genesys.Model.SIMAN.QueueIndex(thisModule.aQueues.Strings[i]);
      queuenumber := Genesys.Model.SIMAN.QueueNumber(queueindex);
      //thisQueue := Genesys.Model.SIMAN.Queue[queueindex];
      Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Looking for corresponding entity at queue "'+thisModule.aQueues.Strings[i]+'"');
      if (thisModule.aAttribute = '') then begin
         inAllQueues := Genesys.Model.SIMAN.QueueNumberOfEntities(queueNumber) > 0;
         queuePos.Add('0');
      end else begin
         attribNum := Genesys.Model.SIMAN.AttributeIndex(thisModule.aAttribute);
         thisAttribValue := Genesys.Model.SIMAN.AttributeValue[thisModule.aAttribute];
         j := 1;
         inAllQueues := false;
         while (j <= Genesys.Model.SIMAN.QueueNumberOfEntities(queueNumber)) and (not inAllQueues) do begin
            queuedEntity := Genesys.Model.SIMAN.QueueEntityRank(queueNumber,j);
            attribvalue := Genesys.Model.SIMAN.EntityAttribute[queuedEntity, attribNum];
            inAllQueues := (attribValue = thisAttribValue);
            j := j + 1;
         end;
         queuePos.Add(IntToStr(j-1));
      end;
      i := i + 1;
   end;
   if inAllQueues then begin
      Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'All entities have matched. Entities are beeing dequeued.');
      for i := 0 to thisModule.aQueues.Count-1 do begin
         queueindex := Genesys.Model.SIMAN.QueueIndex(thisModule.aQueues.Strings[i]);
         queuenumber := Genesys.Model.SIMAN.QueueNumber(queueindex);
         queuedEntity := Genesys.Model.SIMAN.QueueEntityRank(queueNumber, StrToInt(queuePos.Strings[i]));
         Genesys.Model.SIMAN.QueueRemoveEntity(queuedEntity,queueNumber);
         Genesys.Model.SIMAN.EntitySendToModuleNumber(queuedEntity, thisModule.NextID[i], 0);
      end;
   end else begin
      Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Not all entities match. Entity was enqueued.');
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

constructor TMatch.Create(novoId: word; novoNome, novoKind: string);
begin
   try
      inherited;
      UserCreate(novoId, novoNome, novoKind);
   except
      Genesys.Model.Trace(cTLError, 'Plugin "' + MODULE_KIND + '" could not create module ' + self.Name);
   end;
end;

procedure TMatchManager.ReadModule(palavra: TStringList);
var thisModule: TMatch;
    newID: word;
 begin
    try
       newID := Genesys.Model.ModuleAdd(MODULE_KIND);
       thisModule := TMatch(Genesys.Model.ModuleByID(newID));
       Genesys.AuxFunctions.ReadInitialModule(MODULE_KIND, TModule(thisModule), palavra);
       UserRead(thisModule, palavra);
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not read module: ' + thisModule.Name);
   end;
end;

procedure TMatchManager.SaveModule(generalModule: TModule; var palavra: TStringList);
var thisModule: TMatch;
begin
   try
       thisModule := TMatch(generalModule);
       Genesys.AuxFunctions.SaveInitialModule(MODULE_KIND, thisModule, palavra);
       UserSave(thisModule, palavra);
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not save module: ' + thisModule.Name);
   end;
end;

function TMatchManager.VerifySymbols(blocoGeral: TModule): string;
var listaVerificacoes: TStringList;
    thisModule: TMatch;
begin
   try
      thisModule := TMatch(blocoGeral);
      GenesysErrorMessage := '';
      UserVerifySymbols(thisModule, listaVerificacoes);
      result := GenesysErrorMessage;
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not verify symbols of module: ' + thisModule.Name);
   end;
end;

procedure TMatchManager.Execute(var thisModule: TMatch; entidade: word);
begin
   try
      Genesys.Model.TraceSimulation(3, thisModule.ID, entidade, 'Entity arrives at "' +thisModule.Name+ '" module');
      UserExecute(thisModule, entidade);
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not execute module: ' + thisModule.Name);
   end;
end;

constructor TMatchManager.Create;
begin
   inherited Create;
end;



function TMatchManager.AddModule: TMatch;
var newModule: TMatch;
begin
   try
      newModule := TMatch.Create(0,'', MODULE_KIND);
      result := newModule;
   except
       Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not add a new module');
   end;
end;

procedure TMatchManager.ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
var auxStr: string;
    auxBool: boolean;
    ptrBloco: ^TModule;
    ptrStrList: ^TStringList;
    umComponente : TMatch;
    umaEntidade : Word;
begin
   try
      if metodo = pmREADMODULE  then begin
         //in: pointer1: FileName
         ptrStrList := umPonteiro1;
         PlugInMatch.ReadModule(ptrStrList^);
      end else if metodo = pmSAVEMODULE then begin
         //in: pointer1: a Module
         //out: TStringList with the attributes'values
         ptrBloco := umPonteiro1;
         ptrStrList := umPonteiro2;
         PlugInMatch.SaveModule(ptrBloco^, ptrStrList^);
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
         auxStr := PlugInMatch.VerifySymbols(ptrBloco^);
         GetMem(umPonteiro1, SizeOf(auxStr));
         string(umPonteiro1^) := auxStr;
      end else if metodo = pmINCLUDEMODULE then begin
         umComponente := PlugInMatch.AddModule;
         GetMem(umPonteiro1, SizeOf(umComponente));
         TMatch(umPonteiro1) := umComponente;
      end else if metodo = pmExecute then begin
         umComponente := TMatch(umPonteiro1^);
         umaEntidade := Word(umPonteiro2^);
         PlugInMatch.Execute(umComponente,umaEntidade);
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
   exportedMethods := PlugInMatch.ExportedMethodsAccess;
end;

{ Exports the method that gives access to all module's functions }
exports GetComponentMethods;

{ Initialization }
begin
   PlugInMatch := TMatchManager.Create;
end.

finalization
   PlugInMatch.Destroy;

{Template Author: Rafael Luiz Cancian}
{Date:  v1.0:10/03/2002,   v1.1:11/07/2003, ... v: 04/10/2003, 13/03/2004,  v3.1: 23/06/2004,  V4.0: 11/03/2005}

