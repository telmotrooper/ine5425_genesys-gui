{Comment the next line ($UNDEF IsDllPlugin) if you intend to generate a DLL file.}
{Uncomment it to generate a DCU file}
{$UNDEF IsDllPlugin}
{$IFDEF IsDllPlugin}
library COMPILER;
{$ELSE}
unit COMPILER;
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
    TNewModuleCompiler = Class(TModule)
    private
         {place here the attributes of your new module}
         {Examples:}
         {attribute1: type1;}
         {attribute2: type2;}
         {... YOUR CODE HERE ...}
         aFileName,
         aOutputDir: string;
         aMessages: TStringList;
         aDLL: integer;
         aMethodName:string;
         //aGenesysEventHandler: TGenesysEventHandler;
         {place here the methods of your new module}
         {Examples:}
         {procedure Methode1;}
         {function Methode2(param1:type1);}
         {... YOUR CODE HERE ...}

          procedure UserCreate(novoId: word; novoNome, novoKind: string);
      public
         constructor Create(novoId: word; novoNome, novoKind: string); override;
         destructor UserDestroy;
      published
         {place in this region the property of this module that can be edit by the user}
         {Examples:}
         {property MyProperty1:type1  read attribute1  write attribute1;}
         {property MyProperty2:type2  read attribute2  write attribute2;}
         {... YOUR CODE HERE ...}
         property MethodToExecute:string             write aMethodName;
         //property GenesysEventHandler:TGenesysEventHandler   read  aGenesysEventHandler;
      end;

      TModuleManagerCompiler = class(TObject)
      private
         function  AddModule: TNewModuleCompiler;
         procedure ReadModule(palavra: TStringList);
         procedure SaveModule(generalModule: TModule; var palavra: TStringList);
         function Execute(var thisModule: TNewModuleCompiler; umMetodo:string): TGenesysEventHandler; virtual; ////umMetodo:string); virtual; ////entidade: word); virtual;
         function  VerifySymbols(blocoGeral: TModule): string;
         function UserExecute(var thisModule: TNewModuleCompiler; umMetodo:string): TGenesysEventHandler; ////umMetodo:string);////entity: word);
         procedure UserRead(var thisModule: TNewModuleCompiler; words: TStringList);
         procedure UserSave(thisModule: TNewModuleCompiler; var words: TStringList);
         procedure UserVerifySymbols(thisModule: TNewModuleCompiler; var verifyList: TStringList);
         {Extra Method needed}
         {... YOUR CODE HERE ...}
         procedure CompileAndSet(var thisModule: TNewModuleCompiler);
      public
         constructor Create;
         procedure ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
      end;

   var
      PlugInCompiler : TModuleManagerCompiler;
{$IFDEF IsDLLPlugin}
      Genesys: TGenesysAppPtr;
{$ELSE}
implementation
{$ENDIF}

   uses windows, uDelphiCompiler, TypInfo;


   const
      {fill up the following informations about your new module}
      MODULE_KIND        = 'COMPILER';              {... YOUR INFOS HERE ...}
      MODULE_AUTHOR      = 'Thiago Flessak / Rafael Luiz Cancian';   {... YOUR INFOS HERE ...}
      MODULE_VERSION     = '2.2.2 in 15/05/2005';   {... YOUR INFOS HERE ...}
      MODULE_DESCRIPTION = 'Compiles Delphi Source Code';    {... YOUR INFOS HERE ...}
      MODULE_IS_VISUAL   = false;                   {... YOUR INFOS HERE ...}
      MODULE_IS_SOURCE   = false;                   {... YOUR INFOS HERE ...}
      MODULE_IS_DISPOSE  = false;                   {... YOUR INFOS HERE ...}
      MODULE_DEPENDENCES = '';                      {... YOUR INFOS HERE ...}
      {example:  MODULE_DEPENDENCES = 'assign.dll;batch.dll' }


destructor TNewModuleCompiler.UserDestroy;
begin
   if aDLL <> 0 then
      FreeLibrary(aDLL);
   inherited;
end;

procedure TNewModuleCompiler.UserCreate(novoId: word; novoNome, novoKind: string);
begin
   {initialize here the necessary attributes of your new module}
   {Examples:}
   {attribute1 := '';}
   {attribute2 := 0;}
   {... YOUR CODE HERE ...}
   aFileName  := Genesys.Model.Path + Copy(Genesys.Model.FileName, 1, Pos('.', Genesys.Model.FileName)-1) + '.pas';
   aOutputDir := Genesys.Model.Path;
   aMessages := TStringList.Create;
   aMessages.Sorted := false;
end;

procedure TModuleManagerCompiler.UserRead(var thisModule:TNewModuleCompiler; words:TStringList);
begin
    {Place here the code for reading the attributes of your new component}
    {The values readed from the model file are in the "words.Strings[]" vector}
    {Examples:}
    {thisModule.attribute1 := words.Strings[0];}
    {thisModule.attribute2 := StrToInt(words.Strings[1]);}
    {... YOUR CODE HERE ...}
    CompileAndSet(thisModule);
end;

procedure TModuleManagerCompiler.UserSave(thisModule:TNewModuleCompiler; var words: TStringList);
begin
    {Place here the code for saving the attributes of your new component}
    {The values to be saved in the model file need to be added to the "words" list}
    {Examples:}
    {words.Add(thisModule.attribute1);}
    {words.Add(IntToStr(thisModule.attribute2));}
    {... YOUR CODE HERE ...}

end;

procedure TModuleManagerCompiler.UserVerifySymbols(thisModule:TNewModuleCompiler; var verifyList:TStringList);
begin
   {Place here the list of string attributes that parses to expression, attributes,}
   {variables, etc and need to be evaluated - just like "int(Norm(3,1))+Entity.JobStep"}
   {Place that as a list of calls to the "VerifySymbol" procedure, as shown bellow:}
   {Genesys.AuxFunctions.VerifySymbol(moduleName, description, expression, resultType, mandatory}
   {Examples:}
   {Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'The first attribute', thisModule.Attribute1, cEXPRESSION, true);}
   {... YOUR CODE HERE ...}

end;

function TModuleManagerCompiler.UserExecute(var thisModule:TNewModuleCompiler; umMetodo:string): TGenesysEventHandler;////umMetodo:string);//entity:word);
var
   umEvento: TGenesysEventHandler;
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
   if (umMetodo <> '') and (thisModule.aDLL = 0) then begin
      Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, 0, 'Compiling Delphi code');
      CompileAndSet(thisModule);
   end;
   if (umMetodo <> '') and (thisModule.aDLL <> 0) then begin
//      Genesys.Model.TraceSimulation(cTLModuleIntern, thisModule.ID, 0, 'Executing the compiled code');
      @umEvento := GetProcAddress(thisModule.aDLL, PChar(umMetodo));
      result := umEvento;
//      umEvento;
//      GetMem(pointer2, SizeOf(TGenesysEventHandler));
//      pointer2 := GetProcAddress(thisModule.aDLL, PChar(umMetodo));
   end else begin
   end;
end;

procedure TModuleManagerCompiler.CompileAndSet(var thisModule: TNewModuleCompiler);
var DelphiCompiler: TDelphiCompiler;
    nomeDLL, nomeMetodo: string;
    PropList: PPropList;
    PropCount, i: integer;
    PropInfo: PPropInfo;
    umMetodo: TGenesysEventHandler;
    SetGenesysPointer: procedure(umPonteiro: TGenesysAppPtr);
begin
   try
      if thisModule.aDLL <> 0 then
         FreeLibrary(thisModule.aDLL);
      if (FileExists(thisModule.aFileName)) then begin
         DelphiCompiler := TDelphiCompiler.Create;
         DelphiCompiler.OutPutDir := thisModule.aOutputDir;
         if DelphiCompiler.Execute(thisModule.aFileName) then begin
            Genesys.Model.Trace(cTLModuleIntern, 'Delphi compiler was sucessfully called');
            thisModule.aMessages := DelphiCompiler.Messages;
            nomeDLL := ExtractFileName(thisModule.aFileName);
            if thisModule.aOutputDir[Length(thisModule.aOutputDir)] <> '\' then
               nomeDLL := thisModule.aOutputDir + '\' + Copy(nomeDLL, 1, Pos('.', nomeDLL)-1) + '.dll'
            else
               nomeDLL := thisModule.aOutputDir + Copy(nomeDLL, 1, Pos('.', nomeDLL)-1) + '.dll';
            thisModule.aDLL := LoadLibrary(PChar(nomeDLL));
            if thisModule.aDLL <> 0 then begin
               Genesys.Model.Trace(cTLModuleIntern, 'Compiled Delphi code was sucessfully loaded');
               // Passa o ponteiro do Genesys para a DLL
               @SetGenesysPointer := GetProcAddress(thisModule.aDLL, 'SetGenesysPointer');
               if @SetGenesysPointer <> nil then begin
                  SetGenesysPointer(@Genesys);
                  // Pega os eventos disponivel pelo modelo e atribui ao seu metodo referente a DLL
                  PropCount := GetPropList(Genesys.Model.ClassInfo, [tkMethod], nil);
                  GetMem(PropList, PropCount * SizeOf(PPropInfo));
                  GetPropList(Genesys.Model.ClassInfo, [tkMethod], PropList);
                  for i := 0 to PropCount - 1 do begin
                     if Copy(PropList[i].Name, 1, 2) = 'On' then begin
                        nomeMetodo := PropList[i].Name;
                        @umMetodo := GetProcAddress(thisModule.aDLL, PChar('ModelLogic_'+nomeMetodo));
                        PropInfo := GetPropInfo(Genesys.Model, nomeMetodo);
                        SetMethodProp(Genesys.Model, nomeMetodo, TMethod(umMetodo));
                     end;
                  end;
               end else begin
               Genesys.Model.Trace(cTLError, 'Error: Could not get Genesys pointer');
               end;
            end else begin
               Genesys.Model.Trace(cTLError, 'Error: Could not load compiled Delphi code');
            end;
         end else begin
            Genesys.Model.Trace(cTLError, 'Error: Could not compile Source Code');
         end;
         DelphiCompiler.Destroy;
      end else begin
         Genesys.Model.Trace(cTLError, 'Error: Could not compile Source Code: '+QuotedStr(thisModule.aFileName)+' file not found');
      end;
   except
      Genesys.Model.Trace(cTLError, 'Error: Plugin "' + MODULE_KIND + '" could not compile source code of module: ' + thisModule.Name);
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

constructor TNewModuleCompiler.Create(novoId: word; novoNome, novoKind: string);
begin
   try
      inherited;
      UserCreate(novoId, novoNome, novoKind);
   except
      Genesys.Model.Trace(1, 'Plugin "' + MODULE_KIND + '" could not create module ' + self.Name);
   end;
end;

procedure TModuleManagerCompiler.ReadModule(palavra: TStringList);
var thisModule: TNewModuleCompiler;
    newID: word;
 begin
    try
       newID := Genesys.Model.ModuleAdd(MODULE_KIND);
       thisModule := TNewModuleCompiler(Genesys.Model.ModuleByID(newID));
       Genesys.AuxFunctions.ReadInitialModule(MODULE_KIND, TModule(thisModule), palavra);
       UserRead(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not read module: ' + thisModule.Name);
   end;
end;

procedure TModuleManagerCompiler.SaveModule(generalModule: TModule; var palavra: TStringList);
var thisModule: TNewModuleCompiler;
begin
   try
       thisModule := TNewModuleCompiler(generalModule);
       Genesys.AuxFunctions.SaveInitialModule(MODULE_KIND, thisModule, palavra);
       UserSave(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not save module: ' + thisModule.Name);
   end;
end;

function TModuleManagerCompiler.VerifySymbols(blocoGeral: TModule): string;
var listaVerificacoes: TStringList;
    thisModule: TNewModuleCompiler;
begin
   try
      thisModule := TNewModuleCompiler(blocoGeral);
      GenesysErrorMessage := '';
      UserVerifySymbols(thisModule, listaVerificacoes);
      result := GenesysErrorMessage;
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not verify symbols of module: ' + thisModule.Name);
   end;
end;

function TModuleManagerCompiler.Execute(var thisModule: TNewModuleCompiler; umMetodo:string): TGenesysEventHandler;////umMetodo:string);////entidade: word);
begin
   try
      Genesys.Model.TraceSimulation(3, thisModule.ID, 0, 'Entity arrives at "' +thisModule.Name+ '" module');
      result := UserExecute(thisModule, umMetodo); ////umMetodo); ////entidade);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not execute module: ' + thisModule.Name);
   end;
end;

constructor TModuleManagerCompiler.Create;
begin
   inherited Create;
end;



function TModuleManagerCompiler.AddModule: TNewModuleCompiler;
var newModule: TNewModuleCompiler;
begin
   newModule := TNewModuleCompiler.Create(0,'', MODULE_KIND);
   result := newModule;
end;

procedure TModuleManagerCompiler.ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
var auxStr: string;
    auxBool: boolean;
    ptrBloco: ^TModule;
    ptrStrList: ^TStringList;
    umComponente : TNewModuleCompiler;
    umaEntidade : Word;
begin
   try
   if metodo = pmReadModule  then begin
      //in: pointer1: FileName
      ptrStrList := umPonteiro1;
      PlugInCompiler.ReadModule(ptrStrList^);
      end
   else if metodo = pmSaveModule then begin
      //in: pointer1: a Module
      //out: TStringList with the attributes'values
      ptrBloco := umPonteiro1;
      ptrStrList := umPonteiro2;
      PlugInCompiler.SaveModule(ptrBloco^, ptrStrList^);
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
      auxStr := PlugInCompiler.VerifySymbols(ptrBloco^);
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmINCLUDEMODULE then begin
      umComponente := PlugInCompiler.AddModule;
      GetMem(umPonteiro1, SizeOf(umComponente));
      TNewModuleCompiler(umPonteiro1) := umComponente;
      end
   else if metodo = pmExecute then begin
      umComponente := TNewModuleCompiler(umPonteiro1^);
      auxStr := string(umPonteiro2^); ////Um método - diferente dos outros templates
      TGenesysEventHandler(umPonteiro2^) := PlugInCompiler.Execute(umComponente,auxStr);
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
   exportedMethods := PlugInCompiler.ExportedMethodsAccess;
end;

{ Exportação, Inicialização e Finalização}

exports GetComponentMethods;

{Autor: Rafael Luiz Cancian}
{Data:  v1.0:10/03/2002,   v1.1:11/07/2003, ... v: 04/10/2003, 13/03/2004}
       {v3.1: 23/06/2004,  V4.0: 11/03/2005  V5.0: 16/05/2005}
begin
   PlugInCompiler := TModuleManagerCompiler.Create;
end.

finalization
   PlugInCompiler.Destroy;
