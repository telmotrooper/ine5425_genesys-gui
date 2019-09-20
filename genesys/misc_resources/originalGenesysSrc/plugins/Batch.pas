{Comment the next line ($UNDEF IsDllPlugin) if you intend to generate a DLL file.}
{Uncomment it to generate a DCU file}
{$UNDEF IsDllPlugin}
{$IFDEF IsDllPlugin}
library BATCH;
{$ELSE}
unit BATCH;
   interface
{$ENDIF}
{Templateversion=4.0}

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

{ Important note about DLL memory management: ShareMem must be the
  first unit in your library's USES clause AND your project's (select
  Project-View Source) USES clause if your DLL exports any procedures or
  functions that pass strings as parameters or function results. This
  applies to all strings passed to and from your DLL--even those that
  are nested in records and classes. ShareMem is the interface unit to
  the BORLNDMM.DLL shared memory manager, which must be deployed along
  with your DLL. To avoid using BORLNDMM.DLL, pass string information
  using PChar or ShortString parameters.
  Author: Rafael Luiz Cancian, cancian@univali.br; cancian@inf.ufsc.br}

uses
  SysUtils,
  Classes,
  Forms,
  extctrls,
  Dialogs,
  graphics,
  YaccLib,
  GenesysKernel;

type
    TBatchRule = (brFIRST, brLAST, brSUM, brPRODUCT);
    TBatchType = (btTEMPORARY, btPERMANENT);
    TNewModuleBatch = Class(TModule)
    private
         {place here the attributes of your new module}
         {Examples:}
         {attribute1: type1;}
         {attribute2: type2;}
         {... YOUR CODE HERE ...}
         aBatchSize: string;
         aBatchType: TBatchType;
         aAttribute: string;
         aBatchRule: TBatchRule;
         aQueueID: word;
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
         property BatchType:TBatchType read aBatchType  write aBatchType;
         property BatchSize:string     read aBatchSize  write aBatchSize;
         property Attribute:string     read aAttribute  write aAttribute;
         property Rule:TBatchRule      read aBatchRule  write aBatchRule;
      end;

      TModuleManagerBatch = class(TObject)
      private
         function  AddModule: TNewModuleBatch;
         procedure ReadModule(palavra: TStringList);
         procedure SaveModule(generalModule: TModule; var palavra: TStringList);
         procedure Execute(var thisModule: TNewModuleBatch; entidade: word); virtual;
         function  VerifySymbols(blocoGeral: TModule): string;
         procedure UserExecute(var thisModule: TNewModuleBatch; entity: word);
         procedure UserRead(var thisModule: TNewModuleBatch; words: TStringList);
         procedure UserSave(thisModule: TNewModuleBatch; var words: TStringList);
         procedure UserVerifySymbols(thisModule: TNewModuleBatch; var verifyList: TStringList);
      public
         constructor Create;
         procedure ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
      end;

   var
      PlugInBatch : TModuleManagerBatch;
{$IFDEF IsDLLPlugin}
      Genesys: TGenesysAppPtr;
{$ELSE}
implementation
{$ENDIF}

   const
      {fill up the following informations about your new module}
      MODULE_KIND        = 'BATCH';                 {... YOUR INFOS HERE ...}
      MODULE_AUTHOR      = 'Rafael Luiz Cancian';   {... YOUR INFOS HERE ...}
      MODULE_VERSION     = '1.1.0 in 15/03/2005';   {... YOUR INFOS HERE ...}
      MODULE_DESCRIPTION = 'Group entities into a batch';    {... YOUR INFOS HERE ...}
      MODULE_IS_VISUAL   = true;                    {... YOUR INFOS HERE ...}
      MODULE_IS_SOURCE   = false;                   {... YOUR INFOS HERE ...}
      MODULE_IS_DISPOSE  = false;                   {... YOUR INFOS HERE ...}
      MODULE_DEPENDENCES = '';                      {... YOUR INFOS HERE ...}
      {example:  MODULE_DEPENDENCES = 'assign.dll;batch.dll' }


procedure TNewModuleBatch.UserCreate(novoId: word; novoNome, novoKind: string);
begin
   {initialize here the necessary attributes of your new module}
   {Examples:}
   {attribute1 := '';}
   {attribute2 := 0;}
   {... YOUR CODE HERE ...}
   aBatchSize := '1';
   aAttribute := '';
   aBatchRule := brFIRST;
   aBatchType := btTemporary;
   aQueueID := Genesys.Model.SIMAN.QueueInsert(0, novoNome, qtFIFO, '');  {novonome ainda vazio}
end;

procedure TModuleManagerBatch.UserRead(var thisModule:TNewModuleBatch; words:TStringList);
begin
    {Place here the code for reading the attributes of your new component}
    {The values readed from the model file are in the "words.Strings[]" vector}
    {Examples:}
    {thisModule.attribute1 := words.Strings[0];}
    {thisModule.attribute2 := StrToInt(words.Strings[1]);}
    {... YOUR CODE HERE ...}
    if StrToInt(words.Strings[0]) = 0 then begin
      thisModule.aBatchType := btPermanent;
    end else begin
      thisModule.aBatchType := btTemporary;
    end;
    thisModule.aBatchSize := words.Strings[1];
    thisModule.aAttribute := words.Strings[2];
    case StrToInt(words.Strings[3]) of
       0: thisModule.aBatchRule := brFIRST;
       1: thisModule.aBatchRule := brLAST;
       2: thisModule.aBatchRule := brSUM;
       3: thisModule.aBatchRule := brPRODUCT;
       else thisModule.aBatchRule := brFIRST;
    end;
    Genesys.Model.SIMAN.QueueName[thisModule.aQueueID] := thisModule.Name + '.queue';
end;

procedure TModuleManagerBatch.UserSave(thisModule:TNewModuleBatch; var words: TStringList);
begin
    {Place here the code for saving the attributes of your new component}
    {The values to be saved in the model file need to be added to the "words" list}
    {Examples:}
    {words.Add(thisModule.attribute1);}
    {words.Add(IntToStr(thisModule.attribute2));}
    {... YOUR CODE HERE ...}
    words.Add(thisModule.aBatchSize);
    words.Add(thisModule.aAttribute);
    case thisModule.aBatchRule of
       brFIRST:   words.Add('0');
       brLAST :   words.Add('1');
       brSUM  :   words.Add('2');
       brPRODUCT: words.Add('3');
    end;
end;

procedure TModuleManagerBatch.UserVerifySymbols(thisModule:TNewModuleBatch; var verifyList:TStringList);
begin
   {Place here the list of string attributes that parses to expression, attributes,}
   {variables, etc and need to be evaluated - just like "int(Norm(3,1))+Entity.JobStep"}
   {Place that as a list of calls to the "VerifySymbol" procedure, as shown bellow:}
   {Genesys.AuxFunctions.VerifySymbol(moduleName, description, expression, resultType, mandatory}
   {Examples:}
   {Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'The first attribute', thisModule.Attribute1, cEXPRESSION, true);}
   {... YOUR CODE HERE ...}
   Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'BatchSize', thisModule.aBatchSize, cEXPRESSION, true);
   Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'Attribute', thisModule.aAttribute, cATTRIBUTE, false);
end;

procedure TModuleManagerBatch.UserExecute(var thisModule:TNewModuleBatch; entity:word);
var newQueueID, batchEntityID, deletedEntity: word;
    i,j, numAtrib, actualBatchSize, totalBatchSize: integer;
    atribValue: double;
    found: boolean;
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
   Genesys.Model.SIMAN.EntityInsertIntoQueue(entity, thisModule.aId, thisModule.aQueueID);
   if thisModule.aAttribute = '' then begin
      actualBatchSize := Genesys.Model.SIMAN.QueueNumberOfEntities(thisModule.aQueueID)
   end else begin
      {conta quantas entidades com esse valor de atributo estão na fiula do Batch}
      actualBatchSize := 0;
      numAtrib := Genesys.Model.SIMAN.AttributeIndex(thisModule.aAttribute);
      atribValue := Genesys.Model.SIMAN.EntityAttribute[entity,numAtrib];
      for i := 0 to Genesys.Model.SIMAN.QueueNumberOfEntities(thisModule.aQueueID)-1 do begin
          batchEntityID := Genesys.Model.SIMAN.QueueEntityRank(thisModule.aQueueID, i);
          if Genesys.Model.SIMAN.EntityAttribute[batchEntityID,numAtrib] = atribValue then begin
             actualBatchSize := actualBatchSize + 1;
          end;
      end;
   end;
   totalBatchSize := trunc(Genesys.Model.SIMAN.StringEvaluateFormula(thisModule.aBatchSize));
   if actualBatchSize = totalBatchSize then begin
      Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Batch is beeing formed');
      if thisModule.aBatchRule = brFIRST then begin
         if thisModule.aAttribute = '' then begin
            {no attribute. Take the very first entity in que queue}
            batchEntityID := Genesys.Model.SIMAN.QueueEntityRank(thisModule.aQueueID, 0);
         end else begin
            {there is an attribute. Take the first entity with that attribute}
            i := 0;
            found := false;
            while (i < Genesys.Model.SIMAN.QueueNumberOfEntities(thisModule.aQueueID)) and not found do begin
               deletedEntity := Genesys.Model.SIMAN.QueueEntityRank(thisModule.aQueueID, i);
               found := (Genesys.Model.SIMAN.EntityAttribute[deletedEntity,numAtrib] = atribValue);
               i := i + 1;
            end;
            {will always finds}
            batchEntityID := Genesys.Model.SIMAN.QueueEntityRank(thisModule.aQueueID, i-1);
         end;
      end else begin
         batchEntityID := Genesys.Model.SIMAN.QueueEntityRank(thisModule.aQueueID, Genesys.Model.SIMAN.QueueNumberOfEntities(thisModule.aQueueID)-1);
      end;
      if thisModule.aBatchType = btTemporary then begin
         {creates a new queue that will contain the entities temporary grouped in this batch}
         newQueueID := Genesys.Model.SIMAN.QueueInsert(0,thisModule.aName+'_'+IntToStr(entity)+'.Queue',qtFIFO,'');
      end;
      for i := Genesys.Model.SIMAN.QueueNumberOfEntities(thisModule.aQueueID)-1 downto 0 do begin
         deletedEntity := Genesys.Model.SIMAN.QueueEntityRank(thisModule.aQueueID, i);
         if (thisModule.Attribute = '') or
         ((thisModule.Attribute <> '') and (Genesys.Model.SIMAN.EntityAttribute[deletedEntity,numAtrib] = atribValue)) then begin
            if (thisModule.aBatchRule = brSUM) OR (thisModule.aBatchRule = brPRODUCT) then begin
               {calculates the sum or product of all attributes}
               for j := 0 to Genesys.Model.SIMAN.AttributesCount -1 do begin
                  if (thisModule.aBatchRule = brSUM) then
                     Genesys.Model.SIMAN.EntityAttribute[batchEntityID,j] :=  0
                  else
                     Genesys.Model.SIMAN.EntityAttribute[batchEntityID,j] :=  0;
               end;
            end;
            if deletedEntity <> batchEntityID then begin
               {remove entity from the queue}
               Genesys.Model.SIMAN.QueueRemoveEntity(deletedEntity, thisModule.aQueueID);
               if thisModule.aBatchType = btPermanent then begin
                  {Permanent batch. Dispose entities}
                  Genesys.Model.SIMAN.EntityDispose(deletedEntity, false);
               end else begin
                  {Temporary batch. Insert entities into a new queue}
                  Genesys.Model.SIMAN.EntityInsertIntoQueue(deletedEntity,thisModule.ID,newQueueID);
               end;
            end else begin
               {this entity will represent the group}
               if thisModule.aBatchType = btTemporary then begin
                   {this entity needs to know where are the other entities it represents}
                   numAtrib := Genesys.Model.SIMAN.AttributeIndex('Entity.BatchQueue');
                   Genesys.Model.SIMAN.EntityAttribute[deletedEntity,numAtrib] := newQueueID;
                   Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Batch was formed as QueueID '+IntToStr(newQueueID));
               end;
            end;
         end;
      end;
      {sends the batched entity}
      Genesys.Model.SIMAN.QueueRemoveEntity(deletedEntity, thisModule.aQueueID);
      Genesys.Model.SIMAN.EntitySendToModuleNumber(batchEntityID, thisModule.NextID[0], 0);
      end
   else begin
       Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Entity waits in the queue ' +thisModule.Name+'.Queue for more '+IntToStr(totalBatchSize-actualBatchSize) +' entities');
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




































































{ Métodos Fixos e Expostação do Método de Acesso }

constructor TNewModuleBatch.Create(novoId: word; novoNome, novoKind: string);
begin
   try
      inherited;
      UserCreate(novoId, novoNome, novoKind);
   except
      Genesys.Model.Trace(1, 'Plugin "' + MODULE_KIND + '" could not create module ' + self.Name);
   end;
end;

procedure TModuleManagerBatch.ReadModule(palavra: TStringList);
var thisModule: TNewModuleBatch;
    newID: word;
 begin
    try
       newID := Genesys.Model.ModuleAdd(MODULE_KIND);
       thisModule := TNewModuleBatch(Genesys.Model.ModuleByID(newID));
       Genesys.AuxFunctions.ReadInitialModule(MODULE_KIND, TModule(thisModule), palavra);
       UserRead(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not read module: ' + thisModule.Name);
   end;
end;

procedure TModuleManagerBatch.SaveModule(generalModule: TModule; var palavra: TStringList);
var thisModule: TNewModuleBatch;
begin
   try
       thisModule := TNewModuleBatch(generalModule);
       Genesys.AuxFunctions.SaveInitialModule(MODULE_KIND, thisModule, palavra);
       UserSave(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not save module: ' + thisModule.Name);
   end;
end;

function TModuleManagerBatch.VerifySymbols(blocoGeral: TModule): string;
var listaVerificacoes: TStringList;
    thisModule: TNewModuleBatch;
begin
   try
      thisModule := TNewModuleBatch(blocoGeral);
      GenesysErrorMessage := '';
      UserVerifySymbols(thisModule, listaVerificacoes);
      result := GenesysErrorMessage;
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not verify symbols of module: ' + thisModule.Name);
   end;
end;

procedure TModuleManagerBatch.Execute(var thisModule: TNewModuleBatch; entidade: word);
begin
   try
      Genesys.Model.TraceSimulation(3, thisModule.ID, entidade, 'Entity arrives at "' +thisModule.Name+ '" module');
      UserExecute(thisModule, entidade);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not execute module: ' + thisModule.Name);
   end;
end;

constructor TModuleManagerBatch.Create;
begin
   inherited Create;
end;



function TModuleManagerBatch.AddModule: TNewModuleBatch;
var newModule: TNewModuleBatch;
begin
   newModule := TNewModuleBatch.Create(0,'', MODULE_KIND);
   result := newModule;
end;

procedure TModuleManagerBatch.ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
var auxStr: string;
    auxBool: boolean;
    ptrBloco: ^TModule;
    ptrStrList: ^TStringList;
    umComponente : TNewModuleBatch;
    umaEntidade : Word;
begin
   try
   if metodo = pmReadModule  then begin
      //in: pointer1: FileName
      ptrStrList := umPonteiro1;
      PlugInBatch.ReadModule(ptrStrList^);
      end
   else if metodo = pmSaveModule then begin
      //in: pointer1: a Module
      //out: TStringList with the attributes'values
      ptrBloco := umPonteiro1;
      ptrStrList := umPonteiro2;
      PlugInBatch.SaveModule(ptrBloco^, ptrStrList^);
      umPonteiro2 := ptrStrList;
      //TStringList(umPonteiro2^) := ptrStrList^;
      end
   else if metodo = pmGetType then begin
      auxStr := MODULE_KIND;
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmGETAUTHOR then begin
      auxStr := MODULE_AUTHOR;
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmGETVERSION then begin
      auxStr := MODULE_VERSION;
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmGETDESCRIP then begin
      auxStr := MODULE_DESCRIPTION;
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmGETDEPENDENCES then begin
      auxStr := MODULE_DEPENDENCES;
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmGETINFOS then begin
      Genesys := TGenesysApplication(umPonteiro1^); //// NEW FOR TEMPLATE 3.1 ////
      auxStr := MODULE_KIND+';'+MODULE_AUTHOR+';'+MODULE_VERSION+';'+MODULE_DESCRIPTION+';';
      if MODULE_IS_SOURCE then auxStr := auxStr+'1;' else auxStr := auxStr+'0;';
      if MODULE_IS_DISPOSE then auxStr := auxStr+'1;' else auxStr := auxStr+'0;';
      if MODULE_IS_VISUAL    then auxStr := auxStr+'1;' else auxStr := auxStr+'0;';
      auxStr := auxStr + MODULE_DEPENDENCES;
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmGetSOURCE then begin
      auxBool := MODULE_IS_SOURCE;
      GetMem(umPonteiro1, SizeOf(auxBool));
      boolean(umPonteiro1^) := auxBool;
      end
   else if metodo = pmGetDRENO then begin
      auxBool := MODULE_IS_DISPOSE;
      GetMem(umPonteiro1, SizeOf(auxBool));
      boolean(umPonteiro1^) := auxBool;
      end
   else if metodo = pmGetVISUAL then begin
      auxBool := MODULE_IS_VISUAL;
      GetMem(umPonteiro1, SizeOf(auxBool));
      boolean(umPonteiro1^) := auxBool;
      end
   else if metodo = pmVERIFYSYMBOLS then begin
      ptrBloco := umPonteiro1;
      auxStr := PlugInBatch.VerifySymbols(ptrBloco^);
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmINCLUDEMODULE then begin
      umComponente := PlugInBatch.AddModule;
      GetMem(umPonteiro1, SizeOf(umComponente));
      TNewModuleBatch(umPonteiro1) := umComponente;
      end
   else if metodo = pmExecute then begin
      umComponente := TNewModuleBatch(umPonteiro1^);
      umaEntidade := Word(umPonteiro2^);
      PlugInBatch.Execute(umComponente,umaEntidade);
      end
   else begin
      auxStr := 'Error: Unknown command';
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
   end;
   except
   end;
end;

procedure GetComponentMethods(umSimulador: TGenesysAppPtr; var exportedMethods: TPlugInAccess);
begin
{$IFDEF IsDllPlugin}
   Genesys := umSimulador;
{$ENDIF}
   exportedMethods := PlugInBatch.ExportedMethodsAccess;
end;

{ Exportação, Inicialização e Finalização}

exports GetComponentMethods;

{Autor: Rafael Luiz Cancian}
{Data:  v1.0:10/03/2002,   v1.1:11/07/2003, ... v: 04/10/2003, 13/03/2004}
       {v3.1: 23/06/2004,  V4.0: 11/03/2005}
begin
   PlugInBatch := TModuleManagerBatch.Create;
end.

finalization
   PlugInBatch.Destroy;
