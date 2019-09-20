{Comment the next line ($UNDEF IsDllPlugin) if you intend to generate a DLL file.}
{Uncomment it to generate a DCU file}
{$UNDEF IsDllPlugin}
{$IFDEF IsDllPlugin}
library MICROCONTROLLER;
{$ELSE}
unit MICROCONTROLLER;
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
const
   itLogicArit      = 0;
   itJumpGoto       = 1;
   itBranch         = 2;
   itTimer          = 3;
   itWatchDog       = 4;
   itInternalMemory = 5;
   itPeriferal      = 6;
   itBus            = 7;

type
    TInstructionTable = class(TObject)
    private
       OutputPin,
       InputPin: integer;
       InstructionType: integer;
       Address: string;
       CiclesPerInstruction: string;
       Probability: string;
       Synchonous: boolean;
       NumSends: string;
    end;

    TNewModuleMicrocontroller = Class(TSourceModule)
    private
         {place here the attributes of your new module}
         {Examples:}
         {attribute1: type1;}
         {attribute2: type2;}
         {... YOUR CODE HERE ...}
         aInstructionTable: TStringList;  {list of TInstructionTable}
         //Atributos do Microcontrolador
         aClockFrequency: Double;
         {Internal Memory}
         aAccessNumberToInternalMemoryCStatID : Word;
         aTimeAccessToInternalMemoryCStatID : Word;
         {Timer}
         aAccessNumberToTimerCStatID : Word;
         aTimeAccessToTimerCStatID : Word;
         {WatchDog Timer}
         aAccessNumberToWatchDogCStatID : Word;
         aTimeAccessToWatchDogCStatID : Word;
         {Branch}
         aAccessNumberToBranchCStatID : Word;
         aTimeAccessToBranchCStatID : Word;
         {Bus}
         aAccessNumberToBusCStatID : Word;
         {Logic Aritmetic}
         aAccessNumberToLogicAritCStatID : Word;
         {Jump and Goto}
         aAccessNumberToJumpGotoCStatID : Word;
         {Peripherals}
         aAccessNumberToPeriferalCStatID : Word;
         {other}
         aTimerAccessTimeCStatID: word;
         aRemainingCicles, aRemainingSends: integer;
         aSendOutputPin: integer;
         aExternalSignalWaiting: integer;
         aRequestSendTime: double;
         aAnswerIntervalCStatID: word;
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
         property InstructionTable: TStringList    read aInstructionTable  write aInstructionTable;
         property Frequency:Double                 read aClockFrequency    write aClockFrequency;
      end;

      TModuleManagerMicrocontroller = class(TObject)
      private
         function  AddModule: TNewModuleMicrocontroller;
         procedure ReadModule(palavra: TStringList);
         procedure SaveModule(generalModule: TModule; var palavra: TStringList);
         procedure Execute(var thisModule: TNewModuleMicrocontroller; entidade: word); virtual;
         function  VerifySymbols(blocoGeral: TModule): string;
         procedure UserExecute(var thisModule: TNewModuleMicrocontroller; entity: word);
         procedure UserRead(var thisModule: TNewModuleMicrocontroller; words: TStringList);
         procedure UserSave(thisModule: TNewModuleMicrocontroller; var words: TStringList);
         procedure UserVerifySymbols(thisModule: TNewModuleMicrocontroller; var verifyList: TStringList);
      public
         constructor Create;
         procedure ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
      end;

   var
      PlugInMicrocontroller : TModuleManagerMicrocontroller;
{$IFDEF IsDLLPlugin}
      Genesys: TGenesysAppPtr;
{$ELSE}
implementation
{$ENDIF}

   const
      {fill up the following informations about your new module}
      MODULE_KIND        = 'MICROCONTROLLER';                   {... YOUR INFOS HERE ...}
      MODULE_AUTHOR      = 'Rafael Luiz Cancian';   {... YOUR INFOS HERE ...}
      MODULE_VERSION     = '1.1.0 in 15/03/2005';   {... YOUR INFOS HERE ...}
      MODULE_DESCRIPTION = 'Instruction execution on a microcontroller';   {... YOUR INFOS HERE ...}
      MODULE_IS_VISUAL   = true;                    {... YOUR INFOS HERE ...}
      MODULE_IS_SOURCE   = true;                    {... YOUR INFOS HERE ...}
      MODULE_IS_DISPOSE  = true;                    {... YOUR INFOS HERE ...}
      MODULE_DEPENDENCES = '';                      {... YOUR INFOS HERE ...}
      {example:  MODULE_DEPENDENCES = 'assign.dll;batch.dll' }


procedure TNewModuleMicrocontroller.UserCreate(novoId: word; novoNome, novoKind: string);
begin
   {initialize here the necessary attributes of your new module}
   {Examples:}
   {attribute1 := '';}
   {attribute2 := 0;}
   {... YOUR CODE HERE ...}
   aFirstCreation := 0;
   aEntitiesPerCreation := '1';

   aInstructionTable := TStringList.Create;
   InstructionTable.Sorted := false;
   aClockFrequency := 0; //10
   aAccessNumberToInternalMemoryCStatID := 0;
   aTimeAccessToInternalMemoryCStatID := 0;
   aAccessNumberToTimerCStatID := 0;
   aTimeAccessToTimerCStatID := 0;
   aAccessNumberToWatchDogCStatID := 0;
   aTimeAccessToWatchDogCStatID := 0;
   aAccessNumberToBranchCStatID := 0;
   aTimeAccessToBranchCStatID := 0;
   aAccessNumberToBusCStatID := 0;
   aAccessNumberToLogicAritCStatID := 0;
   aAccessNumberToJumpGotoCStatID := 0;
   aAccessNumberToPeriferalCStatID := 0;
   aTimerAccessTimeCStatID := 0;
   aRemainingCicles := 0;
   aRemainingSends := 0;
   aExternalSignalWaiting := 0;
   Randomize;
end;

procedure TModuleManagerMicrocontroller.UserRead(var thisModule:TNewModuleMicrocontroller; words:TStringList);
var
  i : Integer;
  instrTableRow: TInstructionTable;
begin
    {Place here the code for reading the attributes of your new component}
    {The values readed from the model file are in the "words.Strings[]" vector}
    {Examples:}
    {thisModule.attribute1 := words.Strings[0];}
    {thisModule.attribute2 := StrToInt(words.Strings[1]);}
    {... YOUR CODE HERE ...}
    thisModule.aClockFrequency := StrToFloat(words.Strings[0]);
    i := 5;
    while(i < words.Count) do begin
        instrTableRow := TInstructionTable.Create;
        instrTableRow.OutputPin := StrToInt(words.Strings[i+0]);
        instrTableRow.InputPin := StrToInt(words.Strings[i+1]);
        instrTableRow.InstructionType := StrToInt(words.Strings[i+2]);
        instrTableRow.CiclesPerInstruction := (words.Strings[i+3]);
        instrTableRow.Probability := (words.Strings[i+4]);
        instrTableRow.Synchonous := StrToInt(words.Strings[i+5]) = 1;
        instrTableRow.Address := (words.Strings[i+6]);
        instrTableRow.NumSends := (words.Strings[i+7]);
        thisModule.aInstructionTable.AddObject(IntToStr(i),instrTableRow);
        i := i + 8;
    end;
    {cria os CStats necessários}
    thisModule.aAnswerIntervalCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.AnswerTime', cCSTAT);
    thisModule.aAccessNumberToInternalMemoryCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.AccessNumberInternalMemory', cCSTAT);
    thisModule.aTimeAccessToInternalMemoryCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.TimeAccessInternalMemory', cCSTAT);
    thisModule.aAccessNumberToTimerCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.AccessNumberTimer', cCSTAT);
    thisModule.aTimeAccessToTimerCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.TimeAccessTimer', cCSTAT);
    thisModule.aAccessNumberToWatchDogCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.AccessNumberWatchDog', cCSTAT);
    thisModule.aTimeAccessToWatchDogCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.TimeAccessWatchDog', cCSTAT);
    thisModule.aAccessNumberToBranchCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.AccessNumberBranch', cCSTAT);
    thisModule.aTimeAccessToBranchCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.TimeAccessBranch', cCSTAT);
    thisModule.aAccessNumberToBusCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.AccessNumberBus', cCSTAT);
    thisModule.aAccessNumberToLogicAritCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.AccessNumberLogicArit', cCSTAT);
    thisModule.aAccessNumberToJumpGotoCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.AccessNumberJumpGoto', cCSTAT);
    thisModule.aAccessNumberToPeriferalCStatID := Genesys.Model.SIMAN.CStatInsert(0, thisModule.Name+'.AccessNumberPeriphiral', cCSTAT);
end;

procedure TModuleManagerMicrocontroller.UserSave(thisModule:TNewModuleMicrocontroller; var words: TStringList);
var
  i: Integer;
  instrTableRow: TInstructionTable;
begin
    {Place here the code for saving the attributes of your new component}
    {The values to be saved in the model file need to be added to the "words" list}
    {Examples:}
    {words.Add(thisModule.attribute1);}
    {words.Add(IntToStr(thisModule.attribute2));}
    {... YOUR CODE HERE ...}
     words.Add(FloatToStr(thisModule.aClockFrequency));
{     words.Add(FloatToStr(thisModule.aTimeAccessToInternalMemory));
     words.Add(FloatToStr(thisModule.aTimeAccessToTimer));
     words.Add(FloatToStr(thisModule.aTimeAccessToWatchDog));
     words.Add(FloatToStr(thisModule.aTimeAccessToInternalBus));
}
     for i := 0 to thisModule.aInstructionTable.Count - 1 do begin
        instrTableRow := TInstructionTable(thisModule.aInstructionTable.Objects[i]);
        words.Add(IntToStr(instrTableRow.OutputPin));
        words.Add(IntToStr(instrTableRow.InputPin));
        words.Add(IntToStr(instrTableRow.InstructionType));
        words.Add((instrTableRow.CiclesPerInstruction));
        words.Add((instrTableRow.Probability));
        if instrTableRow.Synchonous then words.Add('1') else words.Add('0');
        words.Add((instrTableRow.Address));
        words.Add((instrTableRow.NumSends));
    end;
end;

procedure TModuleManagerMicrocontroller.UserVerifySymbols(thisModule:TNewModuleMicrocontroller; var verifyList:TStringList);
var
  i: Integer;
  instrRow: TInstructionTable;
begin
   {Place here the list of string attributes that parses to expression, attributes,}
   {variables, etc and need to be evaluated - just like "int(Norm(3,1))+Entity.JobStep"}
   {Place that as a list of calls to the "VerifySymbol" procedure, as shown bellow:}
   {Genesys.AuxFunctions.VerifySymbol(moduleName, description, expression, resultType, mandatory}
   {Examples:}
   {Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'The first attribute', thisModule.Attribute1, cEXPRESSION, true);}
   {... YOUR CODE HERE ...}
   Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'EntitiesPerCreation', thisModule.aEntitiesPerCreation , cEXPRESSION, true);
   for i := 0 to thisModule.aInstructionTable.Count-1 do begin
      instrRow := TInstructionTable(thisModule.aInstructionTable.Objects[i]);
      Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'Probability['+intToStr(i)+']', instrRow.Probability , cEXPRESSION, true);
      Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'Address['+intToStr(i)+']', instrRow.Address, cEXPRESSION, false);
      Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'CiclesPerInstruction['+intToStr(i)+']', instrRow.CiclesPerInstruction, cEXPRESSION, true);
      Genesys.AuxFunctions.VerifySymbol(thisModule.Name, 'NumSends['+intToStr(i)+']', instrRow.NumSends, cEXPRESSION, false);
   end;
end;

procedure TModuleManagerMicrocontroller.UserExecute(var thisModule:TNewModuleMicrocontroller; entity:word);
var
  fltProbAcc, fltProbEsc : Double;
  i, sends, input, addr : Integer;
  prob, newPulse: double;
  instrRow: TInstructionTable;
  newEntityID: word;
  thisWait: TWaiting;
  thisQueue: TQueue;
  strIntr: String;
  atendeu,
  enviou: boolean;

{Procedimento que Verifica se existe um sinal em algum pino e o executa}
{caso exista outros mais, somente o último é utilizado}
procedure VerifySignalInPins;
Begin
   i := 0;
   input := 0;
   while (i < Genesys.Model.SIMAN.QueuesCount) and (input = 0) do begin
      thisQueue := Genesys.Model.SIMAN.Queue[i];
      if (thisQueue.ModuleID = thisModule.ID) and (thisQueue.Waiting.Count > 0) then begin
         {achou uma fila associada a um pino de entrada deste módulo com entidades esperando}
         {decarta as n-1 primeiras entidades}
         while (thisQueue.Waiting.Count > 1) do begin
            thisQueue.RemoveElementByRank(0); //Não REMOVE!!!!!!
            {pode anotar a quantidade de entidaes (sinais) perdidos e colocar num CSTAT}
         end;
         thisWait := thisQueue.RemoveElementByRank(0); {remove o último sinal, aquele que será atendido}
         input := thisQueue.ModuleInput{ + 1 {input tem o pino}
      end;
      i := i + 1;
   end;

   if (input > 0) then begin
      {há um sinal para ser atendido}
      {pega o endereço da entidade que aguardava}
      atendeu := true;
      enviou := true;
      i := Genesys.Model.SIMAN.AttributeIndex('Address');
      addr := trunc(Genesys.Model.SIMAN.EntityAttribute[thisWait.EntityID, i]);
      {procura na tabela de instruções uma linha com esse pino de entrada e esse endereço}
      i := 0;
      while (i < thisModule.aInstructionTable.Count) do begin
         instrRow := TInstructionTable(thisModule.aInstructionTable.Objects[i]);
         if (instrRow.InputPin = input){ and (Genesys.Model.SIMAN.StringEvaluateFormula(instrRow.Address) = addr)} then begin
            thisModule.aRemainingCicles := trunc(Genesys.Model.SIMAN.StringEvaluateFormula(instrRow.CiclesPerInstruction)) - 1;
            i := thisModule.aInstructionTable.Count;
         end;
         i := i + 1;
      end;
   end;
End;
{Fim do Procesimento}

procedure ExecuteNewInstruction;
begin
   {escolhe o tipo de instrução conforme a Tabela de Instruções}
   i := 0;
   fltProbAcc := 0;
   fltProbEsc := Random;
   while (fltProbAcc < fltProbEsc) and (i < thisModule.aInstructionTable.Count) do begin
     if (i = thisModule.aInstructionTable.Count) Then
        i := 0;

     instrRow := TInstructionTable(thisModule.aInstructionTable.Objects[i]);
     prob := Genesys.Model.SIMAN.StringEvaluateFormula(instrRow.Probability);
     fltProbAcc := fltProbAcc + prob;
     Inc(i);
   end;
   Dec(i);
   instrRow := TInstructionTable(thisModule.aInstructionTable.Objects[i]);
   {verifica o tipo de instrução e coleta estatisticas}
   strIntr := '';
   Case instrRow.InstructionType Of
     itLogicArit      : Genesys.Model.SIMAN.CStatAddValue(thisModule.aAccessNumberToLogicAritCStatID,1);
     itJumpGoto       : Genesys.Model.SIMAN.CStatAddValue(thisModule.aAccessNumberToJumpGotoCStatID,1);
     itBranch         : Genesys.Model.SIMAN.CStatAddValue(thisModule.aAccessNumberToBranchCStatID,1);
     itTimer          : Genesys.Model.SIMAN.CStatAddValue(thisModule.aAccessNumberToTimerCStatID,1);
     itWatchDog       : Genesys.Model.SIMAN.CStatAddValue(thisModule.aAccessNumberToWatchDogCStatID,1);
     itInternalMemory : Genesys.Model.SIMAN.CStatAddValue(thisModule.aAccessNumberToInternalMemoryCStatID,1);
     itPeriferal      : Genesys.Model.SIMAN.CStatAddValue(thisModule.aAccessNumberToPeriferalCStatID,1);
     itBus            : Genesys.Model.SIMAN.CStatAddValue(thisModule.aAccessNumberToBusCStatID,1);
   End;
   {vai executar uma instrução do i-ésimo tipo}
   if instrRow.NumSends = '' then
      sends := 1
   else begin
      sends := trunc(Genesys.Model.SIMAN.StringEvaluateFormula(instrRow.NumSends));
   end;
   thisModule.aRemainingCicles := trunc(Genesys.Model.SIMAN.StringEvaluateFormula(instrRow.CiclesPerInstruction)) * sends - 1;
   Genesys.Model.TraceSimulation(cTLModuleIntern,thisModule.ID,entity,'Will execute a instruction of type '+IntToStr(i)+' for '+IntToStr(thisModule.aRemainingCicles+1)+' cicles');
   if (instrRow.OutputPin > 0) then begin
      {essa instrução acessa um dispositivo de saída. Envia uma entidade para o pino associado}
      if instrRow.Synchonous then begin
         thisModule.aExternalSignalWaiting := instrRow.InputPin;
         {algum atributo deve receber TNOW para depois marcar num CSTST o yempo decorrido}
         thisModule.aRequestSendTime := Genesys.Model.TNOW;
      end;
      {envia entidade para pino de saída}
      enviou := true;
      thisModule.aRemainingSends := trunc(Genesys.Model.SIMAN.StringEvaluateFormula(instrRow.NumSends)) - 1;
      thisModule.aSendOutputPin := instrRow.OutputPin;
      i := Genesys.Model.SIMAN.AttributeIndex('Address');
      Genesys.Model.SIMAN.EntityAttribute[entity,i] := Genesys.Model.SIMAN.StringEvaluateFormula(instrRow.Address);
      Genesys.Model.SIMAN.EntitySendToModuleNumber(entity,thisModule.NextID[thisModule.aSendOutputPin-1],0);
   end;
end;
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
   input := trunc(Genesys.Model.SIMAN.AttributeValue['Entity.InputNumber']);
   if (input = 0) then begin
      {é um pulso de clock interno}
      {agenda a criação de um novo pulso de clock}
      enviou := false;
      newEntityID := Genesys.Model.SIMAN.EntityCreate(thisModule.aEntityTypeID);
      newPulse := Genesys.Model.TNOW + (1/thisModule.aClockFrequency)*Genesys.AuxFunctions.TimeUnitConvert(tuS, Genesys.Model.BaseTimeUnit);
      Genesys.Model.TraceSimulation(cTLModuleIntern,thisModule.ID,entity,'Received a clock pulse. Next pulse will be at time '+FloatToStr(newPulse));
      Genesys.Model.SIMAN.CalendarInsertEvent(newPulse, newEntityID, thisModule.ID);
      {verifica se continua a execução de uma instrução ou executa uma nova}
      if (thisModule.aRemainingCicles > 0) then begin
         {ainda está executando uma instrução. Decrementa a quantidade pulsos que ainda faltam}
         thisModule.aRemainingCicles := thisModule.aRemainingCicles - 1;
         Genesys.Model.TraceSimulation(cTLModuleIntern,thisModule.ID,entity,'Continue executing the current instruction');
         {verifica se deve enviar a entidade para algum pino de saída}
         if thisModule.aRemainingSends > 0 then begin
            enviou := true;
            thisModule.aRemainingSends := thisModule.aRemainingSends - 1;
            Genesys.Model.SIMAN.EntitySendToModuleNumber(entity,thisModule.NextID[thisModule.aSendOutputPin-1],0);
         end;
      end else begin
         if (thisModule.aExternalSignalWaiting = 0) then begin
            {verifica se há sinal pendente}
            VerifySignalInPins;
            {vai executar uma nova instrução}
            if (input = 0) Then Begin
               ExecuteNewInstruction;
            end;
         end;
      end;
      {verfica se a entidade que representa o pulso de clock não foi enviada adiante. Nesse caso, destroi a entidade}
      if not enviou then begin
         Genesys.Model.SIMAN.EntityDispose(entity, false);
         //Genesys.Model.TraceSimulation(5,thisModule.ID,entity,'Entity is Disposed');
      end;
   end;

   if (input > 0) then begin
      {chegou uma entidade por algum pino de entrada}
      atendeu := false;
      if (thisModule.aExternalSignalWaiting > 0) then begin
         {um sinal é esperado}
         if (thisModule.aExternalSignalWaiting = input) then begin
            {o sinal esperado foi recebido}
            atendeu := true;
            thisModule.aExternalSignalWaiting := 0;
            {marcar no CSTAT o tempo decorrido}
            Genesys.Model.SIMAN.CStatAddValue(thisModule.aAnswerIntervalCStatID, (Genesys.Model.TNOW - thisModule.aRequestSendTime));
            {retira entidade que chegou da fila de espera do pino de entrada}
            i := Genesys.Model.SIMAN.AttributeIndex('Entity.QueuedNumber'); {i tem o índice do atributo QueuedNumber}
            i := trunc(Genesys.Model.SIMAN.EntityAttribute[entity,i]);  {i tem o valor do atributo, ou seja, o ID da fila}
            i := Genesys.Model.SIMAN.QueueIndex(i);  {i tem o índice da fila}
            Genesys.Model.SIMAN.Queue[i].RemoveElementByID(entity); {remove a entidade da fila}
         end;
      end;
      {verifica se tem alguma entidade num pino de entrada para atender}
      if (thisModule.aExternalSignalWaiting = 0) then begin
        VerifySignalInPins;
      end;
      if not atendeu then begin
         Genesys.Model.TraceSimulation(cTLModuleIntern,thisModule.ID,entity,'Entity remains waiting in queue');
      end;
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

constructor TNewModuleMicrocontroller.Create(novoId: word; novoNome, novoKind: string);
begin
   try
      inherited;
      UserCreate(novoId, novoNome, novoKind);
   except
      Genesys.Model.Trace(1, 'Plugin "' + MODULE_KIND + '" could not create module ' + self.Name);
   end;
end;

procedure TModuleManagerMicrocontroller.ReadModule(palavra: TStringList);
var thisModule: TNewModuleMicrocontroller;
    newID: word;
 begin
    try
       newID := Genesys.Model.ModuleAdd(MODULE_KIND);
       thisModule := TNewModuleMicrocontroller(Genesys.Model.ModuleByID(newID));
       Genesys.AuxFunctions.ReadInitialModule(MODULE_KIND, TModule(thisModule), palavra);
       UserRead(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not read module: ' + thisModule.Name);
   end;
end;

procedure TModuleManagerMicrocontroller.SaveModule(generalModule: TModule; var palavra: TStringList);
var thisModule: TNewModuleMicrocontroller;
begin
   try
       thisModule := TNewModuleMicrocontroller(generalModule);
       Genesys.AuxFunctions.SaveInitialModule(MODULE_KIND, thisModule, palavra);
       UserSave(thisModule, palavra);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not save module: ' + thisModule.Name);
   end;
end;

function TModuleManagerMicrocontroller.VerifySymbols(blocoGeral: TModule): string;
var listaVerificacoes: TStringList;
    thisModule: TNewModuleMicrocontroller;
begin
   try
      thisModule := TNewModuleMicrocontroller(blocoGeral);
      GenesysErrorMessage := '';
      UserVerifySymbols(thisModule, listaVerificacoes);
      result := GenesysErrorMessage;
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not verify symbols of module: ' + thisModule.Name);
   end;
end;

procedure TModuleManagerMicrocontroller.Execute(var thisModule: TNewModuleMicrocontroller; entidade: word);
begin
   try
      Genesys.Model.TraceSimulation(3, thisModule.ID, entidade, 'Entity arrives at "' +thisModule.Name+ '" module');
      UserExecute(thisModule, entidade);
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not execute module: ' + thisModule.Name);
   end;
end;

constructor TModuleManagerMicrocontroller.Create;
begin
   inherited Create;
end;



function TModuleManagerMicrocontroller.AddModule: TNewModuleMicrocontroller;
var newModule: TNewModuleMicrocontroller;
begin
   newModule := TNewModuleMicrocontroller.Create(0,'', MODULE_KIND);
   result := newModule;
end;

procedure TModuleManagerMicrocontroller.ExportedMethodsAccess(metodo: TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer);
var auxStr: string;
    auxBool: boolean;
    ptrBloco: ^TModule;
    ptrStrList: ^TStringList;
    umComponente : TNewModuleMicrocontroller;
    umaEntidade : Word;
begin
   try
   if metodo = pmReadModule  then begin
      //in: pointer1: FileName
      ptrStrList := umPonteiro1;
      PlugInMicrocontroller.ReadModule(ptrStrList^);
      end
   else if metodo = pmSaveModule then begin
      //in: pointer1: a Module
      //out: TStringList with the attributes'values
      ptrBloco := umPonteiro1;
      ptrStrList := umPonteiro2;
      PlugInMicrocontroller.SaveModule(ptrBloco^, ptrStrList^);
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
      if MODULE_IS_SOURCE  then auxStr := auxStr+'1;' else auxStr := auxStr+'0;';
      if MODULE_IS_DISPOSE then auxStr := auxStr+'1;' else auxStr := auxStr+'0;';
      if MODULE_IS_VISUAL  then auxStr := auxStr+'1;' else auxStr := auxStr+'0;';
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
      auxStr := PlugInMicrocontroller.VerifySymbols(ptrBloco^);
      GetMem(umPonteiro1, SizeOf(auxStr));
      string(umPonteiro1^) := auxStr;
      end
   else if metodo = pmINCLUDEMODULE then begin
      umComponente := PlugInMicrocontroller.AddModule;
      GetMem(umPonteiro1, SizeOf(umComponente));
      TNewModuleMicrocontroller(umPonteiro1) := umComponente;
      end
   else if metodo = pmExecute then begin
      umComponente := TNewModuleMicrocontroller(umPonteiro1^);
      umaEntidade := Word(umPonteiro2^);
      PlugInMicrocontroller.Execute(umComponente,umaEntidade);
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
   exportedMethods := PlugInMicrocontroller.ExportedMethodsAccess;
end;

{ Exportação, Inicialização e Finalização}

exports GetComponentMethods;

{Autor: Rafael Luiz Cancian}
{Data:  v1.0:10/03/2002,   v1.1:11/07/2003, ... v: 04/10/2003, 13/03/2004}
       {v3.1: 23/06/2004,  V4.0: 11/03/2005}
begin
   PlugInMicrocontroller := TModuleManagerMicrocontroller.Create;
end.

finalization
   PlugInMicrocontroller.Destroy;
