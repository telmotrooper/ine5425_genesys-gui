{Comment the next line ($UNDEF IsDllPlugin) if you intend to generate a DLL file.}
{Uncomment it to generate a DCU file}
{$UNDEF IsDllPlugin}
{$IFDEF IsDllPlugin}
library ASSIGN;
{$ELSE}
unit ASSIGN;
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
    TNewModuleAssign = Class(TModule)
    private
         {place here the attributes of your new module}
         {Examples:}
         {attribute1: type1;}
         {attribute2: type2;}
         {... YOUR CODE HERE ...}
         aAssignList: TStringList;
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
         property Assignments:TStringList  read  aAssignList  write aAssignList;
      end;

      TModuleManagerAssign = class(TObject)
      private
         function  AddModule: TNewModuleAssign;
         procedure ReadModule(palavra: TStringList);
         procedure SaveModule(generalModule: TModule; var palavra: TStringList);
         procedure Execute(var thisModule: TNewModuleAssign; entidade: word); virtual;
         function  VerifySymbols(blocoGeral: TModule): string;
         procedure UserExecute(var thisModule: TNewModuleAssign; entity: word);
         procedure UserRead(var thisModule: TNewModuleAssign; words: TStringList);
         procedure UserSave(thisModule: TNewModuleAssign; var words: TStringList);
         procedure UserVerifySymbols(thisModule: TNewModuleAssign; var verifyList: TStringList);
      public
         constructor Create;
         procedure ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
      end;

   var
      PlugInAssign : TModuleManagerAssign;
{$IFDEF IsDLLPlugin}
      Genesys: TGenesysAppPtr;
{$ELSE}
implementation
{$ENDIF}

   const
      {fill up the following informations about your new module}
      MODULE_KIND        = 'ASSIGN';                {... YOUR INFOS HERE ...}
      MODULE_AUTHOR      = 'Rafael Luiz Cancian';   {... YOUR INFOS HERE ...}
      MODULE_VERSION     = '1.1.0 in 15/03/2005';   {... YOUR INFOS HERE ...}
      MODULE_DESCRIPTION = 'Assign statements';     {... YOUR INFOS HERE ...}
      MODULE_IS_VISUAL   = true;                    {... YOUR INFOS HERE ...}
      MODULE_IS_SOURCE   = false;                   {... YOUR INFOS HERE ...}
      MODULE_IS_DISPOSE  = false;                   {... YOUR INFOS HERE ...}
      MODULE_DEPENDENCES = '';                      {... YOUR INFOS HERE ...}
      {example:  MODULE_DEPENDENCES = 'assign.dll;batch.dll' }


procedure TNewModuleAssign.UserCreate(novoId: word; novoNome, novoKind: string);
begin
   {initialize here the necessary attributes of your new module}
   {Examples:}
   {attribute1 := '';}
   {attribute2 := 0;}
   {... YOUR CODE HERE ...}
   aAssignList := TStringList.Create;
   aAssignList.Sorted := false;
end;

procedure TModuleManagerAssign.UserRead(var thisModule:TNewModuleAssign; words:TStringList);
var i: integer;
begin
    {Place here the code for reading the attributes of your new component}
    {The values readed from the model file are in the "words.Strings[]" vector}
    {Examples:}
    {thisModule.attribute1 := words.Strings[0];}
    {thisModule.attribute2 := StrToInt(words.Strings[1]);}
    {... YOUR CODE HERE ...}
    i := 0;
    while i < words.Count do begin
       thisModule.aAssignList.Add(words.Strings[i]);
       i := i + 1;
    end;
end;

procedure TModuleManagerAssign.UserSave(thisModule:TNewModuleAssign; var words: TStringList);
var i: integer;
begin
    {Place here the code for saving the attributes of your new component}
    {The values to be saved in the model file need to be added to the "words" list}
    {Examples:}
    {words.Add(thisModule.attribute1);}
    {words.Add(IntToStr(thisModule.attribute2));}
    {... YOUR CODE HERE ...}
    for i := 0 to thisModule.aAssignList.Count-1 do begin
       words.Add(thisModule.aAssignList.Strings[i]);
    end;
end;

procedure TModuleManagerAssign.UserVerifySymbols(thisModule:TNewModuleAssign; var verifyList:TStringList);
var i, pos: integer;
    text, res, expr: string;
begin
   {Place here the list of string attributes that parses to expression, attributes,}
   {variables, etc and need to be evaluated - just like "int(Norm(3,1))+Entity.JobStep"}
   {Place that as a list of calls to the "VerifySymbol" procedure, as shown bellow:}
   {VerifySymbol(moduleName, description, expression, resultType, mandatory}
   {Examples:}
   {VerifySymbol(thisModule.Name, 'The first attribute', thisModule.Attribute1, cEXPRESSION, true);}
   {... YOUR CODE HERE ...}
   for i := 0 to thisModule.aAssignList.Count-1 do begin
      text := thisModule.aAssignList.Strings[i];
      pos := Genesys.AuxFunctions.StrPos(text,'=');
      if pos = 0 then
         //error
      else begin
         res  := Trim(Genesys.AuxFunctions.StrLeft(text,pos-1));
         expr := trim(Genesys.AuxFunctions.StrRight(text, Genesys.AuxFunctions.StrLenght(text)-pos));
         Genesys.AuxFunctions.VerifySymbol(thisModule.aName, 'Assignment', expr, cEXPRESSION, true);
         {FALTA VERIFICAR RES. PODE SER ATRIBUTO, VARIÁVEL, ETC.}
         if GenesysErrorMessage = '' then begin
            Genesys.AuxFunctions.VerifySymbol(thisModule.aName, 'Assignment', res, cATTRIBUTE, false);
            if GenesysErrorMessage <> '' then begin
               {não era um atributo. tenta verificar se é uma variável}
               GenesysErrorMessage := '';
               Genesys.AuxFunctions.VerifySymbol(thisModule.aName, 'Assignment', res, cVARIABLE, false);
               if GenesysErrorMessage <> '' then begin
                  {não era uma variável. o que ainda pode ser?}
               end;
            end;
         end;
      end;
   end;
end;

procedure TModuleManagerAssign.UserExecute(var thisModule:TNewModuleAssign; entity:word);
var i, ind, pos: integer;
    text, res, valname, expr: string;
    value: double;
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
   for i := 0 to thisModule.aAssignList.Count-1 do begin
      text := thisModule.aAssignList.Strings[i];
      pos := Genesys.AuxFunctions.StrPos(text,'=');
      if pos = 0 then
         Genesys.Model.Trace(cTLError,'Error: Illegal Assignment: "' + text + '"')
      else begin
         res  := Trim(Genesys.AuxFunctions.StrLeft(text,pos-1));
         expr := Genesys.AuxFunctions.StrRight(text, Genesys.AuxFunctions.StrLenght(text)-pos);
         value := Genesys.Model.SIMAN.StringEvaluateFormula(expr);
         ind := Genesys.Model.SIMAN.AttributeIndex(res);
         if ind >= 0 then begin
            {it is an attribute}
            Genesys.Model.SIMAN.AttributeValue[res] := value;  {assigns the attribute}
            Genesys.Model.TraceSimulation(cTLModuleIntern,thisModule.ID,entity,'Assigning '+FloatToStr(value) + ' to attribute "'+res+'"');
         end else begin
            pos := Genesys.AuxFunctions.StrPos(res,'[');
            if pos = 0 then
               valname := res
            else
               valname := Genesys.AuxFunctions.StrLeft(res,pos-1);   {removes indexes of array variable}
            ind := Genesys.Model.SIMAN.VariableIndex(valname);
            if ind >=0 then begin
               {it is an variable}
               if pos = 0 then begin
                   Genesys.Model.SIMAN.VariableValue[ind,1,1] := value;
                   Genesys.Model.TraceSimulation(cTLModuleIntern,thisModule.ID,entity,'Assigning '+FloatToStr(value) + ' to variable "'+res+'"');
               end else begin
                  {array or matrix variable}
                  if Genesys.AuxFunctions.StrRight(res,1) <> ']' then
                     //erro de sintaxe
                     Genesys.Model.Trace(cTLError,'Illegal Assignment: "' + text + '"')
                  else begin
                     //atribuir ao vetor ou matriz
                  end;
               end;
            end;
         end;
      end;
   end;
   Genesys.Model.SIMAN.EntitySendToModuleNumber(entity, thisModule.NextID[0], 0);
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

constructor TNewModuleAssign.Create(novoId: word; novoNome, novoKind: string);
begin
   try
      inherited;
      UserCreate(novoId, novoNome, novoKind);
   except
      Genesys.Model.Trace(1, 'Plugin "' + MODULE_KIND + '" could not create module ' + self.Name);
   end;
end;

procedure TModuleManagerAssign.ReadModule(palavra: TStringList);
var thisModule: TNewModuleAssign;
    newID: word;
 begin
    try
       newID := Genesys.Model.ModuleAdd(MODULE_KIND);
       thisModule := TNewModuleAssign(Genesys.Model.ModuleByID(newID));
       Genesys.AuxFunctions.ReadInitialModule(MODULE_KIND, TModule(thisModule), palavra);
       UserRead(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not read module: ' + thisModule.Name);
   end;
end;

procedure TModuleManagerAssign.SaveModule(generalModule: TModule; var palavra: TStringList);
var thisModule: TNewModuleAssign;
begin
   try
       thisModule := TNewModuleAssign(generalModule);
       Genesys.AuxFunctions.SaveInitialModule(MODULE_KIND, thisModule, palavra);
       UserSave(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not save module: ' + thisModule.Name);
   end;
end;

function TModuleManagerAssign.VerifySymbols(blocoGeral: TModule): string;
var listaVerificacoes: TStringList;
    thisModule: TNewModuleAssign;
begin
   try
      thisModule := TNewModuleAssign(blocoGeral);
      GenesysErrorMessage := '';
      UserVerifySymbols(thisModule, listaVerificacoes);
      result := GenesysErrorMessage;
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not verify symbols of module: ' + thisModule.Name);
   end;
end;

procedure TModuleManagerAssign.Execute(var thisModule: TNewModuleAssign; entidade: word);
begin
   try
      Genesys.Model.TraceSimulation(3, thisModule.ID, entidade, 'Entity arrives at "' +thisModule.Name+ '" module');
      UserExecute(thisModule, entidade);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not execute module: ' + thisModule.Name);
   end;
end;

constructor TModuleManagerAssign.Create;
begin
   inherited Create;
end;



function TModuleManagerAssign.AddModule: TNewModuleAssign;
var newModule: TNewModuleAssign;
begin
   newModule := TNewModuleAssign.Create(0,'', MODULE_KIND);
   result := newModule;
end;

procedure TModuleManagerAssign.ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
var auxStr: string;
    auxBool: boolean;
    ptrBloco: ^TModule;
    ptrStrList: ^TStringList;
    umComponente : TNewModuleAssign;
    umaEntidade : Word;
begin
   try
   if metodo = pmReadModule  then begin
      //in: pointer1: FileName
      ptrStrList := umPonteiro1;
      PlugInAssign.ReadModule(ptrStrList^);
      end
   else if metodo = pmSaveModule then begin
      //in: pointer1: a Module
      //out: TStringList with the attributes'values
      ptrBloco := umPonteiro1;
      ptrStrList := umPonteiro2;
      PlugInAssign.SaveModule(ptrBloco^, ptrStrList^);
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
      auxStr := PlugInAssign.VerifySymbols(ptrBloco^);
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmINCLUDEMODULE then begin
      umComponente := PlugInAssign.AddModule;
      GetMem(umPonteiro1, SizeOf(umComponente));
      TNewModuleAssign(umPonteiro1) := umComponente;
      end
   else if metodo = pmExecute then begin
      umComponente := TNewModuleAssign(umPonteiro1^);
      umaEntidade := Word(umPonteiro2^);
      PlugInAssign.Execute(umComponente,umaEntidade);
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
   exportedMethods := PlugInAssign.ExportedMethodsAccess;
end;

{ Exportação, Inicialização e Finalização}

exports GetComponentMethods;

{Autor: Rafael Luiz Cancian}
{Data:  v1.0:10/03/2002,   v1.1:11/07/2003, ... v: 04/10/2003, 13/03/2004}
       {v3.1: 23/06/2004,  V4.0: 11/03/2005}
begin
   PlugInAssign := TModuleManagerAssign.Create;
end.

finalization
   PlugInAssign.Destroy;
