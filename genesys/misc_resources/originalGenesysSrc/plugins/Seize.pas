{Comment the next line ($UNDEF IsDllPlugin) if you intend to generate a DLL file.}
{Uncomment it to generate a DCU file}
{$UNDEF IsDllPlugin}
{$IFDEF IsDllPlugin}
library SEIZE;
{$ELSE}
unit SEIZE;
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
    TResourceType = (rtSET, rtRESOURCE);
    TResourceRule = (rrRANDOM, rrCICLICAL, rrESPECIFIC, rrSMALLESTBUSY, rrLARGESTREMAININGCAPACITY);
    TNewModuleSeize = Class(TModule)
    private
         {place here the attributes of your new module}
         {Examples:}
         {attribute1: type1;}
         {attribute2: type2;}
         {... YOUR CODE HERE ...}
         aAllocationType: byte;
         aPriority: byte;
         aResourceType: TResourceType;
         aResourceName: string;
         aQuantity: string;
         aRule: TResourceRule;
         aSaveAttribute: string;
         aLastMemberSeized: integer;
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
         property AllocationType:byte         read aAllocationType write aAllocationType;
         property Priority:byte               read aPriority       write aPriority;
         property ResourceType: TResourceType read aResourceType   write aResourceType;
      end;

      TModuleManagerSeize = class(TObject)
      private
         function  AddModule: TNewModuleSeize;
         procedure ReadModule(palavra: TStringList);
         procedure SaveModule(generalModule: TModule; var palavra: TStringList);
         procedure Execute(var thisModule: TNewModuleSeize; entidade: word); virtual;
         function  VerifySymbols(blocoGeral: TModule): string;
         procedure UserExecute(var thisModule: TNewModuleSeize; entity: word);
         procedure UserRead(var thisModule: TNewModuleSeize; words: TStringList);
         procedure UserSave(thisModule: TNewModuleSeize; var words: TStringList);
         procedure UserVerifySymbols(thisModule: TNewModuleSeize; var verifyList: TStringList);
      public
         constructor Create;
         procedure ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
      end;

   var
      PlugInSeize : TModuleManagerSeize;
{$IFDEF IsDLLPlugin}
      Genesys: TGenesysAppPtr;
{$ELSE}
implementation
{$ENDIF}

   const
      {fill up the following informations about your new module}
      MODULE_KIND        = 'SEIZE';                 {... YOUR INFOS HERE ...}
      MODULE_AUTHOR      = 'Rafael Luiz Cancian';   {... YOUR INFOS HERE ...}
      MODULE_VERSION     = '1.1.0 in 15/03/2005';   {... YOUR INFOS HERE ...}
      MODULE_DESCRIPTION = 'Alocates a resource';   {... YOUR INFOS HERE ...}
      MODULE_IS_VISUAL   = true;                    {... YOUR INFOS HERE ...}
      MODULE_IS_SOURCE   = false;                   {... YOUR INFOS HERE ...}
      MODULE_IS_DISPOSE  = false;                   {... YOUR INFOS HERE ...}
      MODULE_DEPENDENCES = '';                      {... YOUR INFOS HERE ...}
      {example:  MODULE_DEPENDENCES = 'assign.dll;batch.dll' }


procedure TNewModuleSeize.UserCreate(novoId: word; novoNome, novoKind: string);
begin
   {initialize here the necessary attributes of your new module}
   {Examples:}
   {attribute1 := '';}
   {attribute2 := 0;}
   {... YOUR CODE HERE ...}
   aAllocationType := 0;
   aPriority := 0;
   aResourceType := rtRESOURCE;
   aResourceName := '';
   aQuantity := '1';
   aRule := rrRANDOM;
   aSaveAttribute := '';
   aLastMemberSeized := -1;
end;

procedure TModuleManagerSeize.UserRead(var thisModule:TNewModuleSeize; words:TStringList);
begin
    {Place here the code for reading the attributes of your new component}
    {The values readed from the model file are in the "words.Strings[]" vector}
    {Examples:}
    {thisModule.attribute1 := words.Strings[0];}
    {thisModule.attribute2 := StrToInt(words.Strings[1]);}
    {... YOUR CODE HERE ...}
    thisModule.aAllocationType := StrToInt(words.Strings[0]);
    thisModule.aPriority := StrToInt(words.Strings[1]);
    if StrToInt(words.Strings[2]) = 0 then  {0 = set ; <>0 = resource}
       thisModule.aResourceType := rtSET
    else
       thisModule.aResourceType := rtRESOURCE;
    thisModule.aResourceName := Genesys.AuxFunctions.Underscore(words.Strings[3]);
    thisModule.aQuantity := words.Strings[4];
    case StrToInt(words.Strings[5]) of
       0: thisModule.aRule := rrRANDOM;
       1: thisModule.aRule := rrCICLICAL;
       2: thisModule.aRule := rrESPECIFIC;
       3: thisModule.aRule := rrSMALLESTBUSY;
       4: thisModule.aRule := rrLARGESTREMAININGCAPACITY;
    end;
    thisModule.aSaveAttribute := Genesys.AuxFunctions.Underscore(words.Strings[6]);
end;

procedure TModuleManagerSeize.UserSave(thisModule:TNewModuleSeize; var words: TStringList);
begin
    {Place here the code for saving the attributes of your new component}
    {The values to be saved in the model file need to be added to the "words" list}
    {Examples:}
    {words.Add(thisModule.attribute1);}
    {words.Add(IntToStr(thisModule.attribute2));}
    {... YOUR CODE HERE ...}
    words.Add(IntToStr(thisModule.aAllocationType));
    words.Add(IntToStr(thisModule.aPriority));
    if thisModule.aResourceType = rtSET then
       words.Add('0')
    else
       words.Add('1');
    words.Add(thisModule.aResourceName);
    words.Add(thisModule.aQuantity);
    if thisModule.aRule = rrRANDOM then words.Add('0')
    else if thisModule.aRule = rrCICLICAL then words.Add('1')
    else if thisModule.aRule = rrESPECIFIC then words.Add('2')
    else if thisModule.aRule = rrSMALLESTBUSY then words.Add('3')
    else if thisModule.aRule = rrLARGESTREMAININGCAPACITY then words.Add('4');
    words.Add(thisModule.aSaveAttribute);
end;

procedure TModuleManagerSeize.UserVerifySymbols(thisModule:TNewModuleSeize; var verifyList:TStringList);
begin
   {Place here the list of string attributes that parses to expression, attributes,}
   {variables, etc and need to be evaluated - just like "int(Norm(3,1))+Entity.JobStep"}
   {Place that as a list of calls to the "VerifySymbol" procedure, as shown bellow:}
   {VerifySymbol(moduleName, description, expression, resultType, mandatory}
   {Examples:}
   {VerifySymbol(thisModule.Name, 'The first attribute', thisModule.Attribute1, cEXPRESSION, true);}
   {... YOUR CODE HERE ...}
   if thisModule.aResourceType = rtSET then
      Genesys.AuxFunctions.VerifySymbol(thismodule.Name, 'Resource Set Name', thisModule.aResourceName, cSET, true)
   else
      Genesys.AuxFunctions.VerifySymbol(thismodule.Name, 'Resource Name', thisModule.aResourceName, cRESOURCE, true);
   Genesys.AuxFunctions.VerifySymbol(thismodule.Name, 'Quantity', thisModule.aQuantity, cEXPRESSION, true);
   Genesys.AuxFunctions.VerifySymbol(thismodule.Name, 'Save Attribute', thisModule.aSaveAttribute, cATTRIBUTE, thisModule.aResourceType = rtSET);
end;

procedure TModuleManagerSeize.UserExecute(var thisModule:TNewModuleSeize; entity:word);
var nomeRecurso: string;
    i: integer;
    umRecurso: TResource;
    umaFila: TQUEUE;
    setID, recID: word;
    memberIndex: integer;
    esperandoRec: TWaitingResource;
    umaQuantidade: word;
    minBusy, minIndex: integer;
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
   if thisModule.aResourceType = rtSET then begin
      //pega o nome do recurso no set, conforme a regra estabelecida
      // TResourceRule = (rrRANDOM, rrCICLICAL, rrESPECIFIC, rrSMALLESTBUSY);
      setID := Genesys.Model.SIMAN.SetIndex(thisModule.aResourceName);
      setID := Genesys.Model.SIMAN.SetNumber[setID];
      case thisModule.aRule of
         rrRandom: begin
            memberIndex := trunc(random * Genesys.Model.SIMAN.SetMemberCount(setID));
         end;
         rrCiclical: begin
            thisModule.aLastMemberSeized := thisModule.aLastMemberSeized + 1;
            if (thisModule.aLastMemberSeized) >= Genesys.Model.SIMAN.SetMemberCount(setID) then
               thisModule.aLastMemberSeized := 0;
            memberIndex := thisModule.aLastMemberSeized;
         end;
         rrEspecific: begin
            memberIndex := trunc(Genesys.Model.SIMAN.StringEvaluateFormula(thisModule.aSaveAttribute));
         end;
         rrSmallestBusy: begin
            minBusy := 32535;
            for i := 0 to Genesys.Model.SIMAN.SetMemberCount(setID)-1 do begin
               nomeRecurso := Genesys.Model.SIMAN.SetMemberName(setID, i);
               recID := Genesys.Model.SIMAN.ResourceIndex(nomeRecurso);
               umaQuantidade := Genesys.Model.SIMAN.Resource[recID].NumberBusy;
               if umaQuantidade < minBusy then begin
                  minBusy := umaQuantidade;
                  minIndex := i;
               end;
            end;
            memberIndex := minIndex;
         end;
         rrLARGESTREMAININGCAPACITY: begin
            minBusy := 0; {max remainging capacity}
            for i := 0 to Genesys.Model.SIMAN.SetMemberCount(setID)-1 do begin
               nomeRecurso := Genesys.Model.SIMAN.SetMemberName(setID, i);
               recID := Genesys.Model.SIMAN.ResourceIndex(nomeRecurso);
               umaQuantidade := Genesys.Model.SIMAN.Resource[recID].Capacity - Genesys.Model.SIMAN.Resource[recID].NumberBusy;
               if umaQuantidade > minBusy then begin
                  minBusy := umaQuantidade;
                  minIndex := i;
               end;
            end;
            memberIndex := minIndex;
         end;
      end;
      if (thisModule.aSaveAttribute <> '') and (thisModule.aRule <> rrEspecific) then begin
         minIndex := Genesys.Model.SIMAN.AttributeIndex(thisModule.aSaveAttribute);
         Genesys.Model.SIMAN.EntityAttribute[entity,minIndex] := memberIndex;
      end;
      nomeRecurso := Genesys.Model.SIMAN.SetMemberName(setID, memberIndex);
      Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Choosing member '+IntToStr(memberIndex)+' ('+nomeRecurso+') from set "'+thisModule.aResourceName+'"');
   end else begin
      nomeRecurso := thisModule.aResourceName;
   end;
   i := Genesys.Model.SIMAN.ResourceIndex(nomeRecurso);
   if i >=0 then begin
      umRecurso := Genesys.Model.SIMAN.Resource[i];
      umaQuantidade := Trunc(Genesys.Model.SIMAN.StringEvaluateFormula(thisModule.aQuantity));
      if (umRecurso.Capacity - umRecurso.NumberBusy) < umaQuantidade then begin
         //não há instâncias livres suficientes. Coloca a entidade esperando na fila
         esperandoRec := TWaitingResource.Create(entity, thisModule.ID, umaQuantidade);
         Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Entity will be waiting for resource "' +thisModule.aResourceName+ '" at queue "' + umRecurso.QueueName + '"');
         i := Genesys.Model.SIMAN.QueueIndex(umRecurso.QueueName);
         if i >= 0 then begin
            umaFila := Genesys.Model.SIMAN.Queue[i];
            umaFila.InsertElement(esperandoRec);
         end else begin
            Genesys.Model.Trace(cTLError, 'Error: Queue "' + umRecurso.QueueName + '" not found');
         end;
      end else begin
         //há instâncias livres suficientes. Marca a alocação e envia a entidade adiante
         Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, entity, 'Entity seizes ' +IntToStr(umaQuantidade)+ ' units of resource "' +thisModule.aResourceName+ '"');
         umRecurso.Seize(umaQuantidade);
         {envia adiante}
         Genesys.Model.SIMAN.EntitySendToModuleNumber(entity, thisModule.NextID[0], 0);
      end;
   end else begin
      Genesys.Model.Trace(cTLError, 'Error: Resource "' + nomeRecurso + '" not found');
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
{              INVOQUE THE METHOD GENESYS.PLUGINADD                            }
{                                                                              }
{******************************************************************************}
{******************************************************************************}




































































{ Métodos Fixos e Expostação do Método de Acesso }

constructor TNewModuleSeize.Create(novoId: word; novoNome, novoKind: string);
begin
   try
      inherited;
      UserCreate(novoId, novoNome, novoKind);
   except
      Genesys.Model.Trace(1, 'Plugin "' + MODULE_KIND + '" could not create module ' + self.Name);
   end;
end;

procedure TModuleManagerSeize.ReadModule(palavra: TStringList);
var thisModule: TNewModuleSeize;
    newID: word;
 begin
    try
       newID := Genesys.Model.ModuleAdd(MODULE_KIND);
       thisModule := TNewModuleSeize(Genesys.Model.ModuleByID(newID));
       Genesys.AuxFunctions.ReadInitialModule(MODULE_KIND, TModule(thisModule), palavra);
       UserRead(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not read module: ' + thisModule.Name);
   end;
end;

procedure TModuleManagerSeize.SaveModule(generalModule: TModule; var palavra: TStringList);
var thisModule: TNewModuleSeize;
begin
   try
       thisModule := TNewModuleSeize(generalModule);
       Genesys.AuxFunctions.SaveInitialModule(MODULE_KIND, thisModule, palavra);
       UserSave(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not save module: ' + thisModule.Name);
   end;
end;

function TModuleManagerSeize.VerifySymbols(blocoGeral: TModule): string;
var listaVerificacoes: TStringList;
    thisModule: TNewModuleSeize;
begin
   try
      thisModule := TNewModuleSeize(blocoGeral);
      GenesysErrorMessage := '';
      UserVerifySymbols(thisModule, listaVerificacoes);
      result := GenesysErrorMessage;
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not verify symbols of module: ' + thisModule.Name);
   end;
end;

procedure TModuleManagerSeize.Execute(var thisModule: TNewModuleSeize; entidade: word);
begin
   try
      Genesys.Model.TraceSimulation(3, thisModule.ID, entidade, 'Entity arrives at "' +thisModule.Name+ '" module');
      UserExecute(thisModule, entidade);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not execute module: ' + thisModule.Name);
   end;
end;

constructor TModuleManagerSeize.Create;
begin
   inherited Create;
end;



function TModuleManagerSeize.AddModule: TNewModuleSeize;
var newModule: TNewModuleSeize;
begin
   newModule := TNewModuleSeize.Create(0,'', MODULE_KIND);
   result := newModule;
end;

procedure TModuleManagerSeize.ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
var auxStr: string;
    auxBool: boolean;
    ptrBloco: ^TModule;
    ptrStrList: ^TStringList;
    umComponente : TNewModuleSeize;
    umaEntidade : Word;
begin
   try
   if metodo = pmReadModule  then begin
      //in: pointer1: FileName
      ptrStrList := umPonteiro1;
      PlugInSeize.ReadModule(ptrStrList^);
      end
   else if metodo = pmSaveModule then begin
      //in: pointer1: a Module
      //out: TStringList with the attributes'values
      ptrBloco := umPonteiro1;
      ptrStrList := umPonteiro2;
      PlugInSeize.SaveModule(ptrBloco^, ptrStrList^);
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
      auxStr := PlugInSeize.VerifySymbols(ptrBloco^);
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmINCLUDEMODULE then begin
      umComponente := PlugInSeize.AddModule;
      GetMem(umPonteiro1, SizeOf(umComponente));
      TNewModuleSeize(umPonteiro1) := umComponente;
      end
   else if metodo = pmExecute then begin
      umComponente := TNewModuleSeize(umPonteiro1^);
      umaEntidade := Word(umPonteiro2^);
      PlugInSeize.Execute(umComponente,umaEntidade);
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
   exportedMethods := PlugInSeize.ExportedMethodsAccess;
end;

{ Exportação, Inicialização e Finalização}

exports GetComponentMethods;

{Autor: Rafael Luiz Cancian}
{Data:  v1.0:10/03/2002,   v1.1:11/07/2003, ... v: 04/10/2003, 13/03/2004}
       {v3.1: 23/06/2004,  V4.0: 11/03/2005}
begin
   PlugInSeize := TModuleManagerSeize.Create;
end.

finalization
   PlugInSeize.Destroy;
