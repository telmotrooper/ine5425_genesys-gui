{$UNDEF KernelIsDLL}         {When uncommented compile KERNEL as DLL}
//{$DEFINE KernelIsDLL}      {When uncommented compile KERNEL as unit}

//{$DEFINE IsDLLPlugin}      {When uncommented compile plug-ins as DLLs files}
{$UNDEF IsDLLPlugin}         {When uncommented compile plug-in as unit files}

//{$DEFINE KernelDebugMode}  {When uncommented sets the kernel to debug mode}

{*******************************************************************************
*                                                                              *
*           GENESYS - GENERIC EXPANSIBLE SYSTEMS SIMULATOR                     *
*                                                                              *
*                                                                              *
*           ZEROUM SOLUCOES LTDA                                               *
*                                                                              *
*                                                                              *
* Autor: Rafael Luiz Cancian, 03/2002 - 05/2005                                *
*        -------------------                                                   *
*                                                                              *
*******************************************************************************}

{$IFDEF KernelIsDLL}
   library GenesysKernel;
{$ELSE}
   unit GenesysKernel;
   interface
{$ENDIF}

   uses
      classes, graphics, stdctrls, Dialogs, XMLIntf
{$IFNDEF KernelIsDLL}
      ;
{$ELSE}
     ,Windows, Sysutils, buttons, Forms, extctrls,
     GenesysYacc, lexlib, yacclib, uGenerateActivationCode
  {$IFDEF IsDLLPlugin}
     ;
  {$ELSE}
     , DllOrUnit;
  {$ENDIF}
{$ENDIF}


   const
      cKERNELVERSION    = '2.3.0';
      { Module Structures provid by Genesys }
      cATTRIBUTE        = 'ATTRIBUTE';
      cCSTAT            = 'CSTAT';
      cENTITY           = 'ENTITY';
      cENTITYTYPE       = 'ENTITYTYPE';
      cEVENT            = 'EVENT';
      cFAILURE          = 'FAILURE';
      cEXPRESSION       = 'EXPRESSION';
      cFORMULA          = 'FORMULA';
      cQUEUE            = 'QUEUE';
      cPROJECT          = 'PROJECT';
      cRESOURCE         = 'RESOURCE';
      cSET              = 'SET';
      cVARIABLE         = 'VARIABLE';
      {trace levels}
      {0:NONE;
       1:ERROR MESSAGES ONLY;
       2:RESULTS OF METHODS;
       3:1st LEVEL OF METHODS;
       4:2nd LEVEL OF METHODS-DETAILED;
       5:MOST DETAILED}
      cTLMostImportant = 0;
      cTLError         = 1;
      cTLTransfer      = 2;
      cTLModule        = 3;
      cTLModuleIntern  = 4;
      cTLModuleDetail  = 5;
      cTLKernelIntern  = 6;
      cTLReport        = 0;

   type
      TTraceLevel = (tlReport, tlError, tlMethods, tlArrival, tlInternel, tlDetail, tlKernelIntern);

      TTimeUnit = (tuPs, tuNs, tuUs, tuMs, tuS, tuMin, tuH, tuDay, tuWeek, tuMounth, tuYear, tuDecade, tuCentury);

      TAllocationType = (atNone, atWaitingTime, atTransferTime, atVATime, atNVATime, atOtherTime);

      {Basic class for all components of Genesys Simulator}
      TModuleStructure = class(TPersistent)
      private
         procedure _SetID(const Value: word); virtual;
      protected
         aId: word;
         aName: string;
         aKind: string;
         aInterfaceReserved:string;
      public
         constructor Create(novoId: word; novoNome, novoKind: string); virtual;
         property ID:word                  read aId                write _SetID;              {unique ID}
         property Kind:string              read aKind              write aKind;               {string whiy the 'type' of the module}
         property InterfaceReserved:string read aInterfaceReserved write aInterfaceReserved;  {string reserved for graphical interface purposes}
      published
         property Name:string              read aName              write aName;
      end;

      {Basic class for all plug-in modules of Genesys simulator}
      TModule = class(TModuleStructure)
      protected
         aIDNexts  : TStringList;
         function  _GetProximoCount: integer;
         function  _GetIDProximo(index:integer): word;
         procedure _SetIDProximo(index:integer; valor:word);
      public
         constructor Create(novoId: word; novoNome, novoKind: string); virtual;
         procedure Execute(entidade: word); virtual; abstract;                                {main method of a plug-in module}
         property  NextCount:integer            read _GetProximoCount;                        {number of modules connected as output}
         property  NextIDs:TStringList          read aIDNexts        write aIDNexts;          {list of next modules IDs}
         property  NextID[index:integer]:word  read _GetIDProximo   write _SetIDProximo;     {one next module ID}
      published
      end;


      {Basic classs for all plug-in modules that create enetities in the model}
      TSourceModule = class(TModule)
      protected
         aFirstCreation: double;
         aEntitiesPerCreation: string;
         aEntityTypeID: word;
      public
      published
         constructor Create(novoId: word; novoNome, novoKind: string); virtual;
         {these methods are always present in 'creation' modules}
         property EntitiesPerCreation:string  read aEntitiesPerCreation  write aEntitiesPerCreation;
         property FirstCreation:double        read aFirstCreation        write aFirstCreation;
         property EntityTypeID:word           read aEntityTypeID         write aEntityTypeID;
      end;


      {An event to be threated and scheduled}
      TEvent = class(TModuleStructure) //TObject)
      private
         aTime: double;
         aEntity,
         aModuleID: word;
      public
         constructor Create(novoInstante: double; novaEntid, novoId: word);
      published
         property Time:double   read aTime      write aTime;
         property Entity:word   read aEntity    write aEntity;
         property ModuleID:word read aModuleID  write aModuleID;
      end;


      {Class that collects statistics from the model}
      TCSTAT = class(TModule)
      protected
         aCategory: string;
         aAcumulatedAverage,
         aAcumulatedDeviation,
         aSumOfValues,
         aSumOfSquareValues,
         aIntervalo,
         aMinimum,
         aMaximum,
         aZCritico,
         aLastValue: double;
         aKeepAtualizated: boolean;
         aNumElementos: word;
         aGravarLog: boolean;
         aFileName: string;
         procedure _SetConfianca(valor: double);
      public
         constructor Create(newID:word; newName, newCategory:string); virtual;
         procedure AddValue(valor: double);
         procedure Clear;
         property  Average:double                read aAcumulatedAverage;
         property  CAtegory:string               read aCAtegory          write aCategory;
         property  Deviation:double              read aAcumulatedDeviation;
         property  KeepAtualizated: boolean      read aKeepAtualizated   write aKeepAtualizated;
         property  Minimum:double                read aMinimum;
         property  Maximum:double                read aMaximum;
         property  HalfWidth:double              read aIntervalo;
         property  TotalSum:double               read aSumOfValues;
         property  LastValue:double              read aLastValue         write aLastValue;
         property  Size:word                     read aNumElementos;
         property  Log:boolean                   read aGravarLog         write aGravarLog;
         property  FileName:string               read aFileName       write aFileName;
         property  Significancy:double                                   write _SetConfianca;
      end;


      {Class that reepresents the type of an entity and keeps the entitites' statistics}
      TEntityType = class(TmoduleStructure)
      private
         aInitialPicture: string;
         aInitialVACost,
         aInitialNVACost,
         aInitialOtherCost,
         aInitialWaitingCost: double;
         aCSTATWaitingTimeID,
         aCSTATTransferTimeID,
         aCSTATOtherTimeID,
         aCSTATVATimeID,
         aCSTATNVATimeID,
         aCSTATTimeInSystemID: word;
      public
         constructor Create(novoID:word; novoNome:string); virtual;
      published
         property InitialPicture: string        read aInitialPicture     write aInitialPicture;
         property InitialVACost:double          read aInitialVACost      write aInitialVACost;
         property InitialNVACost:double         read aInitialNVACost     write aInitialNVACost;
         property InitialOtherCost:double       read aInitialOtherCost   write aInitialOtherCost;
         property InitialWaitingCost: double    read aInitialWaitingCost write aInitialWaitingCost;
      end;


      TEntityPicture = string;  /////????

      {Class that represents one entity itself}
      TEntity = class(TModuleStructure)
      private
         aTypeID: word;
         aAttributes: TStringList; { (num_do_atrib, ?) }
         aCSTATWaitingTimeID,
         aCSTATTransferTimeID,
         aCSTATOtherTimeID,
         aCSTATVATimeID,
         aCSTATNVATimeID: word;
         procedure _SetAttribute(index:integer; value:double);
         function  _GetAttribute(index:integer): double;
      public
         constructor Create(novoId: word; novoNome: string); virtual;
         property Attributes:TStringList            read aAttributes   write aAttributes;
         property Attribute[index:integer]:double   read _GetAttribute write _SetAttribute;
         property TypeID:word                       read aTypeID       write aTypeID;
      end;


      {A resource that can be seized and released}
      TResourceState = (rsIDLE, rsBUSY, rsFAILED, rsINACTIVE, rsOTHER);
      TResource = class(TModuleStructure)
      private
         aWhenSeized: double;
         //aTempoAlocado: double;
         aNumberBusy,
         aNumberOut,
         aCapacity: integer;
         aCostBusyHour,
         aCostIdleHour,
         aCostPerUse: double;
         aQueueName: string;
         aState: TResourceState;
         aSeizes: word;
         aCSTATTimeSeizedID: word;
         aLastTimeSeized: double;
         aFailures:TStringList;
      public
         constructor Create(novoId: word; novoNome: string); virtual;
         property  NumberOut:integer       read aNumberOut;//               write aNumberOut;
         property  Seizes:word             read aSeizes;//                  write aSeizes;
         property  LastTimeSeized:double   read aLastTimeSeized;
         property  State:TResourceState    read aState;
         procedure Seize(quantity:integer);
         procedure Release(quantity:integer);
         procedure Clear;
      published
         property Capacity:integer        read aCapacity                write aCapacity;
         property CostIdlePerHour:double  read aCostIdleHour            write aCostIdleHour;
         property CostBusyPerHour:double  read aCostBusyHour            write aCostBusyHour;
         property CostPerUse:double       read aCostPerUse              write aCostPerUse;
         property NumberBusy: integer     read aNumberBusy;//              write aNumberBusy;
         property QueueName:string        read aQueueName               write aQueueName;
      end;


      TFailureType = (ftTime, ftCount);

      TFailure = class(TModuleStructure)
      private
         aType: TFailureType;
         aCount: string;
         aUpTime: string;
         aUpTimeUnit: TTimeUnit;
         aStateOnly: boolean;
         aUpTimeInThisStateOnly: TResourceState;
         aDownTime: string;
         aDownTimeUnit: TTimeUnit;
      public
         constructor Create(novoId: word; novoNome: string); virtual;
      published
         property FailureType:TFailureType             read aType                  write aType;
         property Count:string                         read aCount                 write aCount;
         property UpTime:string                        read aUpTime                write aUpTime;
         property UpTimeUnit:TTimeUnit                 read aUpTimeUnit            write aUpTimeUnit;
         property UpStateOnly:boolean                  read aStateOnly             write aStateOnly;
         property UpTimeInThisStateOnly:TResourceState read aUpTimeInThisStateOnly write aUpTimeInThisStateOnly;
         property DownTime:string                      read aDownTime              write aDownTime;
         property DownTimeUnit:TTimeUnit               read aDownTimeUnit          write aDownTimeUnit;
      end;

      {Class that represents an entity waiting into a queue}
      TWaiting = class(TObject)
      private
         aIDEntidade,
         aIdBloco: word;
         aInsertedTime: double;
      public
         constructor Create(novaEntid, novoIdBloco: word);
         property EntityID: word read aIDEntidade;
         property ModuleID: word read aIDBloco;
      end;


      {Class that represents an entity waiting into a queue to seize a certain amount of resource's instances}
      TWaitingResource = class(TWaiting)
      private
         aQuantidade: integer;
      public
         constructor Create(novaEntid, novoIdBloco: word; novaQuant: integer);
      published
         property Quantity: integer read aQuantidade;
      end;


      {A queue of several types}
      TQueueType = (qtFIFO, qtLVF, qtHVF, qtLIFO);
      TQueue = class(TModuleStructure)
      private
         aTipo: TQueueType;
         aAtributo: string;
         aEsperando: TStringList;
         aCSTATWaitingTimeID,
         aCSTATNumberWaitingID: word;
         aModuleID: word;
         aModuleInput: word;
         procedure _SetWaitingTimes(thisWait: TWaiting);
      public
         constructor Create(novoId: word; novoNome: string); virtual;
         destructor  Destroy; virtual;
         property  Waiting: TStringList     read aEsperando;
         procedure InsertElement(element:TWaiting);
         property  ModuleID:word            read aModuleID    write aModuleID;
         property  ModuleInput:word         read aModuleInput write aModuleInput;
         function  RemoveElementByRank(ranking:integer): TWaiting;
         function  RemoveElementByID(entityNumber:word): TWaiting;
         procedure Clear;
      published
         property QueueType:TQueueType     read aTipo        write aTipo;
         property Attribute:string         read aAtributo    write aAtributo;
      end;


      {Class that represents a global variable in the model. May be scalar, 1D or 2D arrays}
      TVariable = class(TModuleStructure)
      private
         aTamDimensao0: integer;
         aTamDimensao1: integer;
         aValores: TStringList; { (?, ?) }
         aInitialValores: TStringList; { (?, ?) }
      public
         constructor Create(novoId: word; novoNome: string); virtual;
         property  Values:TStringList           read aValores           write aValores;
         procedure Clear;
      published
         property Dimension1: Integer           read aTamDimensao0      write aTamDimensao0;
         property Dimension2: Integer           read aTamDimensao1      write aTamDimensao1;
         property InitialValues:TStringList     read aInitialValores    write aInitialValores;
      end;

      {Class that represents a global formula in the model. May be scalar, 1D or 2D arrays}
      TFormula = class(TVariable)
      private
      public
      published
         constructor Create(novoId: word; novoNome: string); override;
      end;

      {Class that represets a vector of structures}
      TSet = class(TModuleStructure)
      private
         aMembersType: string;  {resource, queue, etc}
         aMembers: TStringList; {string:ID}
         function _GetName(index:word):string;
         function _GetCount:integer;
      public
         constructor Create(novoId: word; novoNome: string); virtual;
         property MemberName[index:word]:string    read _GetName;
         property Count:integer                    read _GetCount;
      published
         property MemberType:string                read aMembersType write aMembersType;
         property Members:TStringList              read aMembers     write aMembers;
      end;


      {Types used to get access to DLLs and plug-in methods}

      {Type of 'Genesys Simulator' to be used in the plug-ins to get access of genesys' methods}
      TGenesysAppPtr = ^TGenesysApplication;
      {Type of plug-in's method (function) that kernel wants to access. There is only one exported method and the real funcion to executed is passed as an argument of this type}
      TPluginMethod = (pmREADMODULE, pmSAVEMODULE, pmIncludeModule, pmEXECUTE, pmGETTYPE, pmGETAUTHOR, pmGETVERSION, pmGETDESCRIP,
                       pmGETDEPENDENCES, pmGETINFOS, pmGETSOURCE, pmGETDRENO, pmGetVisual, pmVerifySymbols);
      {The only plug-in exported method is of the type bellow. The function is the first argument and input/output value are the two following pointers}
      TPluginAccess = procedure (command:TPlugInMethod; var umPonteiro1: pointer; var umPonteiro2: pointer) of object;
      {used one once to get access to the 'TPlugInAccess' exported method}
      TPluginInitiation = procedure (ptrSimulador: TGenesysAppPtr; var procAcessa: TPluginAccess);
      {type of method that can handle all trace events}
      TProcTrace = procedure(texto:string) of object;
      {type of method that can handle all simulator events}
      TGenesysEventHandler = procedure of object;


      {Class that keeps informations about an inserted plug-in}
      TPlugIn = class(TObject)
      private
         aID: word;
         aDLL,        {whole path of PlugIn file}
         aTipo,       {exemplo: 'CREATE', 'DELAY', 'RESOURCE', ...}
         aAutor,
         aVersao,
         aDescricao: string;
         aFonte,
         aDreno,
         aVisual: boolean;
         aDependencies: string; {list of DLL file dependences}
         aAcessa_Metodo: TPluginAccess; {pointer to the method that gives access to plug-in functions}  (* only when using DLL *)
      public
         constructor Create;
         property Author:string                 read aAutor             write aAutor;
         property DLL:string                    read aDLL               write aDLL;
         property Dreno:boolean                 read aDreno             write aDreno;
         property Description:string            read aDescricao         write aDescricao;
         property Dependences:string            read aDependencies      write aDependencies;
         property ID:word                       read aID;
         property Kind:string                   read aTipo              write aTipo;
         property Methods:TPluginAccess         read aAcessa_Metodo     write aAcessa_Metodo;
         property Source:boolean                read aFonte             write aFonte;
         property Version:string                read aVersao            write aVersao;
         property Visual:boolean                read aVisual            write aVisual;
      end;


      {Class that generates probability distributions}
      TProbDistribs = class(TObject)
      private
          aSeed: comp;
          aModulo: comp;
          aSeedInit: comp;
          aMultiplier: comp;
          aNormalFlag: boolean;
          aNormalResult: double;
          function  _Uni01: double;
          procedure _SetSeed(Value: comp);
          function  _GetSeed: comp;
          procedure _SetMultiplier(Value: comp);
          function  _GetMultiplier: comp;
          function  _GammaJonk(Alpha: double): double;
      public
          constructor Create;
          procedure Reset;
          function Uniform(limiteInf: double; limiteSup: double): double;
          function Triangular(Min: double; Mode: double; Max: double): double;
          function Exponential(media: double): double;
          function Erlang(media: double; M: integer): double;
          function Normal(media: double; desvio: double): double;
          function Gamma(media: double; Alpha: double): double;
          function Beta(ShapeAlpha: double; ShapeBeta: double;
                        limiteInf: double; limiteSup: double): double;
          function Weibull(Alpha: double; Scale: double): double;
          function Lognormal(media: double; desvio: double): double;
          property Seed: comp read _GetSeed write _SetSeed;
          property Multiplier: comp read _GetMultiplier write _SetMultiplier;
      end;

      {Auxiliar class that provides auxiliar functions}
      TAuxiliarFunctions = class(TObject)
      public
         constructor Create;
         {strings}
         procedure SeparateWords(texto: string; separador:char; var wordsList: TStringList);
         function  Substring(texto: string; inicio, chars: integer): string;
         function  LookForChar(texto: string; caract: char; inicio: integer): integer;
         function  StrLenght(texto: string): integer;
         function  StrLeft(texto: string; chars: integer): string;
         function  StrRight(texto: string; chars: integer): string;
         function  StrPos(texto, substr: string): integer;
         function  StrIdent(num: integer): string;
         function  FillValueWithZeros(valor: double; tamanho: integer): string;
         procedure SeparatePathAndFileName(caminho: string; var diretorio:string; var arquivo:string);
         function  Underscore(texto: string): string;
         procedure AdjustFloatFormat(var floatValue:string);
         {convertions}
         function  TimeUnitToInt(timeunit: TTimeUnit): integer;
         function  IntToTimeUnit(value:integer): TTimeUnit;
         function  TimeUnitConvert(timeunit1, timeunit2:TTimeUnit): double;
         function  ResourceStateToInt(state: TResourceState): integer;
         function  IntToResourceState(value:integer): TResourceState;
         {miscelaneous}
         procedure VerifySymbol(moduleName, expressionName, expression, resultType: string; mandatory: boolean);
         procedure Get_Lista_Proximos(texto: string; var IDProximos: TStringList);
         procedure SaveInitialModule(Module_Kind:string; thisModule:TModule; var wordsList:TStringList);
         procedure ReadInitialModule(Module_Kind:string; var thisModule:TModule; var wordsList:TStringList);
      end;


      {Main class to manipulate model structures and model modules - derived from Arena Siman language}
      TSIMAN = class(TObject)
      private
         aActiveEntity: word;
         aActiveModule: word;
         aLastNewID: word;
         aParent: TObject;
         aModuleStructures: TStringList;  {list of list} {list with Attributes, Entities, Events, Queues, VAriables, Resources}
         aRandom: TProbDistribs;
         function  _GenerateNewStructureID: word;
         function  _GetActualEntityAttributeValue(attributeName:string):double;
         function  _GetAttributeName(index:integer):string;
         function  _GetAttributeValue(entitynum,atribnum:word): double;
         function  _GetAttributesCount: integer;
         procedure _SetAttributeValue(entitynum,atribnum:word; value:double);
         function  _GetFailure(index: word): TFailure;
         procedure _SetFailure(index: word; const Value: TFailure);
         function  _GetFormula(index, i, j: integer): string;
         function  _GetFormulaCount: integer;
         function  _GetFormulaObject(index: integer): TFormula;
         function  _GetFormulaName(index: integer): string;
         function  _GetFormulaValue(index, i, j: integer): double;
         procedure _SetFormula(index, i, j: integer; const Value: string);
         function  _GetCStat(cstatNumber:word): TCStat;
         function  _GetStatAverage(cstatNumber:word):double;
         function  _GetStatSize(cstatNumber:word):double;
         function  _GetStatHalfWidth(cstatNumber:word):double;
         function  _GetStatLastValue(cstatNumber:word):double;
         function  _GetStatMaximum(cstatNumber:word):double;
         function  _GetStatMinimum(cstatNumber:word):double;
         function  _GetStatName(cstatNumber: word): string;
         procedure _SetStatName(cstatNumber: word; const Value: string);
         function  _GetStatFile(cstatNumber: word): string;
         procedure _SetStatFile(cstatNumber: word; const Value: string);
         function  _GetQueue(index: word):TQueue;
         function  _GetQueueByID(queueID:word): TQueue;
         function  _GetQueueName(queueID:word): string;
         procedure _SetActualEntityAttributeValue(attributeName:string; attributeValue:double);
         procedure _SetQueue(index:word; thisQueue:TQueue);
         procedure _SetQueueName(queueID:word; queueName:string);
         function  _GetResource(index: word):TResource;
         procedure _SetResource(index:word; thisResource:TResource);
         function  _GetModuleStructuresByKind(kind:string): TStringList;
         function  _GetVariableCount: integer;
         function  _GetVariable(index:integer):TVariable;
         function  _GetVariableName(index:integer): string;
         function  _GetVariableValue(index:integer; i,j:integer): double;
         procedure _SetVariableValue(index:integer; i,j:integer; value:double);
         function  _GetSetName(setNumber: word): string;
         function  _GetSetNumber(setIndex: word): word;
         procedure _SetSetName(setNumber: word; const Value: string);
      public
         constructor Create(owner:TObject);
         destructor Destroy;
         property  ActiveEntity:word                                        read aActiveEntity                                   write aActiveEntity;  {for Search module}
         property  ActiveModule:word                                        read aActiveModule;
         property  AttributeValue[attributeName:string]:double              read _GetActualEntityAttributeValue                  write _SetActualEntityAttributeValue;
         function  AttributeIndex(attributeName:string): integer;
         property  Attributes[attributeIndex:integer]:string                read _GetAttributeName;
         property  AttributesCount:integer                                  read _GetAttributesCount;
         procedure CalendarInsertEvent(time:double;entityID,moduleID:word);
         function  CalendarGetNextEvent:TEvent;
         function  CalendarCount: integer;
         procedure CStatAddValue(cstatNumber:word; newValue: double);
         property  CStatAverage[cstatNumber:word]:double                    read _GetStatAverage;
         procedure CStatClear(cstatNumber:word);
         function  CStatInsert(cstatNumber: word; cstatName, cstatCategory: string): word;
         property  CStatHalfWidth[cstatNumber:word]:double                  read _GetStatHalfWidth;
         property  CStatLastValue[cstatNumber:word]:double                  read _GetStatLastValue;
         property  CStatMaximum[cstatNumber:word]:double                    read _GetStatMaximum;
         property  CStatMinimum[cstatNumber:word]:double                    read _GetStatMinimum;
         property  CStatName[cstatNumber:word]:string                       read _GetStatName                      write _SetStatName;
         property  CStatFile[cstatNumber:word]:string                       read _GetStatFile                      write _SetStatFile;
         property  CStatSize[cstatNumber:word]:double                       read _GetStatSize;
         function  CStatIndex(cstatNumber:word):integer;
         function  CStatsCount: integer;
         property  EntityAttribute[entityNumber,attributeNumber:word]:double      read _GetAttributeValue          write _SetAttributeValue;
         procedure EntityAllocationTimeAdd(entityNumber:word; allocationType:TAllocationType; time:double);
         function  EntityCreate(TypeID:word):word;
         procedure EntityDispose(entityNumber:word; collectStatistics:boolean);
         procedure EntityInsertIntoQueue(entityNumber, moduleNumber, queueNumber:word);
         procedure EntityInsertIntoQueueByRank(entityNumber,moduleNumber, queueNumber, rank:word);
         function  EntityType(entityNumber:word): word;
         function  EntityNumber(entityNumber:word): word;
         procedure EntitySendToModuleLabel(entityNumber:word; moduleName:string; TimeDelay:double);
         procedure EntitySendToModuleNumber(entityNumber:word; moduleNumber:word; TimeDelay:double);
         procedure EntitySetPicture(entityNumber,newPicture:word);
         function  Eval(expression:string): double;
         property  FormulaCount:integer                              read _GetFormulaCount;
         property  FormulaName[index:integer]:string                 read _GetFormulaName;
         property  Formula[index:integer]:TFormula                read _GetFormulaObject;
         property  Formulas[index:integer;i,j:integer]:string        read _GetFormula     write _SetFormula;
         function  FormulaIndex(FormulaName:string):integer;
         property  FormulaValue[index:integer;i,j:integer]:double    read _GetFormulaValue;
         function  FailuresCount: integer;
         function  FailureName(failureNumber:word): string;
         function  FailureIndex(failureName:string): integer;
         function  FailureInsert(failureNumber:word; failureName:string; failureType:TFailureType; count:string;
                   upTime:string; upTimeUnit:TTimeUnit; downTime:string; downTimeUnit:TTimeUnit; stateOnly:boolean; UpTimeThisState:TResourceState):word;
         procedure FailureRemove(failureNumber:word);
         property  Failure[index:word]:TFailure                             read _GetFailure                write _SetFailure;
         property  Parent:TObject                                           read aParent                    write aParent;
         function  QueueInsert(queueNumber: word; queueName:string; queueType: TQueueType; queueAttribute:string): word;
         property  Queue[index:word]:TQueue                                 read _GetQueue                   write _SetQueue;
         function  QueueNumber(index:integer): word;
         function  QueueIndex(queueName:string): integer; overload;
         function  QueueIndex(queueNumber:word): integer; overload;
         function  QueuesCount: integer;
         property  QueueName[queueNumber:word]:string                       read _GetQueueName               write _SetQueueName;
         procedure QueueRemove(queueNumber:word);
         procedure QueueRemoveEntity(entityNumber, queueNumber:word);
         function  QueueEntityRank(queueNumber,rank:word):word;
         function  QueueNumberOfEntities(queueNumber:word): integer;
         property  Resource[index: word]: TResource                         read _GetResource                write _SetResource;
         function  ResourceIndex(resourceName:string): integer;
         function  ResourceInsert(resourceNumber:word; resourceName:string; resBusyNumber, resCapacity: word; resQueueName: string): word;
         function  ResourceName(resourceNumber:word): string;
         function  SampleBeta(alpha, beta, lowerLimit, upperLimit: double): double;
         function  SampleGamma(mean, alpha: double): double;
         function  SampleErlang(mean: double; M: integer): double;
         function  SampleExponential(mean:double): double;
         function  SampleLogNormal(mean, stddev:double): double;
         function  SampleNormal(mean,stddev:double): double;
         function  SampleUniform(min,max:double): double;
         function  SampleTriangular(min, mode, max: double): double;
         function  SampleWeibull(alpha, scale: double): double;
         property  SetNumber[setIndex:word]: word                       read _GetSetNumber;
         property  SetName[setNumber:word]: string                      read _GetSetName write _SetSetName;
         function  SetIndex(setName:string): integer;
         procedure SetRemove(setNumber:word);
         function  SetInsert(setNumber:word; setName:string; setType:string):word;
         procedure SetInsertMember(setNumber:word; memberName:string; memberIndex:integer);
         function  SetsCount: integer;
         function  SetMemberName(setNumber, memberIndex:word):string;
         function  SetMemberCount(setNumber:word):integer;
         property  Structures:TStringList                               read aModuleStructures;
         procedure ShowStatistics;
         function  StringEvaluateFormula(expression:string): double;
         property  VariableCount:integer                                read _GetVariableCount;
         property  Variable[index:integer]:TVariable                    read _GetVariable;
         property  Variables[index:integer]:string                      read _GetVariableName;
         function  VariableIndex(variableName:string): integer;
         property  VariableValue[index:integer;i,j:integer]:double      read _GetVariableValue  write _SetVariableValue;
      end;


      {Main class that manipulate models}
      TModel = class(TPersistent)
      private
         aSIMAN: TSIMAN;
         aAnalystName: string;
         aBaseTimeUnit: TTimeUnit;
         aBreakOnTime:double;
         aEntityPictures: TStringList;
         aFileName: string;
         aFullName: string;
         aInitializeStatistics: boolean;
         aInitializeSystem: boolean;
         aLastTimeTraceSimulation: double;
         aLastEntityTraceSimulation,
         aLastModuleTraceSimulation:word;
         aModules: TStringList; {list of lists, sorted by PlugIn.ID then by Module.ID}
         aName: string;
         aNumberOfReplications: word;
         aPath: string;
         aParent: TObject;
         aPauseBetween: boolean;
         aPauseRequest: boolean;
         aProjectTitle: string;
         aQueues: TStringList;
         aReplicationLenght: double;
         aReplicationLenghtTimeUnit: TTimeUnit;
         aReplicationStartTime: TdateTime; {only to calculate duration of simulation}
         aResourcePictures: TStringList;
         aRunning: boolean;
         aSaved: boolean;
         aStepByStep: boolean;
         aTerminatingCondition: string;
         aThisReplication: integer;
         aTNow: double;
         aTrace,
         aTraceReports: TProcTrace;
         aTraceSimulation: TProcTrace;
         aTraceLevel: byte; {0:NONE;  1:ERROR MESSAGES ONLY;     2:RESULTS OF METHODS;         3:1st LEVEL OF METHODS;         4:2nd LEVEL OF METHODS-DETAILED;       5:MOST DETAILED}
         aVersion: string;
         aWarmUpPeriod: double;
         aWarmUpPeriodTimeUnit: TTimeUnit;
         {eventos manipulados}
         aonBeginSimulation,
         aonBeginReplication,
         aonEndSimulation,
         aonEndReplication,
         aonDocumentOpen,
         aonDocumentClose,
         aonDocumentSave,
         aonNewEvent,
         aonEntityMove: TGenesysEventHandler;
         procedure _WriteInFile(var arq: text; wordsList: TStringList);
         procedure _BeginSimulation;
         function  _CheckSymbols: integer;
         function  _CheckAndAddInternalLiters: integer;
         function  _CheckConnected: integer;
         function  _CheckPathway: integer;
         function  _CheckActivationCode: integer;
         procedure _ContinueSimulation;
         procedure _CorrectIDs;
         procedure _EndOfSimulation;
         procedure _EndOfReplicationCleaness;
         function  _GenerateNewModuleID: word;
         function  _GenerateNewModuleName(kind:string):string;
         function  _GetModulesOfKind(kind:string): TStringList;
         function  _GetEntityPicture(index: integer): TEntityPicture;
         function  _LoadTextModel(fileName:string):integer;
         function  _LoadXMLModel(fileName:string):integer;
         procedure _SetEntityPicture(index: integer; picture:TEntityPicture);
         procedure _SaveProjectModule(var arq:text);
         procedure _SaveAttributesModule(var arq:text);
         procedure _SaveCStatsModule(var arq:text);
         procedure _SaveEntityTypesModule(var arq:text);
         procedure _SaveFormulaModule(var arq:text);
         procedure _SaveQueuesModule(var arq:text);
         procedure _SaveResourcesModule(var arq:text);
         procedure _SaveSetsModule(var arq:text);
         procedure _SaveVariablesModule(var arq:text);
         procedure _SaveStatisticsModule(var arq:text);
         procedure _SaveFailureModule(var arq:text);
         procedure _ReadProjectModule(wordsList:TStringList);
         procedure _ReadAttributesModule(wordsList:TStringList);
         procedure _ReadQueuesModule(wordsList:TStringList);
         procedure _ReadEntityTypeModule(wordsList:TStringList);
         procedure _ReadFormulaModule(wordsList:TStringList);
         procedure _ReadResourcesModule(wordsList:TStringList);
         procedure _ReadSetsModule(wordsList: TStringList);
         procedure _ReadVariablesModule(wordsList:TStringList);
         procedure _ReadCSTATModule(wordsList:TStringList);
         procedure _ReadFailureModule(wordsList:TStringList);
         procedure _ReadXMLProjectModule(XMLNode: IXMLNode);
         procedure _ReadXMLAttributesModule(XMLNode: IXMLNode);
         procedure _ReadXMLQueuesModule(XMLNode: IXMLNode);
         procedure _ReadXMLEntityTypeModule(XMLNode: IXMLNode);
         procedure _ReadXMLFormulaModule(XMLNode: IXMLNode);
         procedure _ReadXMLResourcesModule(XMLNode: IXMLNode);
         procedure _ReadXMLSetsModule(XMLNode: IXMLNode);
         procedure _ReadXMLVariablesModule(XMLNode: IXMLNode);
         procedure _ReadXMLCSTATModule(XMLNode: IXMLNode);
         procedure _ReadXMLFailureModule(XMLNode: IXMLNode);
         procedure _RecursiveConnectedTo(thisModule: TModule; var visited,  unconnected: TStringList; var drenoFOund:boolean);
         procedure _ReinitializeStatistics;
         procedure _ReinitializeSystem;
         procedure _SaveHeaderAndInternalStructures(var arq: text);
      public
         constructor Create(owner:TObject);
         destructor  Destroy;
         procedure Activate;
         property  AnalystName:string                                   read aAnalystName             write aAnalystName;
         property  BaseTimeUnit:TTimeUnit                               read aBaseTimeUnit            write aBaseTimeUnit;
         procedure BreakOnTime(time:double);
         function  Check: integer;
         procedure Close;
         property  EntityPictures[index:integer]:TEntityPicture         read _GetEntityPicture        write _SetEntityPicture;
         property  FileName:string                                      read aFileName;
         property  FullName:string                                      read aFullName;
         procedure Go;
         function  Load(fileName:string):integer;
         property  InitializeStatisticsBetweenReplications:boolean      read aInitializeStatistics    write aInitializeStatistics;
         property  InitializeSystemBetweenReplications:boolean          read aInitializeSystem        write aInitializeSystem;
         function  Module(index:word):TModule;
         function  ModuleByID(moduleNumber: word): TModule;
         procedure ModeleEdite(moduleNumBer: word; pointer1: pointer);
         function  ModuleCount: integer;
         function  ModuleType(index:word): string;
         procedure ModuleTypeInsert(newModuleType:string);
         function  ModuleAdd(kind:string): word;
         property  ModulesOfKind[kind:string]:TStringList               read _GetModulesOfKind;
         property  Name:string                                          read aName                    write aName;
         property  NumberOfReplications:word                            read aNumberOfReplications    write aNumberOfReplications;
         property  Parent:TObject                                       read aParent                  write aParent;
         property  Path:string                                          read aPath                    write aPath;
         procedure Pause;
         property  PauseBetweenReplications:boolean                     read aPauseBetween            write aPauseBetween;
         property  ProjectTitle:string                                  read aProjectTitle            write aProjectTitle;
         property  ReplicationLenght:double                             read aReplicationLenght       write aReplicationLenght;
         property  ReplicationLenghtTimeUnit:TTimeUnit                  read aReplicationLenghtTimeUnit write aReplicationLenghtTimeUnit;
         procedure Save;
         procedure SaveAs(filename:string; overwrite:boolean);
         property  Saved:boolean                                        read aSaved;
         property  SIMAN:TSIMAN                                         read aSIMAN                   write aSIMAN;
         procedure Step;
         procedure Stop;
         property  TerminatingCondition:string                          read aTerminatingCondition    write aTerminatingCondition;
         property  TNOW:double                                          read aTNOW;
         property  TraceHandler:TProcTrace                              read aTrace                   write aTrace;
         property  TraceReportsHandler:TProcTrace                       read aTraceReports            write aTraceReports;
         property  TraceSimulationHandler:TProcTrace                    read aTraceSimulation         write aTraceSimulation;
         property  TraceLevel:byte                                      read aTraceLevel              write aTraceLevel;
         procedure Trace(level:byte; text:string);
         procedure TraceSimulation(level:byte; moduleID,entityID:word;text:string);
         property  Version:string                                       read aVersion                 write aVersion;
         procedure ViewResults;
         procedure ViewSIMAN;
         property  WarmUpPeriod:double                                  read aWarmUpPeriod            write aWarmUpPeriod;
         property  WarmUpPeriodTimeUnit:TTimeUnit                       read aWarmUpPeriodTimeUnit    write aWarmUpPeriodTImeUnit;
      published
         property  OnBeginSimulation:TGenesysEventHandler                   read aonBeginSimulation       write aonBeginSimulation;
         property  OnBeginReplication:TGenesysEventHandler                  read aonBeginReplication      write aonBeginReplication;
         property  OnEndSimulation:TGenesysEventHandler                     read aonEndSimulation         write aonEndSimulation;
         property  OnEndReplication:TGenesysEventHandler                    read aonEndReplication        write aonEndReplication;
         property  OnDocumentOpen:TGenesysEventHandler                      read aonDocumentOpen          write aonDocumentOpen;
         property  OnDocumentClose:TGenesysEventHandler                     read aonDocumentClose         write aonDocumentClose;
         property  OnDocumentSave:TGenesysEventHandler                      read aonDocumentSave          write aonDocumentSave;
         property  OnNewEvent:TGenesysEventHandler                          read aonNewEvent              write aonNewEvent;
         property  OnEntityMove:TGenesysEventHandler                        read aonEntityMove            write aonEntityMove;
      end;


      {Main class that represents the entire simulator - all other class are aprt of this one}
      TGenesysApplication = class(TObject)
      private
         aActiveModelIndex: integer;
         aActiveModel: TModel;  {always contain the active model}
         aValidActivationCode: boolean;
         aModels: TStringList; {list of TModels}
         aPlugIns: TStringList; {list of TPlugIn, sorted by Kind}
         aFullName: string;
         aLicenseType: string;
         aName: string;
         aVersion: string;
         aVisible: boolean;
         aSafeMode: boolean;
         aFLAG: integer;  {used only for safe mode}
         aAuxFuncs: TAuxiliarFunctions;
         function  _GetActiveModel: TModel;
         function  _GetModel(name:string):TModel;
         procedure _SetActiveModel(model: TModel);
         function  _GetPlugIn(index:integer): TPlugIn;
         function  _GetPlugInCount: integer;
         procedure _VerifyInternalStructures;
      public
         constructor Create;
         destructor  Destroy; override;
         property  AuxFunctions:TAuxiliarFunctions                       read aAuxFuncs;
         property  Model:TModel                                          read _GetActiveModel           write _SetActiveModel;
         procedure ModelCreate;
         property  ModelActivedModel:integer                             read aActiveModelIndex         write aActiveModelIndex;
         procedure ModelSetActual(modelName:string);
         property  Models: TStringList                                   read aModels;
         property  FullName:string                                       read aFullName                 write aFullName;
         property  LicenseType:string                                    read aLicenseType;
         property  Name:string                                           read aName;
         property  PlugIn[index:integer]:TPlugIn                         read _GetPlugIn;
         function  PlugInID(kind:string):word;
         property  PlugInCount: integer                                  read _GetPlugInCount;
         function  PlugInIndexOf(kind:string): integer;
         function  PlugInAdd(fileName: string): string;
         function  PlugInDelete(fileName: string): string; {retorna o tipo ou nulo se falhou}
         procedure PlugInVerify(fileName: string; var infos:string); {returns if is a valid Genesys plug-in}
         property  SafeMode:boolean                                      read aSafeMode                 write aSafeMode;
         procedure Quit;
         function  SerialNumber:string;
         function  SetActivationCode(activationCode:string): boolean;
         property  Version:string                                        read aVersion;
         property  Visible:boolean                                       read aVisible                  write aVisible;
      end;


   var
      Genesys: TGenesysApplication;
      GenesysErrorMessage: string;

{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

{$IFNDEF KernelIsDLL}
IMPLEMENTATION

   uses
     Windows, Sysutils, buttons, Forms, extctrls,
     GenesysYacc, lexlib, yacclib, uGenerateActivationCode,
     xmldom, msxmldom, XMLDoc, OLE2
  {$IFDEF IsDLLPlugin}
     ;
  {$ELSE}
     , DllOrUnit;
  {$ENDIF}
{$ENDIF}


{ TRESOURCE }

{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

procedure TResource.Clear;
begin
   aNumberBusy := 0;
   aSeizes := 0;
   aState := rsIdle;
end;

constructor TResource.Create(novoId: word; novoNome: string);
begin
   inherited Create(novoId, novoNome, cRESOURCE);
   aCapacity := 0;
   aQueueName := '';
   aFailures := TStringList.Create;
   Clear;
   aCSTATTimeSeizedID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.TimeSeized', cRESOURCE);
end;

procedure TResource.Release(quantity: integer);
var cstats: TStringList;
    i: integer;
    timeSeized: double;
begin
   aNumberBusy := aNumberBusy - quantity;
   if aNumberBusy < 0 then aNumberBusy := 0;
   aNumberOut := aNumberOut + 1;
   timeSeized := Genesys.Model.TNOW - aWhenSeized;
   cstats := Genesys.Model.SIMAN._GetModuleStructuresByKind(cCSTAT);
   i := cstats.IndexOf(IntToStr(aCSTATTimeSeizedID));
   TCStat(cstats.Objects[i]).AddValue(timeSeized);
   aLastTimeSeized := timeSeized;
end;

procedure TResource.Seize(quantity: integer);
begin
   aNumberBusy := aNumberBusy + quantity;
   aSeizes := aSeizes + 1;
   aWhenSeized := Genesys.Model.TNOW;
end;

{ TWAITING }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

constructor TWaiting.Create(novaEntid, novoIdBloco: word);
begin
   inherited Create;
   aIdEntidade := novaEntid;
   aIdBloco := novoIdBloco;
end;


{ TQUEUE }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

procedure TQueue.Clear;
begin
   aEsperando.Clear;
end;

constructor TQueue.Create(novoId: word; novoNome: string);
//var newCSTAT: TCStat;
begin
   inherited Create(novoId, novoNome, cQUEUE);
   aTipo := qtFIFO;
   aAtributo := '';
   aEsperando := TStringList.Create;
   aEsperando.Sorted := false;  {será ordenado quando for inserido}
   aCSTATWaitingTimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.WaitingTime', cQUEUE);
   aCSTATNumberWaitingID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.NumberWaiting', cQUEUE);
   aModuleID := 0;
   aModuleInput := 0;
end;

destructor TQueue.Destroy;
var stats: TStringList;
    I: integer;
begin
   {clear queue}
   aEsperando.Clear;
   {destroy CStats}
   stats := Genesys.Model.SIMAN._GetModuleStructuresByKind(cCSTAT);
   i := stats.IndexOf(IntToStr(aCSTATWaitingTimeID));
   if i >=0 then begin
      stats.Objects[i].Destroy;
      stats.Delete(i);
   end;
   i := stats.IndexOf(IntToStr(aCSTATNumberWaitingID));
   if i >=0 then begin
      stats.Objects[i].Destroy;
      stats.Delete(i);
   end;
   inherited;
end;

procedure TQueue.InsertElement(element: TWaiting);
var position: integer;
    ordem: double;
    found: boolean;
begin
   {annotates the time when if was inserted into queue}
   element.aInsertedTime := Genesys.Model.TNOW;
   case aTipo of
      qtFIFO: begin
            position :=  aEsperando.Count;
            ordem := element.aIDEntidade;
         end;
      qtLVF: begin
           ordem := Genesys.Model.SIMAN.AttributeValue[aAtributo];
           position := 0;
           found := false;
           while (position < aEsperando.Count) and (not found) do begin
              found := StrToFloat(aEsperando.Strings[position]) > ordem;
              position := position + 1;
           end;
           if found then position := position - 1;
         end;
      qtHVF: begin
           ordem := Genesys.Model.SIMAN.AttributeValue[aAtributo];
           position := 0;
           found := false;
           while (position < aEsperando.Count) and (not found) do begin
              found := StrToFloat(aEsperando.Strings[position]) < ordem;
              position := position + 1;
           end;
           if found then position := position - 1;
         end;
      qtLIFO: begin
            position :=  aEsperando.Count;
            ordem := element.aIDEntidade;
         end;
   end;
   aEsperando.InsertObject(position, FloatToStr(ordem), element); {insere a posição adequada}
end;

function TQueue.RemoveElementByID(entityNumber: word): TWaiting;
var i: integer;
    found: boolean;
    aux: TWaiting;
begin
   i := 0;
   found := false;
   while (i < aEsperando.Count) and (not found) do begin
      found := TWaiting(aEsperando.Objects[i]).aIDEntidade = entityNumber;
      i := i + 1;
   end;
   if found then begin
      i := i - 1;
      aux := TWaiting(aEsperando.Objects[i]);
      _SetWaitingTimes(aux);
      aEsperando.Delete(i);
      result := aux;
   end else begin
      result := nil;
   end;
end;

function TQueue.RemoveElementByRank(ranking: integer): TWaiting;
var aux: TWaiting;
begin
   if ranking < aEsperando.Count then begin
      aux := TWaiting(aEsperando.Objects[ranking]);
      aEsperando.Delete(ranking);
      _SetWaitingTimes(aux);
      result := aux;
   end else begin
      result := nil;
   end;
end;

procedure TQueue._SetWaitingTimes(thisWait: TWaiting);
var timequeued: double;
    entities: TStringList;
    thisEnt: TEntity;
begin
   {time in witch the entity stayed in the queue}
   timequeued := Genesys.Model.TNOW - thisWait.aInsertedTime;
   {actualize queue cstat}
   Genesys.Model.SIMAN.CStatAddValue(self.aCSTATWaitingTimeID, timequeued);
   {actualize entity cstat}
   entities := Genesys.Model.SIMAN._GetModuleStructuresByKind(cENTITY);
   thisEnt := TEntity(entities.Objects[entities.IndexOf(IntToStr(thisWait.aIDEntidade))]);
   Genesys.Model.SIMAN.CStatAddValue(thisEnt.aCSTATWaitingTimeID, timequeued);
   Genesys.Model.TraceSimulation(cTLKernelIntern, thisWait.ModuleID, thisWait.EntityID, 'Entity waited in queue for '+FloatToStr(timequeued));
end;



{ TVariable }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

procedure TVariable.Clear;
begin
  { TODO 1 -oRafael Cancian -cNúcleo : Fazer todas as variáveis receberem novamente os valores iniciais para "zerá-las" entre replicações }
  Genesys.Model.Trace(cTLError,'Not implemented');
end;

constructor TVariable.Create(novoId: word; novoNome: string);
begin
   inherited Create(novoID, novoNome, cVARIABLE);
   aTamDimensao0 := 0;
   aTamDimensao1 := 0;
   aValores := TStringList.Create;
   aValores.Sorted := false; {não pode estar ordenado}
   aInitialValores := TStringList.Create;
   aInitialValores.Sorted := false;
end;


{ TEVENT }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

constructor TEvent.Create(novoInstante: double; novaEntid, novoId: word);
begin
   inherited Create(0,'T'+FloatToStr(novoInstante)+'E'+IntToStr(novaEntid)+'M'+IntToStr(novoID),cEVENT);
   aTime := novoInstante;
   aEntity := novaEntid;
   aModuleId := novoId;
end;


{ TMODULESTRUCTURE }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

constructor TModuleStructure.Create(novoId: word; novoNome, novoKind: string);
begin
//   inherited Create;
   aId := novoId;
   aName := novoNome;
   aKind := novoKind;
end;


procedure TModuleStructure._SetID(const Value: word);
begin
   aID := value;
end;

{ TMODULE }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

procedure TModule._SetIDProximo(index:integer; valor:word);
var i: integer;
begin
   { Sets hts ID of a connected module }
   try
      if index >= aIDNexts.Count then begin
         for i := aIDNexts.Count to index do begin
           aIDNexts.Add('0');
         end;
      end;
      aIDNexts.Strings[index] := IntToStr(valor);
   except
   end;
end;

constructor TModule.Create(novoId: word; novoNome, novoKind: string);
begin
   inherited;
   ///aDescription := novoNome;
   aIDNexts := TStringList.Create;
   aIDNexts.Sorted := false;
end;

function TModule._GetIDProximo(index:integer): word;
begin
   { Returns the ID of a connected module }
   if index < aIDNexts.Count then
      result := StrToInt(aIDNexts.Strings[index])
   else
      result := 0;
end;

function TModule._GetProximoCount: integer;
begin
   { Returns the number of connected modules }
   result := aIDNexts.Count;
end;


{ TENTITY}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

constructor TEntity.Create(novoId: word; novoNome: string);
begin
   inherited Create(novoId, novoNome, cENTITY);
   aAttributes := TStringList.Create;
   aAttributes.Sorted := false;
   aCSTATWaitingTimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.WaitingTime', cENTITY);
   aCSTATTransferTimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.TransferTime', cENTITY);
   aCSTATOtherTimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.OtherTime', cENTITY);
   aCSTATVATimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.VATime', cENTITY);
   aCSTATNVATimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.NVATime', cENTITY);
end;

function TEntity._GetAttribute(index: integer): double;
begin
   { Returns the value of the 'index'th attribute }
   if index < aAttributes.Count then
      result := StrToFloat(aAttributes.Strings[index])
   else
      result := 0;
end;

procedure TEntity._SetAttribute(index: integer; value: double);
var i: integer;
begin
   { Sets the value of the 'index'th attribute }
   if index >= aAttributes.Count then begin
      for i := aAttributes.Count to index do begin
         aAttributes.Add('0');
      end;
   end;
   aAttributes.Strings[index] := FloatToStr(value);
end;


{ TCSTAT }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

procedure TCSTAT.AddValue(valor: double);
begin
   { Adds a new value and actualizes the statistics }
   if aNumElementos = 0 then begin
      //primeiro valor
      aMinimum := valor;
      aMaximum := valor;
      aAcumulatedAverage := valor;
      aSumOfValues := valor;
      aSumOfSquareValues := valor * valor;
      aAcumulatedDeviation := 0;
      aIntervalo := 0;
      end
   else begin
      //acumula estatisticas
      if valor < aMinimum then aMinimum := valor;
      if valor > aMaximum then aMaximum := valor;
      aSumOfValues := aSumOfValues + valor;
      aSumOfSquareValues := aSumOfSquareValues + valor*valor;
      aAcumulatedAverage := ((aAcumulatedAverage * aNumElementos) + valor) / (aNumElementos + 1);
      aAcumulatedDeviation := Sqrt( (aSumOfSquareValues - (aSumOfValues * aSumOfValues / (aNumElementos + 1))) / aNumElementos);
      aIntervalo := aZCritico * aAcumulatedDeviation / Sqrt(aNumElementos+1);
   end;
   aLastValue := valor;
   aNumElementos := aNumElementos + 1;
   if aGravarLog and (aFileName <> '') then begin
      //gravar arquivo
   end;
end;

procedure TCSTAT.Clear;
begin
   { Reset the statistics }
   aMinimum := 0;
   aMaximum := 0;
   aAcumulatedAverage := 0;
   aAcumulatedDeviation := 0;
   aNumElementos := 0;
   aSumOfValues := 0;
   aSumOfSquareValues := 0;
   aIntervalo := 0;
   aLAstValue := 0;
end;

constructor TCSTAT.Create(newID:word; newName, newCategory:string);
begin
   inherited Create(newID, newName, cCSTAT);
   Clear;
   aGravarLog := false;
   aKeepAtualizated := true;
   aFileName := '';
   aZCritico := 1.96; // 95%
   aCategory := newCAtegory;
end;

procedure TCSTAT._SetConfianca(valor: double);
begin
   aZCritico := 1.96;
end;


{ TEntityType }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

constructor TEntityType.Create(novoID: word; novoNome: string);
begin
   inherited Create(novoID,novoNome, cENTITYTYPE);
   aInitialPicture := '';
   aInitialVACost := 0;
   aInitialNVACost := 0;
   aInitialOtherCost := 0;
   aInitialWaitingCost := 0;
   aCSTATWaitingTimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.WaitingTime', cENTITY);
   aCSTATTransferTimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.TransferTime', cENTITY);
   aCSTATOtherTimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.OtherTime', cENTITY);
   aCSTATVATimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.VATime', cENTITY);
   aCSTATNVATimeID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.NVATime', cENTITY);
   aCSTATTimeInSystemID := Genesys.Model.SIMAN.CStatInsert(Genesys.Model.SIMAN._GenerateNewStructureID, novoNome+'.TimeInSystem', cENTITY);
end;


{ TPLUG-IN }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}


constructor TPlugIn.Create;
begin
   inherited Create;
   aID := 0;
   aAcessa_Metodo := nil;
   aDLL := '';
   aTipo := '';
   aAutor := 'Rafael Luiz Cancian';
   aVersao  := '0';
   aDescricao :=  '';
   aFonte := false;
   aDreno := false;
   aVisual := false;
   aDependencies := '';
end;


{ TSIMAN }

{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}


function TSIMAN.QueueNumber(index: integer): word;
var queues: TStringList;
begin
   queues := _GetModuleStructuresByKind(cQUEUE);
   if (index >=0) and (index < queues.Count) then begin
      result := StrToInt(queues.Strings[index]);
   end else begin
      result := 0;
   end;
end;

function TSIMAN.CalendarCount: integer;
begin
   { Returns the number of events in the calendar }
   result := _GetModuleStructuresByKind(cEVENT).Count;
end;

function TSIMAN.CalendarGetNextEvent: TEvent;
var calendar: TStringList;
begin
   { Returns the next event and remove it from the Calendar }
   calendar := _GetModuleStructuresByKind(cEVENT);
   if Calendar.Count > 0 then begin
      result := TEvent(calendar.Objects[0]);
      calendar.Delete(0);
      end
   else begin
      result := nil;
   end;
end;

procedure TSIMAN.CalendarInsertEvent(time:double; entityID, moduleID:word);
var eventTimeStr: string;
    calendar: TStringList;
    anEvent: TEvent;
begin
   { Adds cronologically a new event in the calendar }
   //searches for the right position
   if time < 1e-300 then time := 0;  {for rounding purposes}
   eventTimeStr := Genesys.AuxFunctions.FillValueWithZeros(time,15);
   anEvent := TEvent.Create(time, entityID, moduleID);
   calendar := _GetModuleStructuresByKind(cEVENT);
   calendar.AddObject(eventTimeStr, anEvent);
end;

constructor TSIMAN.Create(owner:TObject);
var i: integer;
    attrs,events: TStringList;
begin
   inherited Create;
   aActiveEntity := 0;
   aACtiveModule := 0;
   aLastNewID := 0;
   aParent := owner;
   aRandom := TProbDistribs.Create;
   aModuleStructures := TStringList.Create; {list of lists}
   aModuleStructures.Sorted := true;
   {initialize known module structures}
   aModuleStructures.AddObject(cEVENT,TStringList.Create);
   aModuleStructures.AddObject(cENTITY,TStringList.Create);
   aModuleStructures.AddObject(cENTITYTYPE,TStringList.Create);
   aModuleStructures.AddObject(cATTRIBUTE,TStringList.Create);
   aModuleStructures.AddObject(cRESOURCE,TStringList.Create);
   aModuleStructures.AddObject(cQUEUE,TStringList.Create);
   aModuleStructures.AddObject(cVARIABLE,TStringList.Create);
   aModuleStructures.AddObject(cFORMULA,TStringList.Create);
   aModuleStructures.AddObject(cCSTAT,TStringList.Create);
   aModuleStructures.AddObject(cSET,TStringList.Create);
   aModuleStructures.AddObject(cFAILURE,TStringList.Create);
   {garante que as listas são ordenadas, com exceçao de atributos}
   for i := 0 to aModuleStructures.Count - 1 do begin
      if (aModuleStructures.Strings[i] = cATTRIBUTE) then
         TStringList(aModuleStructures.Objects[i]).Sorted := false
      else
         TStringList(aModuleStructures.Objects[i]).Sorted := true;
   end;
   {all entities have, at least, the following attributes}
   attrs := TStringList(aModuleStructures.Objects[aModuleStructures.IndexOf(cATTRIBUTE)]);
   attrs.Add('Entity.ArrivalTime');
   attrs.Add('Entity.JobStep');
   attrs.Add('Entity.Picture');
   attrs.Add('Entity.Sequence');
   attrs.Add('Entity.Station');
   attrs.Add('Entity.Type');
   attrs.Add('Entity.InputNumber');
   attrs.Add('Entity.QueuedNumber');
   events := TStringList(aModuleStructures.Objects[aModuleStructures.IndexOf(cEVENT)]);
   events.Sorted := true;
   events.Duplicates := dupAccept;
end;

function TSIMAN.EntityCreate(TypeID:word):word;
var newEntity: TEntity;
    i, numatribs: integer;
    entities, types: TStringList;
    newID: word;
    thisType: string;
//    found: boolean;
begin
   { Create data sctructure and attibutes for a new entity }
   entities := _GetModuleStructuresByKind(cENTITY);
   newID := aLastNewID + 1;
   aLastNewID := newID;
   newEntity := TEntity.Create(newID,'Entity'+IntToStr(newID));
   numatribs := _GetModuleStructuresByKind(cATTRIBUTE).Count;
   for i := 0 to numatribs-1 do begin
      newEntity.Attribute[i] := 0;
   end;
   newEntity.aTypeID := TypeID;
   {gets type}
   types := _GetModuleStructuresByKind(cENTITYTYPE);
   i := types.IndexOf(IntToStr(TypeID));
   thisType := TEntityType(types.Objects[i]).aName;
   {includes entity}
   entities.AddObject(IntToStr(newID), newEntity);
   result := newID;
   {set the arrival attribute}
   Genesys.Model.SIMAN.EntityAttribute[newID,Genesys.Model.SIMAN.AttributeIndex('Entity.ArrivalTime')] := Genesys.Model.TNOW;
   Genesys.Model.TraceSimulation(cTLModuleDetail,aActiveModule, aActiveEntity, 'Creating entity '+IntToStr(newID)+' of type "'+thisType+'"');
end;

procedure TSIMAN.EntityDispose(entityNumber: word; collectStatistics: boolean);
var i,j: integer;
    thisEnt: TEntity;
    thisEntType: TEntityType;
    entStat, typeStat: TCStat;
    entities, types, stats: TStringList;
    timeInSystem: double;
begin
   { Removes data structure of an entity and possibly calculate statistics }
   //Genesys.Model.Trace(6,'Disposing entity '+ IntToStr(entityNumber));
   Genesys.Model.TraceSimulation(cTLModuleDetail,aActiveModule, aActiveEntity, 'Disposing entity '+IntToStr(entityNumber));
   entities := _GetModuleStructuresByKind(cENTITY);
   i := entities.IndexOf(IntToStr(entityNumber));
   if i >= 0 then begin
      thisEnt := TEntity(entities.Objects[i]);
      {take CSTATS}
      stats := Genesys.Model.SIMAN._GetModuleStructuresByKind(cCSTAT);
      if collectStatistics then begin
         {collects information of the CSTATs and send then to general TEntityType CSTATs}
         {take the entitytype of this entity}
         types := _GetModuleStructuresByKind(cENTITYTYPE);
         j := types.IndexOf(IntToStr(thisEnt.aTypeID));
         thisEntType := TEntityType(types.Objects[j]);
         {transfer dieing entity CSTATs to persistent entitytype CTATs}
         entStat  := _GetCSTAT(thisEnt.aCSTATWaitingTimeID);
         typeStat := _GetCSTAT(thisEntType.aCSTATWaitingTimeID);
         typeStat.AddValue(entStat.Average);
         entStat  := _GetCSTAT(thisEnt.aCSTATTransferTimeID);
         typeStat := _GetCSTAT(thisEntType.aCSTATTransferTimeID);
         typeStat.AddValue(entStat.Average);
         entStat  := _GetCSTAT(thisEnt.aCSTATOtherTimeID);
         typeStat := _GetCSTAT(thisEntType.aCSTATOtherTimeID);
         typeStat.AddValue(entStat.Average);
         entStat  := _GetCSTAT(thisEnt.aCSTATVATimeID);
         typeStat := _GetCSTAT(thisEntType.aCSTATVATimeID);
         typeStat.AddValue(entStat.Average);
         entStat  := _GetCSTAT(thisEnt.aCSTATNVATimeID);
         typeStat := _GetCSTAT(thisEntType.aCSTATNVATimeID);
         typeStat.AddValue(entStat.Average);
         timeInSystem := Genesys.Model.SIMAN.AttributeValue['Entity.ArrivalTime'];
         timeInSystem := Genesys.Model.TNOW - timeInSystem;
         typeStat := _GetCSTAT(thisEntType.aCSTATTimeInSystemID);
         typeStat.AddValue(timeInSystem);
      end;
      //limpa a lista de atributos
      thisEnt.Attributes.Clear;
      {destroy this entity CSTATs}
      j := stats.IndexOf(IntToStr(thisEnt.aCSTATWaitingTimeID));
      if (j >= 0) then begin
         stats.Objects[j].Destroy;
         stats.Delete(j);
      end;
      j := stats.IndexOf(IntToStr(thisEnt.aCSTATTransferTimeID));
      if (j >= 0) then begin
         stats.Objects[j].Destroy;
         stats.Delete(j);
      end;
      j := stats.IndexOf(IntToStr(thisEnt.aCSTATOtherTimeID));
      if (j >= 0) then begin
         stats.Objects[j].Destroy;
         stats.Delete(j);
      end;
      j := stats.IndexOf(IntToStr(thisEnt.aCSTATVATimeID));
      if (j >= 0) then begin
         stats.Objects[j].Destroy;
         stats.Delete(j);
      end;
      j := stats.IndexOf(IntToStr(thisEnt.aCSTATNVATimeID));
      if (j >= 0) then begin
         stats.Objects[j].Destroy;
         stats.Delete(j);
      end;
      {remove entidade}
      entities.Objects[i].Destroy;
      entities.Delete(i);
   end;
end;

procedure TSIMAN.EntityInsertIntoQueue(entityNumber, moduleNumber, queueNumber: word);
var thisQueue: TQueue;
    thisWaiting: TWaiting;
begin
   thisQueue := _GetQueueByID(queueNumber);
   if thisQueue <> nil then begin
      thisWaiting := TWaiting.Create(entityNumber, moduleNumber);
      thisQueue.InsertElement(thisWaiting);
   end;
end;

procedure TSIMAN.EntityInsertIntoQueueByRank(entityNumber, moduleNumber, queueNumber, rank: word);
var thisQueue: TQueue;
    thisWaiting: TWaiting;
    ordem: double;
begin
   thisQueue := _GetQueueByID(queueNumber);
   if thisQueue <> nil then begin
      thisWaiting := TWaiting.Create(entityNumber, moduleNumber);
      case thisQueue.aTipo of
         qtFIFO: ordem := thisWaiting.aIDEntidade;
         qtLVF:  ordem := Genesys.Model.SIMAN.AttributeValue[thisQueue.aAtributo];
         qtHVF:  ordem := Genesys.Model.SIMAN.AttributeValue[thisQueue.aAtributo];
      end;
      if (rank > thisQueue.aEsperando.Count) then begin
         rank  := thisQueue.aEsperando.Count
      end;
      thisQueue.aEsperando.InsertObject(rank, FloatToStr(ordem), thisWaiting); {insere na posição adequada}
   end;
end;

function TSIMAN.EntityNumber(entityNumber: word): word;
begin
   { Transforms an entityNumber to an EntityNumber}
   result := entityNumber;
end;

procedure TSIMAN.EntitySendToModuleLabel(entityNumber:word; moduleName:string; TimeDelay:double);
//var moduleNumber: word;
begin
  //TRANSFORM NAME IN NUMBER AND ...
  //moduleNumber := ???
  //EntitySendToModuleNumber(entityNumber, ModuleNumber, TImeDelay);
end;

procedure TSIMAN.EntitySendToModuleNumber(entityNumber:word; moduleNumber:word; TimeDelay:double);
var i: integer;
    entities: TStringList;
    thisModule: TModule;
    thisQueue: TQueue;
    plugInIndex: word;
    thisPlugIn: TplugIn;
    point1,point2: pointer;
    wait: TWaiting;
begin
   { Sends immediatilly an entity to be executed by a plugin of a specified module or
     schedule an event to send the entity after a time delay }
   try
{      if TimeDelay = 0 then
         Genesys.Model.Trace(cTLTransfer,aActiveModule,entityNumber,'Entity is beeing sent to module '+IntToStr(moduleNumber))
      else
         Genesys.Model.Trace(cTLTransfer,aActiveModule,entityNumber,'Entity will be send to module '+IntToStr(moduleNumber) + ' at time '+FormatFloat('0.0000e+00', Genesys.Model.TNOW+TimeDelay));
}      aActiveEntity := entityNumber;    {updates active entity}
      aActiveModule := moduleNumber;    {updates active module}
      if @Genesys.Model.OnEntityMove  <> nil then Genesys.Model.OnEntityMove;
      entities := _GetModuleStructuresByKind(cENTITY);
      i := entities.IndexOf(IntToStr(entityNumber));
      if i >= 0 then begin
         {verify if sends now or schedule it}
         if TimeDelay = 0 then begin
            thisModule := Genesys.Model.ModuleByID(moduleNumber);
            if (thisModule = nil) then begin
               {can be a queue associated with a module}
               entities := _GetModuleStructuresByKind(cQUEUE); {entities are queues}
               i := entities.IndexOf(IntToStr(moduleNumber));
               if (i >= 0) then begin
                  {there is a queue with this ID}
                  thisQueue := TQueue(entities.Objects[i]);
                  i := Genesys.Model.SIMAN.AttributeIndex('Entity.InputNumber');
                  Genesys.Model.SIMAN.EntityAttribute[entityNumber, i] := thisQueue.aModuleInput;
                  i := Genesys.Model.SIMAN.AttributeIndex('Entity.QueuedNumber');
                  Genesys.Model.SIMAN.EntityAttribute[entityNumber, i] := thisQueue.ID;
                  wait := TWaiting.Create(entityNumber,moduleNumber);
                  thisQueue.InsertElement(wait);
                  if (thisQueue.ModuleID > 0) then begin
                     {takes the module associated with the queue}
                     thisModule := Genesys.Model.ModuleByID(thisQueue.ModuleID);
                  end;
               end;
            end;
            if (thisModule <> nil) then begin
               plugInIndex := Genesys.PlugInIndexOf(thisModule.Kind);
               if plugInIndex >= 0 then begin
                  thisPlugIn := Genesys.PlugIn[plugInIndex];
                  point1 := @thisModule;
                  point2 := @entityNumber;
                  thisPlugIn.aAcessa_Metodo(pmExecute, point1, point2);
               end;
               end
            else begin
               if (moduleNumber > 0) then
                  Genesys.Model.Trace(cTLError,'Error: Could not send entity '+IntToStr(entityNumber)+' to module '+IntToStr(moduleNumber))
               else begin
                  {negative module ID. Entity must be disposed}
                  Genesys.Model.SIMAN.EntityDispose(entityNumber,false);
               end;
            end;
            end
         else begin
            {schedule the entity to be sent to  next module at a future time}
            self.CalendarInsertEvent(Genesys.Model.TNOW + TimeDelay, entityNumber, moduleNumber);
         end;
      end
   except
      Genesys.Model.Trace(cTLError,'Error: Could not send entity '+IntToStr(entityNumber)+' to module '+IntToStr(moduleNumber));
   end;
end;

procedure TSIMAN.EntitySetPicture(entityNumber, newPicture: word);
begin
   { TODO 5 -oRafael Cancian -cNúcleo : Implementar figuras das entidades }
   Genesys.Model.Trace(cTLError,'Not implemented');
end;

function TSIMAN._GetAttributeValue(entitynum, atribnum: word): double;
var entities: TStringList;
    i: integer;
    attributes: TStringList;
begin
   { Returns the value of a speicifed attribute of an specified entity }
   entities := _GetModuleStructuresByKind(cENTITY);
   i := entities.IndexOf(IntToStr(entitynum));
   if i >= 0 then begin
      attributes := TEntity(entities.Objects[i]).Attributes;
      if atribnum <attributes.Count then
         result := StrToFloat(attributes.Strings[atribnum])
      else
         result := 0;
      end
   else begin
      result := 0;
   end;
end;

function TSIMAN._GetModuleStructuresByKind(kind: string): TStringList;
var i: integer;
begin
   { Returns a list of modules of a specified kind}
   i := aModuleStructures.IndexOf(kind);
   if i >= 0 then
      result := TStringList(aModuleStructures.Objects[i])
   else
      result := nil;
end;

function TSIMAN._GetQueue(index: word): TQueue;
var queues: TStringList;
begin
   { Returns a queue in the list }
   queues := _GetModuleStructuresByKind(cQUEUE);
   if index < queues.Count then
      result := TQueue(queues.Objects[index])
   else
      result := nil;
end;

function TSIMAN._GetResource(index: word): TResource;
var resources: TStringList;
begin
   { Returns a resource in the list }
   resources := _GetModuleStructuresByKind(cRESOURCE);
   if index < resources.Count then
      result := TResource(resources.Objects[index])
   else
      result := nil;
end;


function TSIMAN.CStatIndex(cstatNumber: word): integer;
var cstats: TStringList;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   result := cstats.IndexOf(IntToStr(cstatNumber));
end;

function TSIMAN._GetStatFile(cstatNumber: word): string;
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      result := TCSTAT(cstats.Objects[index]).FileName
   else
      result := '';
end;

procedure TSIMAN._SetStatFile(cstatNumber: word; const Value: string);
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      TCSTAT(cstats.Objects[index]).FileName := value;
end;

procedure TSIMAN._SetStatName(cstatNumber: word; const Value: string);
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      TCSTAT(cstats.Objects[index]).Name := Value;
end;

procedure TSIMAN.CStatClear(cstatNumber: word);
var i: integer;
    CStats: TStringList;
begin
   { Resets an statistic }
   CStats := _GetModuleStructuresByKind(cCSTAT);
   i := CStats.IndexOf(IntToSTr(cstatNumber));
   if i > -1 then begin
      TCStat(CStats.Objects[i]).Clear;
   end;
end;

function TSIMAN._GetStatAverage(cstatNumber: word): double;
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      result := TCSTAT(cstats.Objects[index]).Average
   else
      result := 0;
end;

function TSIMAN._GetStatHalfWidth(cstatNumber: word): double;
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      result := TCSTAT(cstats.Objects[index]).HalfWidth
   else
      result := 0;
end;

function TSIMAN._GetStatLastValue(cstatNumber: word): double;
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      result := TCSTAT(cstats.Objects[index]).LastValue
   else
      result := 0;
end;

function TSIMAN._GetStatName(cstatNumber: word): string;
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      result := TCSTAT(cstats.Objects[index]).Name
   else
      result := '';
end;

function TSIMAN._GetStatMaximum(cstatNumber: word): double;
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      result := TCSTAT(cstats.Objects[index]).Maximum
   else
      result := 0;
end;

function TSIMAN._GetStatMinimum(cstatNumber: word): double;
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      result := TCSTAT(cstats.Objects[index]).Minimum
   else
      result := 0;
end;

function TSIMAN._GetStatSize(cstatNumber: word): double;
var cstats: TStringList;
    index: integer;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   index := cstats.IndexOf(IntToStr(cstatNumber));
   if index >= 0 then
      result := TCSTAT(cstats.Objects[index]).Size
   else
      result := 0;
end;

function TSIMAN.QueueEntityRank(queueNumber, rank: word): word;
var thisQueue: TQueue;
begin
   thisQueue := _GetQueueByID(queueNumber);
   if thisQueue <> nil then begin
      if (rank >= 0) and (rank < thisQueue.aEsperando.Count) then
         result := TWaiting(thisQueue.aEsperando.Objects[rank]).aIDEntidade
      else
         result := 0;
      end
   else
      result := 0;
end;

function TSIMAN.QueueInsert(queueNumber: word; queueName:string; queueType: TQueueType;
  queueAttribute: string): word;
var queues: TStringList;
    newQueue: TQueue;
    i: integer;
begin
   { Insert a new queue in the list }
   queues := _GetModuleStructuresByKind(cQUEUE);
   if (queueNumber <= 0) then begin
      {it was asked to a new ID to be generated}
      queueNumber := _GenerateNewStructureID;
   end;
   if queues.IndexOf(IntToStr(queueNumber)) = -1 then begin
      {insert the new queue}
      queues.Add(IntToStr(queueNumber));{insert queue to have it´s ID registered}
      newQueue := TQueue.Create(queueNumber,queueName);
      newQueue.QueueType := queueType;
      newQueue.Attribute := queueAttribute;
      i := queues.IndexOf(IntToStr(queueNumber));
      queues.Objects[i] := newQueue;
      result := queueNumber;
      end
   else begin
      {it was given a specific ID and it already exists. Queue can not be inserted}
      result := 0; {invalid ID}
   end;
end;

function TSIMAN.QueueNumberOfEntities(queueNumber: word): integer;
var thisQueue: TQueue;
begin
   thisQueue := _GetQueueByID(queueNumber);
   if thisQueue <> nil then
      result := thisQueue.aEsperando.Count
   else {queue not found}
      result := -1;
end;

procedure TSIMAN.QueueRemoveEntity(entityNumber, queueNumber:word);
var thisQueue: TQueue;
    i: integer;
    found: boolean;
begin
   thisQueue := _GetQueueByID(queueNumber);
   if thisQueue <> nil then begin
      i := 0;
      found := false;
      while (i < thisQueue.aEsperando.Count) and (not found) do begin
         found := TWaiting(thisQueue.aEsperando.Objects[i]).aIDEntidade = entityNumber;
         i := i + 1;
      end;
      if found then begin
         { TODO : Contar estatísticas de quanto tempo a entidade ficou na fila }
         thisQueue.aEsperando.Objects[i-1].Destroy;
         thisQueue.aEsperando.Delete(i-1);
      end;
   end;
end;

function TSIMAN.ResourceInsert(resourceNumber:word; resourceName:string; resBusyNumber, resCapacity: word; resQueueName: string): word;
var resources: TStringList;
    newresource: TResource;
    i: integer;
begin
   { Insert a new resource in the list }
   resources := _GetModuleStructuresByKind(cRESOURCE);
   if resourceNumber <= 0 then begin
      {it was asked to a new ID to be generated}
      resourceNumber := _GenerateNewStructureID;
   end;
   if resources.IndexOf(IntToStr(resourceNumber)) = -1 then begin
      {insert the new resource}
      resources.Add(IntToStr(resourceNumber));
      newResource := TResource.Create(resourceNumber,resourceName);
      newResource.aNumberBusy := resBusyNumber;
      if resBusyNumber > 0 then
         newResource.aState := rsBUSY
      else
         newResource.aState := rsIDLE;
      newResource.Capacity := resCapacity;
      //newResource.WhenSeized := 0;
      //newResource.TimeSeized := 0;
      newResource.aNumberOut := 0;
      newResource.QueueName := resQueueName;
      i := resources.IndexOf(IntToStr(resourceNumber));
      resources.Objects[i] := newresource;
      result := resourceNumber;
      end
   else begin
      {it was given a specific ID and it already exists. Resource can not be inserted}
      result := 0; {invalid ID}
   end;
end;

function TSIMAN.Eval(expression:string): double;
var parser: TParser;
begin
  { Parses an expression and returns the associated value }
  try
     yyinput_text := expression;
     yyinit;
     parser := tparser.create;
     parser.parse;//(@Genesys);
     parser.free;
{     for i := 0 to yyoutput.Count-1 do begin
        writeln('  ::Parse:'+yyoutput.Strings[i]);
     end;}
     result := StrToFloat(yyoutput.Strings[yyoutput.Count-1]);
  except
     result := 0;
  end;
end;

function TSIMAN.SampleExponential(mean: double): double;
begin
   result := aRandom.Exponential(mean);
end;

function TSIMAN.SampleNormal(mean, stddev: double): double;
begin
   result := aRandom.Normal(mean, stddev);
end;

function TSIMAN.SampleUniform(min, max: double): double;
begin
   result := aRandom.Uniform(min,max);
end;

function TSIMAN.SampleGamma(mean, alpha: double): double;
begin
   result := aRandom.Gamma(mean, alpha);
end;

function TSIMAN.SampleTriangular(min, mode,max: double): double;
begin
   result := aRandom.Triangular(min,mode,max);
end;

function TSIMAN.SampleErlang(mean: double; M:integer): double;
begin
   result := aRandom.Erlang(mean,m);
end;

function TSIMAN.SampleBeta(alpha, beta, lowerLimit, upperLimit:double): double;
begin
   result := aRandom.Beta(alpha, beta, lowerLimit, upperlimit);
end;

function TSIMAN.SampleWeibull(alpha, scale:double): double;
begin
   result := aRandom.Weibull(alpha, scale);
end;

function TSIMAN.SampleLogNormal(mean, stddev:double): double;
begin
   result := aRandom.Lognormal(mean, stddev);
end;

procedure TSIMAN._SetAttributeValue(entitynum, atribnum: word; value: double);
var entities: TStringList;
    thisENtity: TEntity;
    index: integer;
begin
   { Sets the value of an specified attributed of an specified entity }
   if atribnum < _GetModuleStructuresByKind(cATTRIBUTE).Count then begin
      entities := _GetModuleStructuresByKind(cENTITY);
      index := entities.IndexOf(IntTostr(entityNum));
      if index >= 0 then begin
         thisEntity := TEntity(entities.Objects[index]);
         thisEntity.Attribute[atribnum] := value;
      end;
   end;
end;

procedure TSIMAN._SetQueue(index: word; thisQueue: TQueue);
begin
   { TODO 5 -oRafael Cancian -cNúcleo : Implementar _SetQueue }
   Genesys.Model.Trace(cTLError,'Not implemented');
end;

procedure TSIMAN._SetResource(index: word; thisResource: TResource);
begin
   { TODO 5 -oRafael Cancian -cNúcleo : Implementar _SetResource }
   Genesys.Model.Trace(cTLError,'Not implemented');
end;


function TSIMAN.StringEvaluateFormula(expression: string): double;
begin
   { Same as Eval }
   result := Eval(expression);
end;

destructor TSIMAN.Destroy;
var i,j: integer;
    aList: TStringList;
    aStructure: TModuleStructure;
begin
   for i := 0 to aModuleStructures.Count-1 do begin
      aList := TStringList(aModuleStructures.Objects[0]);
      for j := 0 to aList.Count-1 do begin
         aStructure := TModuleStructure(aList.Objects[0]);
         if aStructure <> nil then
            aStructure.Destroy;
         aList.Delete(0);
      end;
      aModuleStructures.Delete(0);
   end;
   aModuleStructures.Destroy;
   inherited;
end;

function TSIMAN._GetAttributeName(index: integer): string;
var attrs: TStringList;
begin
   { Returns the name of the 'index'th attribute }
   attrs := _GetModuleStructuresByKind(cATTRIBUTE);
   if index < attrs.Count then
      result := attrs.Strings[index]
   else
      result := '';
end;

function TSIMAN._GetVariableName(index: integer): string;
var aList: TStringList;
begin
   { Returns the name of a variable }
   aList := _GetModuleStructuresByKind(cVARIABLE);
   if index < aList.Count then begin
      result := aList.Strings[index];
      end
   else begin
      result := '';
   end;
end;

function TSIMAN._GetVariableValue(index, i, j: integer): double;
var aList: TStringList;
    thisVar: TVariable;
    strval: string;
begin
   { Returns tge value of a variable }
   aList := _GetModuleStructuresByKind(cVARIABLE);
   if index < aList.Count then begin
      thisVar := TVariable(aList.Objects[index]);
      if (i <= thisVar.Dimension1) and (j <= thisVar.Dimension2) then begin
         strVal := thisVar.Values.Strings[thisVar.Dimension1*(i-1) + (j-1)];
         Genesys.AuxFunctions.AdjustFloatFormat(strVal);  //troca ponto por vírgula
         result := StrToFloat(strVal);
         end;
      end
   else begin
      result := 0;
   end;
end;

function TSIMAN._GetAttributesCount: integer;
begin
   result := _GetModuleStructuresByKind(cATTRIBUTE).Count;
end;

function TSIMAN.QueueIndex(queueName: string): integer;
var filas: TStringList;
    i: integer;
    found: boolean;
begin
    filas := _GetModuleStructuresByKind(cQUEUE);
    found := false;
    i := 0;
    queueName := upperCase(queueName);
    while (i < filas.Count) and (not found) do begin
       found := UpperCase(TQUEUE(filas.Objects[i]).Name) = queueName;
       i := i + 1;
    end;
    if found then
       result := i - 1
    else
       result := -1;
end;

function TSIMAN.ResourceIndex(resourceName: string): integer;
var recursos: TStringList;
    i: integer;
    found: boolean;
begin
    recursos := _GetModuleStructuresByKind(cRESOURCE);
    found := false;
    i := 0;
    resourceName := UpperCase(resourceName);  
    while (i < recursos.Count) and (not found) do begin
       found := UpperCase(TResource(recursos.Objects[i]).Name) = resourceName;
       i := i + 1;
    end;
    if found then
       result := i - 1
    else
       result := -1;
end;

function TSIMAN._GetActualEntityAttributeValue(
  attributeName: string): double;
var attribnum, entitynum: integer;
    atributos, entidades: TStringList;
    entidade: TEntity;
begin
   atributos := _GetModuleStructuresByKind(cATTRIBUTE);
   attribnum := atributos.IndexOf(attributeName);
   if attribnum >=0 then begin
      entidades := _GetModuleStructuresByKind(cENTITY);
      entitynum := entidades.IndexOf(IntToStr(self.aActiveEntity));
      entidade := TEntity(entidades.Objects[entitynum]);
      result := entidade.Attribute[attribnum];
      end
   else begin
      //Erro. Atributo nao encontrado. Retorna 0.
      result := 0;
   end;
end;

procedure TSIMAN._SetActualEntityAttributeValue(attributeName: string;
  attributeValue: double);
var attribnum, entitynum: integer;
    atributos, entidades: TStringList;
    entidade: TEntity;
begin
   atributos := _GetModuleStructuresByKind(cATTRIBUTE);
   attribnum := atributos.IndexOf(attributeName);
   if attribnum >= 0 then begin
      entidades := _GetModuleStructuresByKind(cENTITY);
      entitynum := entidades.IndexOf(IntToStr(self.aActiveEntity));
      entidade := TEntity(entidades.Objects[entitynum]);
      entidade.Attribute[attribnum] := attributeValue;
      end
   else begin
      Genesys.Model.Trace(cTLError, 'Error: Attribute "'+attributeName+'" specified on module '+IntToStr(aActiveModule)+' was not found.');
   end;
end;

function TSIMAN._GetVariableCount: integer;
begin
   result := _GetModuleStructuresByKind(cVARIABLE).Count;
end;

function TSIMAN.AttributeIndex(attributeName: string): integer;
begin
   result := _GetModuleStructuresByKind(cATTRIBUTE).IndexOf(attributeName);
end;

function TSIMAN.VariableIndex(variableName: string): integer;
begin
   result := _GetModuleStructuresByKind(cVARIABLE).IndexOf(variableName);
end;

function TSIMAN._GetVariable(index: integer): TVariable;
var variables: TStringList;
begin
   { Returns a variable in the list }
   variables := _GetModuleStructuresByKind(cVARIABLE);
   if index < variables.Count then
      result := TVariable(variables.Objects[index])
   else
      result := nil;
end;

procedure TSIMAN._SetVariableValue(index, i, j: integer; value: double);
var aList: TStringList;
    thisVar: TVariable;
begin
   { Sets the value of a variable }
   aList := _GetModuleStructuresByKind(cVARIABLE);
   if index < aList.Count then begin
      thisVar := TVariable(aList.Objects[index]);
      if (i <= thisVar.Dimension1) and (j <= thisVar.Dimension2) then begin
         thisVar.Values.Strings[thisVar.Dimension1*(i-1) + (j-1)] := FloatToStr(value);
      end;
   end;
end;

function TSIMAN._GenerateNewStructureID: word;
var i, index: integer;
    newID: word;
    found: boolean;
    aList: TStringList;
begin
   newID := 1000;
   repeat
      i := 0;
      found := false;
      while (i < aModuleStructures.Count) do begin
         aList := TStringList(aModuleStructures.Objects[i]);
         index := aList.IndexOf(IntToSTr(newID));
         if index >=0 then begin
            i := aModuleStructures.Count; {exits}
            found := true;
         end;
         i := i + 1; {continue searching}
      end;
      newID := newID + 1;
   until not found;
   result := newID -1;
end;

function TSIMAN.ResourceName(resourceNumber: word): string;
var i: integer;
    resources: TStringList;
begin
   resources := _GetModuleStructuresByKind(cRESOURCE);
   i := resources.IndexOf(IntToStr(resourceNumber));
   if i >=0 then
      result := TResource(resources.Objects[i]).aName
   else
      result := '';
end;

function TSIMAN._GetQueueByID(queueID: word): TQueue;
var i: integer;
    queues: TStringList;
begin
   queues := _GetModuleStructuresByKind(cQUEUE);
   i := queues.IndexOf(IntToStr(queueID));
   if i >=0 then
      result := TQueue(queues.Objects[i])
   else
      result := nil;
end;

function TSIMAN._GetQueueName(queueID: word): string;
var thisQueue: TQueue;
begin
   thisQueue := _GetQueueByID(queueID);
   if thisQueue <> nil then
      result := thisQueue.aName
   else
      result := '';
end;

procedure TSIMAN._SetQueueName(queueID: word; queueName: string);
var thisQueue: TQueue;
begin
   thisQueue := _GetQueueByID(queueID);
   if thisQueue <> nil then
      thisQueue.aName := queueName;
end;

procedure TSIMAN.ShowStatistics;
var i: integer;
    text: string;
    thisCStat: TCStat;
    cstats: TStringList;
    tab: string;
begin
   if @Genesys.Model.aTraceReports <> nil then begin
      Genesys.Model.aTraceReports('Replication ' + IntToStr(Genesys.Model.aThisReplication) + '/'+IntToStr(Genesys.Model.NumberOfReplications) + ' Summary:');
      Genesys.Model.aTraceReports('SimulationTime:' + FloatToStr(Genesys.Model.TNOW));
      cstats := self._GetModuleStructuresByKind(cCSTAT);
      tab := '  ';
      for i :=0 to CStatsCount-1 do begin
         thisCStat := TCSTAT(cstats.Objects[i]);
         text := thisCStat.aCategory;
         text := text + tab + 'Name=' + thisCStat.Name;
         text := text + tab + 'Average=' + FloatToSTr(thisCStat.Average);
         text := text + tab + 'StdDev=' + FloatToSTr(thisCStat.aAcumulatedDeviation);
         text := text + tab + 'Half=' + FloatToSTr(thisCStat.HalfWidth);
         text := text + tab + 'Min=' + FloatToSTr(thisCStat.Minimum);
         text := text + tab + 'Max=' + FloatToSTr(thisCStat.Maximum);
         text := text + tab + 'Sum=' + FloatToSTr(thisCStat.TotalSum);
         text := text + tab + 'Num=' + FloatToSTr(thisCStat.Size);
         Genesys.Model.aTraceReports(text);
      end;
      Genesys.Model.aTraceReports('');
   end;
end;

function TSIMAN.CStatsCount: integer;
begin
   result := _GetModuleStructuresByKind(cCSTAT).Count;
end;

procedure TSIMAN.CStatAddValue(cstatNumber: word; newValue: double);
begin
   _GetCStat(cstatNumber).AddValue(newValue); 
end;

function TSIMAN.CStatInsert(cstatNumber: word; cstatName, cstatCategory: string): word;
var cstats: TStringList;
    newCStat: TCStat;
begin
   cstats := _GetModuleStructuresByKind(cCSTAT);
   if cstatNumber <= 0 then
      cstatNumber := _GenerateNewStructureID;
   if cstats.IndexOf(IntToStr(cstatNumber)) = -1 then begin
      newCStat := TCSTAT.Create(cstatNumber,cstatName, cstatCategory);
      cstats.AddObject(IntToStr(cstatNumber), newCStat);
      result := cstatNumber;
      end
   else
      result := 0;  {invalid ID}
end;

function TSIMAN._GetCStat(cstatNumber: word): TCStat;
var i: integer;
    cstats: TStringList;
begin
   cstats := self._GetModuleStructuresByKind(cCSTAT);
   i := cstats.IndexOf(IntToStr(cstatNumber));
   if i >= 0 then
      result := TCSTAT(cstats.Objects[i])
   else
      result := nil;
end;

function TSIMAN.QueueIndex(queueNumber: word): integer;
var queues: TStringList;
begin
   queues := _GetModuleStructuresByKind(cQUEUE);
   result := queues.IndexOf(IntToStr(queueNumber));
end;

function TSIMAN.QueuesCount: integer;
begin
   result := _GetModuleStructuresByKind(cQUEUE).Count;
end;

function TSIMAN.EntityType(entityNumber: word): word;
var i: integer;
    entidades: TStringList;
begin
   entidades := _GetModuleStructuresByKind(cENTITY);
   i := entidades.IndexOf(IntToStr(entityNumber));
   if i >=0 then
      result := TEntity(entidades.Objects[i]).aTypeID
   else
      result := 0;
end;

procedure TSIMAN.EntityAllocationTimeAdd(entityNumber: word;
  allocationType: TAllocationType; time: double);
var ents: TStringList;
    ent: TEntity;
    i: integer;
begin
   ents := _GetModuleStructuresByKind(cENTITY);
   i := ents.IndexOf(IntToStr(entityNumber));
   if i >= 0 then begin
      ent := TEntity(ents.Objects[i]);
      case allocationType of
         atWaitingTime:  self.CStatAddValue(ent.aCSTATWaitingTimeID, time);
         atTransferTime: self.CStatAddValue(ent.aCSTATTransferTimeID, time);
         atVATime:       self.CStatAddValue(ent.aCSTATVATimeID, time);
         atNVATime:      self.CStatAddValue(ent.aCSTATNVATimeID, time);
         atOtherTime:    self.CStatAddValue(ent.aCSTATOtherTimeID, time);
      end;
   end;
end;

procedure TSIMAN.QueueRemove(queueNumber: word);
var queues: TStringList;
    i: integer;
begin
   queues := _GetModuleStructuresByKind(cQUEUE);
   i := queues.IndexOf(IntToStr(queueNumber));
   if i >= 0 then begin
      TQueue(queues.Objects[i]).Destroy;
      queues.Delete(i);
   end;
end;

function TSIMAN._GetSetName(setNumber: word): string;
var sets:TStringList;
    index:integer;
begin
   sets := _GetModuleStructuresByKind(cSET);
   index := sets.IndexOf(IntToStr(setNumber));
   if (index > -1) then
      result := TSet(sets.Objects[index]).aName
   else
      result := '';
end;

function TSIMAN._GetSetNumber(setIndex: word): word;
var sets: TStringList;
begin
   sets := _GetModuleStructuresByKind(cSET);
   if setIndex < sets.Count then
      result := StrToInt(sets.Strings[setIndex])
   else
      result := 0;
end;

function TSIMAN.SetsCount: integer;
begin
   result := _GetModuleStructuresByKind(cSET).Count;
end;

function TSIMAN.SetMemberName(setNumber, memberIndex: word): string;
var sets: TStringList;
    thisSet: TSet;
    index:integer;
begin
   sets := _GetModuleStructuresByKind(cSET);
   index := sets.IndexOf(IntToStr(setNumber));
   if (index > -1) then begin
      thisSet := TSet(sets.Objects[index]);
      if (memberIndex < thisSet.aMembers.Count) then
         result := thisSet.aMembers.Strings[memberIndex]
      else
         result := '';
   end else
      result := '';
end;

function TSIMAN.SetMemberCount(setNumber: word): integer;
var sets: TStringList;
    thisSet: TSet;
    index:integer;
begin
   sets := _GetModuleStructuresByKind(cSET);
   index := sets.IndexOf(IntToStr(setNumber));
   if (index > -1) then begin
      thisSet := TSet(sets.Objects[index]);
      result := thisSet.aMembers.Count;
   end else
      result := 0;
end;

procedure TSIMAN._SetSetName(setNumber: word; const Value: string);
var sets:TStringList;
    index:integer;
begin
   sets := _GetModuleStructuresByKind(cSET);
   index := sets.IndexOf(IntToStr(setNumber));
   if (index > -1) then
      TSet(sets.Objects[index]).aName := value;
end;

function TSIMAN.SetInsert(setNumber: word; setName, setType: string): word;
var sets: TStringList;
    newSet: TSet;
    i: integer;
begin
   { Insert a new set in the list }
   sets := _GetModuleStructuresByKind(cSET);
   if (setNumber <= 0) then begin
      {it was asked to a new ID to be generated}
      setNumber := _GenerateNewStructureID;
   end;
   if sets.IndexOf(IntToStr(setNumber)) = -1 then begin
      {insert the new set}
      sets.Add(IntToStr(setNumber));{insert set to have it´s ID registered}
      newset := TSet.Create(setNumber,setName);
      newset.aMembersType := setType;
      i := sets.IndexOf(IntToStr(setNumber));
      sets.Objects[i] := newset;
      result := setNumber;
      end
   else begin
      {it was given a specific ID and it already exists. Set can not be inserted}
      result := 0; {invalid ID}
   end;
end;

procedure TSIMAN.SetInsertMember(setNumber: word; memberName: string; memberIndex: integer);
var sets: TStringList;
    thisSet: TSet;
    index:integer;
begin
   sets := _GetModuleStructuresByKind(cSET);
   index := sets.IndexOf(IntToStr(setNumber));
   if (index >= 0) then begin
      thisSet := TSet(sets.Objects[index]);
      if (memberIndex >= 0) and (memberIndex < thisSet.aMembers.Count) then
         thisSet.aMembers.Insert(memberIndex, memberName)
      else begin
         thisSet.aMembers.Add(memberName);
      end;
   end;
end;


function TSIMAN.SetIndex(setName: string): integer;
var sets: TStringList;
    i: integer;
    found: boolean;
begin
   sets := _GetModuleStructuresByKind(cSET);
   found := false;
   i := 0;
   setName := upperCase(setName);
   while (i < sets.Count) and not found do begin
      found := UpperCase(TSet(sets.Objects[i]).aName) = setName;
      i := i + 1;
   end;
   if found then
      result := i - 1
   else
      result := -1;
end;


function TSIMAN._GetFailure(index: word): TFailure;
begin

end;

procedure TSIMAN._SetFailure(index: word; const Value: TFailure);
begin

end;

function TSIMAN.FailureIndex(failureName: string): integer;
begin

end;

function TSIMAN.FailureInsert(failureNumber: word; failureName: string;
  failureType: TFailureType; count, upTime: string; upTimeUnit: TTimeUnit;
  downTime: string; downTimeUnit: TTimeUnit; stateOnly: boolean;
  UpTimeThisState: TResourceState): word;
var failures: TStringList;
    newFailure: TFailure;
begin
   failures := _GetModuleStructuresByKind(cFAILURE);
   if failureNumber <= 0 then
      failureNumber := _GenerateNewStructureID;
   if failures.IndexOf(IntToStr(failureNumber)) = -1 then begin
      newFailure := TFailure.Create(failureNumber, failureName);
      newFailure.aType := failureType;
      newFailure.aCount := count;
      newFailure.aUpTime := upTime;
      newFailure.aUpTimeUnit := upTimeUnit;
      newFailure.aDownTime := downTime;
      newFailure.aDownTimeUnit := downTimeUnit;
      newFailure.aStateOnly := stateOnly;
      newFailure.aUpTimeInThisStateOnly := upTimeThisState;
      failures.AddObject(IntToStr(failureNumber), newFailure);
      result := failureNumber;
      end
   else
      result := 0;  {invalid ID}
end;

function TSIMAN.FailureName(failureNumber: word): string;
var index: integer;
    failures: TStringList;
begin
   failures := _GetModuleStructuresByKind(cFAILURE);
   index := failures.IndexOf(IntToStr(failureNumber));
   if index >=0 then begin
      result := TFailure(failures.Objects[index]).aName;
   end else begin
      result := '';
   end;
end;

procedure TSIMAN.FailureRemove(failureNumber: word);
var index: integer;
    failures: TStringList;
begin
   failures := _GetModuleStructuresByKind(cFAILURE);
   index := failures.indexOf(IntToStr(failureNumber));
   if index >=0 then begin
      failures.Objects[index].Destroy;
      failures.Delete(index);
   end;
end;

function TSIMAN.FailuresCount: integer;
begin
   result := _GetModuleStructuresByKind(cFAILURE).Count;
end;

procedure TSIMAN.SetRemove(setNumber: word);
var index: integer;
    sets: TStringList;
begin
   sets := _GetModuleStructuresByKind(cSET);
   index := sets.indexOf(IntToStr(setNumber));
   if index >=0 then begin
      sets.Objects[index].Destroy;
      sets.Delete(index);
   end;
end;


{ TModel }

{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}


procedure TModel._EndOfSimulation;
begin
   if (aPauseRequest or aStepByStep) then begin
      {replication just paused}
      Trace(cTLReport,'Executing Replication '+IntToStr(Genesys.Model.aThisReplication) + '/' + IntToStr(Genesys.Model.aNumberOfReplications)+ '...');
      Trace(cTLReport,'Simulation Paused');
   end else begin
      {replication finished}
      if aInitializeSystem then begin
         {dispose all living entities}
         _EndOfReplicationCleaness;
      end;
      {show final report}
      TraceSimulation(cTLReport, 0,0,'End of replication '+IntToStr(Genesys.Model.aThisReplication) + '/' + IntToStr(Genesys.Model.aNumberOfReplications));
      TraceSimulation(cTLReport, 0,0, 'Simulation Time: ' + TimeToStr(Now - aReplicationStartTime));
      Trace(cTLReport,'');
      Trace(cTLReport,'End of replication '+IntToStr(Genesys.Model.aThisReplication) + '/' + IntToStr(Genesys.Model.aNumberOfReplications));
      Trace(cTLReport,'Simulation Time: ' + TimeToStr(Now - aReplicationStartTime));
      Trace(cTLReport,'');
      SIMAN.ShowStatistics;
      aRunning := false; {replication has ended}
      aThisReplication := aThisReplication + 1;
      {verifies if this events has to be handled}
      if @aOnEndReplication <> nil then aOnEndReplication;
      {prepare for next replication}
      if aThisReplication <= aNumberOfReplications then begin
         {this replication has been ended, but not the whole simulation. So, simulate one more replication}
         if aInitializeStatistics then begin
            {reinitialize statistics}
            _ReinitializeStatistics;
         end;
         if aInitializeSystem then begin
            {reinitialize model}
            _ReinitializeSystem;
         end;
         _BeginSimulation;
      end else begin
         {all replications have been simulated. Simulations has finished}
         {verifies if this events has to be handled}
         if @aOnEndSimulation <> nil then aOnEndSimulation;
      end;
   end;
end;

procedure TModel.Activate;
begin

end;

procedure TModel.Trace(level:byte; text: string);
begin
   //passa texto para interface
   if (level <= aTraceLevel) and (@aTrace <> nil) then begin
      //text := 'L:'+IntToStr(level)+' '+text;
      aTrace(text);
   end;
end;

procedure TModel._BeginSimulation;
var i, j, k, numEnts: integer;
    kind: string;
    entidade: word;
    Criacoes: TStringList;
    aSourceMod: TSourceModule;
    horario: String;
begin
   { Starts a new Replication}
   if (aThisReplication = 1) then begin
      if @aOnBeginSimulation <> nil then aOnBeginSimulation;
   end;
   if @aOnBeginReplication <> nil then aOnBeginReplication;
   i := 0;
   aReplicationStartTime := Now;
   Trace(cTLReport,'----------------------------------------------------------------');
   Trace(cTLReport, Genesys.AuxFunctions.StrIdent(2)+'GenESyS - Generic Expansible Systems Simulator');
   Trace(cTLReport, Genesys.AuxFunctions.StrIdent(2)+'ZeroUm Solucoes LTDA');
   Trace(cTLReport, Genesys.AuxFunctions.StrIdent(2)+'License Type: ' + Genesys.LicenseType);
   Trace(cTLReport,'');
   Trace(cTLReport, Genesys.AuxFunctions.StrIdent(1)+'Trace for Replication '+ IntToStr(aThisReplication) + ' of '+IntToStr(aNumberOfReplications));
   Trace(cTLReport,'');
   Trace(cTLReport,'Project Title: '+aProjectTitle);
   Trace(cTLReport,'Analyst Name: ' +aAnalystName);
   DateTimeToString(horario, 'dd/mm/yyyy "-" hh:nn:ss', Now);
   Trace(cTLReport,'Execution Date: ' + horario);
   Trace(cTLReport,'Trace Level: ' + IntToStr(aTraceLevel));
   Trace(cTLReport,' ');
   TraceSimulation(cTLReport, 0,0, 'Trace for Replication '+ IntToStr(aThisReplication) + ' of '+IntToStr(aNumberOfReplications));
   {creates the very first entities}
   while (i < Genesys.PlugInCount) do begin
      if Genesys.PlugIn[i].Source then begin
         kind := Genesys.PlugIn[i].Kind;
         //localiza a entrada no dicionário de blocos
         Criacoes := ModulesOfKind[kind];
         if Criacoes <> nil then begin
            for j := 0 to Criacoes.Count - 1 do begin
               //para cada bloco CRIACAO, agenda eventos de chegada
               aSourceMod := TSourceModule(Criacoes.Objects[j]);
               numEnts := trunc(SIMAN.StringEvaluateFormula(aSourceMod.EntitiesPerCreation));
               for k := 1 to numEnts do begin
                  entidade := SIMAN.EntityCreate(aSourceMod.aEntityTypeID);
                  SIMAN.CalendarInsertEvent(aSourceMod.FirstCreation, entidade, aSourceMod.ID);
               end;
            end;
         end;
      end;
      i := i + 1;
   end;
   SIMAN.aActiveEntity := 0;
   SIMAN.aActiveModule := 0;
   if SIMAN.CalendarCount > 0 then begin
      aRunning := true;
      _ContinueSimulation;
      end
   else begin
      Genesys.Model.Trace(cTLReport, 'No events to simulate.');
      _EndOfSimulation;
   end;
end;

procedure TModel._ContinueSimulation;
var nextEvent: TEvent;
begin
   { Simulation Main Loop }
   repeat
      nextEvent := SIMAN.CalendarGetNextEvent;
      if (aBreakOnTime > aTNOW) and (aBreakOnTime <= nextEvent.Time) then aPauseRequest := true;
      aTNOW := nextEvent.Time;  {advances the simulation time}
      if (aReplicationLenght = -1) or (aTNOW <= aReplicationLenght) then begin
          {the simulation keeps going. Now the event will be treated}
          if @aOnNewEvent <> nil then aOnNewEvent; {A ENTIDADE ATIVA AINDA É ANTIGA}
          SIMAN.EntitySendToModuleNumber(nextEvent.Entity, nextEvent.ModuleID, 0);
      end;
      Application.ProcessMessages;
   until aStepByStep or aPauseRequest or (SIMAN.CalendarCount = 0) or ((aTNOW > aReplicationLenght) and (aReplicationLenght > -1));
   _EndOfSimulation;
end;

constructor TModel.Create(owner:TObject);
var i: integer;
    WinTempDir: array[0..255] of Char;
begin
   inherited Create;
   {initializes the attributes}
   aSIMAN := TSIMAN.Create(self);
   aAnalystName := '';
   aBaseTimeUnit := tuS; {first in list}
   aBreakOnTime := -1;
   aEntityPictures := TStringList.Create;
   aEntityPictures.Sorted := true;  {sorted by name}
   aInitializeStatistics := true;
   aInitializeSystem := true;
   aLastTimeTraceSimulation := -1;   {starts with a negative time}
   aLastEntityTraceSimulation := 0;  {starts with an invalid id}
   aLastModuleTraceSimulation := 0;  {idem}
   aModules := TStringList.Create;
   aModules.Sorted := true;  {sorted by kindnum}
   { TODO 5 -oRafael Cancian -cNúcleo : Verificar se é realmente necessário iniciar com nome }
   //// INICIALIZAR MODULOS COM O NOME DOS PLUG-INS EXISTENTES ////

   {O nome do arquivo do modelo eh iniciado com o mesmo nome do modelo}
   {E o diretorio-padrao eh o diretorio temporario do windows}
   i := Genesys.Models.Count;
   aName := 'Model ' + IntToStr(i+1);
   GetTempPath(SizeOf(WinTempDir) - 1, WinTempDir);
   aFullName := WinTempDir + 'Model_' + IntToStr(i+1) + '.txt';
   Genesys.AuxFunctions.SeparatePathAndFileName(aFullName, aPath, aFileName);
   aNumberOfReplications := 1;
   aPauseBetween := false;
   aPauseRequest := false;
   aProjectTitle := 'My Genesys Project';
   aAnalystName := 'My name';
   aQueues := TStringList.Create;
   aQueues.Sorted := true;
   aReplicationLenght := 0;
   aReplicationLenghtTimeUnit := tuS;
   aResourcePictures := TStringList.Create;
   aResourcePictures.Sorted := true;
   aRunning := false;
   aSaved := true;
   aStepByStep := false;
   aTerminatingCondition := '';
   aThisReplication := 1;
   aTNOW := 0;
   aTrace := nil;
   aTraceReports := nil;
   aTraceSimulation := nil;
   aTraceLevel := 9; //cTLModuleDetail;
   aWarmUpPeriod := 0;
   aWarmUpPeriodTimeUnit := tuS;
   {eventos manipulados}
   aOnBeginSimulation := nil;
   aOnBeginReplication := nil;
   aOnEndSimulation := nil;
   aOnEndReplication := nil;
   aOnDocumentOpen := nil;
   aOnDocumentClose := nil;
   aOnDocumentSave := nil;
   aOnNewEvent := nil;
   aOnEntityMove := nil;
end;

function TModel._GetModulesOfKind(kind: string): TStringList;
var i: integer;
begin
   { Returns a list with modules of a specified kind }
   i := aModules.IndexOf(kind);
   if i >= 0 then
      result := TStringList(aModules.Objects[i])
   else
      result := nil;
end;

procedure TModel.Go;
begin
   { Starts a simulation }
   aPauserequest := false;
   aStepByStep := false;
   if not aRunning then begin
      if Check >= 0 then
          _BeginSimulation;
      end
   else
      if Check >=0 then
         _ContinueSimulation;
end;

function TModel.ModuleByID(moduleNumber: word): TModule;
var i,j: integer;
    aList: TStringList;
    found: boolean;
begin
   {Returns the }
   i := 0;
   found := false;
   while (i < aModules.Count) and (not found) do begin
      aList := TStringList(aModules.objects[i]);
      if aList <> nil then begin
         j := aList.IndexOf(IntToStr(moduleNumber));
         if j > -1 then begin
            found := true;
            result := TModule(aList.Objects[j]);
         end;
      end;
      i := i + 1;
   end;
   if not found then result := nil;
end;

function TModel.Module(index: word): TModule;
var i, sum: integer;
    aList: TStringList;
    found: boolean;
begin
   {Returns the 'index'th module in the dictionary }
   i := 0;
   sum := 0;
   found := false;
   while (i < aModules.Count) and (not found) do begin
      aList := TStringList(aModules.Objects[i]);
      if sum + aList.Count - 1 < index then begin
         i := i + 1;
         sum := sum + aList.Count;
         end
      else begin
         found := true;
      end;
   end;
   if not found then
      result := nil
   else
      result := TModule(aList.Objects[index-sum]);
end;

procedure TModel.Pause;
begin
   aPauseRequest := true;
end;

procedure TModel._WriteInFile(var arq: text; wordsList: TStringList);
var i: integer;
    texto: string;
begin
   { Wtite the words of a list in a file, separated by a ';' }
   if wordsList.Count > 0 then begin
      texto := wordsList.Strings[0];
      for i := 1 to wordsList.Count - 1 do begin
         texto := texto + ';' + wordsList.Strings[i];
      end;
      writeln(arq, texto);
   end;
end;

procedure TModel.Save;
begin
   SaveAs(aFullName, false);
end;

procedure TModel._SaveHeaderAndInternalStructures(var arq: text);
begin
   { Save a header and internal structure in a file }
   writeln(arq,'####################################################');
   writeln(arq,'# Genesys - Generic Expansible Systems Simulator   #');
   writeln(arq,'#                                                  #');
   writeln(arq,'# ZeroUm Assessoria e Informatica LTDA             #');
   writeln(arq,'# phone: +55(47)9955-6658                          #');
   writeln(arq,'# email: cancian@univali.br, cancian@inf.ufsc.br   #');
   writeln(arq,'#                                                  #');
   writeln(arq,'# Genesys Model File - Editable text format        #');
   writeln(arq,'####################################################');
   writeln(arq,'# Saved in: ' + DateTimeToStr(now));
   writeln(arq,'# Internal Structures:');
   _SaveProjectModule(arq);
   _SaveEntityTypesModule(arq);
   _SaveAttributesModule(arq);
   _SaveQueuesModule(arq);
   _SaveResourcesModule(arq);
   _SaveVariablesModule(arq);
   _SaveFormulaModule(arq);
   _SaveSetsModule(arq);
   _SaveCStatsModule(arq);
   _SaveFailureModule(arq);
   writeln(arq,'');
end;

procedure TModel.SaveAs(filename: string; overwrite: boolean);
var arq: text; //file of text
    i, j,
    index: integer;
    umPlugIn: TPlugIn;
    umBloco: TModule;
    umaLista: TStringList;
    wordsList: TStringList;
    pointer1, pointer2: pointer;
begin
   { Saves the current model in a file }
 try
   if (FileExists(FileName) and overwrite) or (not FileExists(FileName)) then begin
      Trace(3,'Saving model "' + FileName + '"...');
      wordsList := TStringList.Create;
      wordsList.Sorted := false;  {não pode estar ordenado}
      assignFile(arq, FileName);
      rewrite(arq);
      _SaveHeaderAndInternalStructures(arq);
      writeln(arq,'');
      writeln(arq,'# Plug-in Modules:');
      //varre o dicionário de blocos salvando cada bloco
      i := 0;
      while i < aModules.Count do begin
         umaLista := TStringList(aModules.Objects[i]);
         //takes the corresponding PlugIn
         index := Genesys.PlugInIndexOf(aModules.Strings[i]);
         if index >= 0 then begin
            umPlugIn := Genesys.PlugIn[index];
            // varre os blocos desse tipo
            j := 0;
            while j < umaLista.Count do begin
               wordsList.Clear;
               umBloco := TModule(umaLista.Objects[j]);
               Trace(4, Genesys.AuxFunctions.StrIdent(1)+'- Saving: '+umPlugIn.Kind+' -> '+umBloco.Name+'('+IntToStr(umBloco.ID)+')');
               pointer1 := @umBloco;
               pointer2 := @wordsList;
               umPlugIn.aAcessa_Metodo(pmSaveModule, pointer1, pointer2);
               _WriteInFile(arq, wordsList);
               j := j + 1;
            end;
         end;
         i := i + 1;
      end;
      CloseFile(arq);
      Trace(2,'Ok');
      Trace(2,'');
      aFullName := fileName;
      Genesys.AuxFunctions.SeparatePathAndFileName(fileName, aPath, aFileName);
      {verifica se o evento deve ser manipulado}
      if @aOnDocumentSave <> nil then aOnDocumentSave;
   end;
 except
   Trace(cTLError,'Error saving the model "' + fileName + '"');
   Trace(cTLError,'');
   try
       CloseFile(arq);
   except
   end;
 end;
end;


procedure TModel.Step;
begin
   { Executes a step of simulation }
   aPauseRequest := false;
   aStepByStep := true;
   if not aRunning then begin
      if Check >= 0 then _BeginSimulation
      end
   else
      if Check >= 0 then _ContinueSimulation;
end;

procedure TModel.Stop;
begin
   aPauseRequest := true;
   aRunning := false;  //nedded?
end;


function TModel._CheckActivationCode: integer;
var i: integer;
    contModules, contStructures: integer;
    thisList: TStringList;
begin
   Trace(cTLModuleIntern, Genesys.AuxFunctions.StrIdent(1)+'- Verifying activation code');
   if Genesys.aValidActivationCode then
      result := 0
   else begin
      contModules := 0;
      contStructures := 0;
      thisList := self.aModules;
      for i := 0 to thisList.Count-1 do begin
         contModules := contModules + TStringList(thisList.Objects[i]).Count;
      end;
      thisList := aSIMAN.aModuleStructures;
      for i := 0 to thisList.Count-1 do begin
         contStructures := contStructures + TStringList(thisList.Objects[i]).Count;
      end;
      if contModules * 3 + contStructures > 35 then begin
         result := -1; {error: model over limit}
         Genesys.Model.Trace(cTLError,'Error: Genesys Kernel has no valid activation code and model is overlimited to academic licence.');
         Genesys.Model.Trace(cTLError,'       You need to decrease the number of model''s modules/structures or to get a valid activation code.');
      end else
         result := 0; {ok. Model under the limit}
   end;
end;

function TModel._CheckSymbols: integer;
var i,j, plugInIndex: integer;
    aList: TStringList;
    thisModule: TModule;
    thisPlugIn: TPlugIn;
    point1, point2: pointer;
    erro: string;
begin
   { Verify if all symbols were declared or are known }
   try
      erro := '';
      i := 0;
      Trace(cTLModuleIntern, Genesys.AuxFunctions.StrIdent(1)+'- Verifying modules symbols');
      while (i < aModules.Count) and (erro = '') do begin
         aList := TStringList(aModules.Objects[i]);
         j := 0;
         while(j < aList.Count) and (erro = '') do begin
            thisModule := TModule(aList.Objects[j]);
            plugInIndex := Genesys.PlugInIndexOf(thisModule.Kind);
            if plugInIndex >= 0 then begin
               thisPlugIn := Genesys.PlugIn[plugInIndex];
               point1 := @thisModule;
               thisPlugIn.aAcessa_Metodo(pmVerifySymbols, point1, point2);
               if point1 <> nil then
                  erro := string(point1^)
               else
                  erro := '';
            end;
            j := j + 1;
         end;
         i := i + 1;
      end;
   except
      erro := 'Invalid operation';
   end;
   if erro = '' then
      result := 0 {ok}
   else
      result := -1; {error}
end;

function TModel.Check: integer;
var aux: integer;
begin
   { Verifiy the model and look for errors }
   {return -1 or less if error. 0 is sucessful}
   Trace(cTLModule, Genesys.AuxFunctions.StrIdent(1)+'- Checking Model Consistency');
   aux := _CheckAndAddInternalLiters;
   if aux >= 0 then aux := _CheckConnected;
   if aux >= 0 then aux := _CheckSymbols;
   if aux >= 0 then aux := _CheckPathway;
   if aux >= 0 then aux := _CheckActivationCode;
   result := aux;
end;

procedure TModel.ViewResults;
begin
   { TODO 3 -oRafael Cancian -cNúcleo : Implementar ViewResults }
   SIMAN.ShowStatistics;
   //Genesys.Model.Trace(cTLError,'Not implemented');
end;

procedure TModel.ViewSIMAN;
begin
   { TODO 4 -oRafael Cancian -cNúcleo : Implementar ViewSIMAN }
   Genesys.Model.Trace(cTLError,'Not implemented');
end;

procedure TModel._ReadFormulaModule(wordsList: TStringList);
var umaVar: TFormula;
    Variaveis: TStringList;
    i, j, k: integer;
    newID: word;
begin
  try
   variaveis := SIMAN._GetModuleStructuresByKind(cFORMULA) ;
   i := 1;
   while i < wordsList.Count do begin
      newID := variaveis.Count + 1;
      umaVar := TFormula.Create(newID,'');
      umaVar.Name := Genesys.AuxFunctions.Underscore(wordsList.Strings[i]);
      umaVar.Dimension1 := StrToInt(wordsList.Strings[i+1]);
      umaVar.Dimension2 := StrToInt(wordsList.Strings[i+2]);
      umaVar.Values := TStringList.Create;
      umaVar.Values.Sorted := false;  {não pode estar ordenado}
      i := i + 3;
      for j := 1 to umaVar.Dimension1 do begin
         for k := 1 to umaVar.Dimension2 do begin
            umaVar.Values.Add(wordsList.Strings[i]);
            umaVar.InitialValues.Add(wordsList.Strings[i]);
            i := i + 1;
          end;
      end;
      variaveis.AddObject(umaVar.Name, TObject(umaVar));  {ordenado por nome, não ID - até poderia ser por ID}
   end;
  except
      Trace(cTLError,'Error loading "' + wordsList.Strings[0] + '" module');
  end;
end;

procedure TModel._SaveFormulaModule(var arq: text);
var i,j: integer;
    aList: TStringList;
    wordsList: TStringList;
    thisVariable: TVariable;
begin
   { Saves the Formula Module returning its names, dimensions and initial values }
   wordsList := TStringList.Create;
   wordsList.Sorted := false;
   //save description of fields
   wordsList.Add('# ' +cFORMULA+ '; Name; Dimension1; Dimension2; Value[1,1]; Value[2,1]; ...; Value[Dimension1,1]; Value[1,2]; Value[2,2]...; Value[2,Dimension1]; Value[3,1]; ... Value[Dimension1,Dimension2]');
   _WriteInFile(arq, wordsList);
   wordsList.Clear;
   //save the module
   aList := SIMAN._GetModuleStructuresByKind(cFORMULA);
   if aList.Count > 0 then begin
      for i := 0 to aList.Count - 1 do begin
         wordsList.Clear;
         wordsList.Add(cFORMULA);
         thisVariable := TVariable(aList.Objects[i]);
         //wordsList.Add(IntToStr(thisVariable.ID));
         wordsList.Add(thisVariable.Name);
         wordsList.Add(IntToStr(thisVariable.Dimension1));
         wordsList.Add(IntToStr(thisVariable.Dimension2));
         for j := 0 to thisVariable.InitialValues.Count - 1 do begin
            wordsList.Add(thisVariable.InitialValues.Strings[j]);
         end;
         _WriteInFile(arq, wordsList);
      end;
   end;
end;

function TSIMAN.FormulaIndex(FormulaName: string): integer;
begin
   result := _GetModuleStructuresByKind(cFORMULA).IndexOf(FormulaName); 
end;

function TSIMAN._GetFormulaObject(index: integer): TFormula;
var aList: TStringList;
begin
   { Returns the object TFormula }
   aList := _GetModuleStructuresByKind(cFORMULA);
   if index < aList.Count then begin
      result := TFormula(aList.Objects[index]);
   end else begin
      result := nil;
   end;
end;

function TSIMAN._GetFormula(index, i, j: integer): string;
var aList: TStringList;
    thisVar: TFormula;
begin
   { Returns the string expression of an Formula }
   aList := _GetModuleStructuresByKind(cFormula);
   if index < aList.Count then begin
      thisVar := TFormula(aList.Objects[index]);
      if (i <= thisVar.Dimension1) and (j <= thisVar.Dimension2) then begin
         result := thisVar.Values.Strings[thisVar.Dimension1*(i-1) + (j-1)];
      end;
   end else begin
      result := '';
   end;
end;

function TSIMAN._GetFormulaCount: integer;
begin
   result := _GetModuleStructuresByKind(cFORMULA).Count;
end;

function TSIMAN._GetFormulaName(index: integer): string;
var aList: TStringList;
begin
   { Returns the name of an formula }
   aList := _GetModuleStructuresByKind(cFORMULA);
   if index < aList.Count then begin
      result := aList.Strings[index];
   end else begin
      result := '';
   end;
end;

function TSIMAN._GetFormulaValue(index, i, j: integer): double;
var express: String;
begin
   express := _GetFormula(index, i, j);
   result := self.Eval(express);
end;

procedure TSIMAN._SetFormula(index, i, j: integer; const Value: string);
var aList: TStringList;
    thisVar: TFormula;
begin
   { Sets the string expression of an Formula }
   aList := _GetModuleStructuresByKind(cFORMULA);
   if index < aList.Count then begin
      thisVar := TFormula(aList.Objects[index]);
      if (i <= thisVar.Dimension1) and (j <= thisVar.Dimension2) then begin
         thisVar.Values.Strings[thisVar.Dimension1*(i-1) + (j-1)] := Value;
      end
   end;
end;

procedure TModel._SaveProjectModule;
var wordsList:TStringList;
begin
   { Saves the project Module returning its attributes }
   wordsList := TStringList.Create;
   wordsList.Sorted := false;
   //save description of fields
   wordsList.Add('# ' +cPROJECT+ '; AnalystName; BaseTimeUnits; InitializeStatistics; InitializeSystem; NumberOfReplication; PauseBetweenReplicatons; ProjectTitle; ReplicationLength; ReplicationLengthTimeUnits; TerminatingCondition; WarmupPeriod; WarmupPeriodTimeUnits');
   _WriteInFile(arq, wordsList);
   wordsList.Clear;
   //save the module
   wordsList.Add(cPROJECT);
   wordsList.Add(aAnalystName);
   wordsList.Add(IntToStr(Genesys.AuxFunctions.TimeUnitToInt(aBaseTimeUnit)));
   if aInitializeStatistics then wordsList.Add('1') else wordsList.Add('0');
   if aInitializeSystem then wordsList.Add('1') else wordsList.Add('0');
   wordsList.Add(IntToSTr(aNumberOfReplications));
   if aPauseBetween then wordsList.Add('1') else wordsList.Add('0');
   wordsList.Add(aProjectTitle);
   wordsList.Add(FloatToStr(aReplicationLenght));
   wordsList.Add(IntToStr(Genesys.AuxFunctions.TimeUnitToInt(aReplicationLenghtTimeUnit)));
   wordsList.Add(aTerminatingCondition);
   wordsList.Add(FloatToStr(aWarmUpPeriod));
   wordsList.Add(IntToStr(Genesys.AuxFunctions.TimeUnitToInt(aWarmUpPeriodTimeUnit)));
   _WriteInFile(arq, wordsList);
end;

procedure TModel._SaveAttributesModule(var arq:text);
var i: integer;
    aList: TStringList;
    wordsList:TStringList;
begin
   { Saves the Attribute Module returning its attributes' names }
   wordsList := TStringList.Create;
   wordsList.Sorted := false;
   //save description of fields
   wordsList.Add('# ' +cATTRIBUTE+ '; Attribute Name 1; Attribute Name 2; ...; Attrinute Name n');
   _WriteInFile(arq, wordsList);
   wordsList.Clear;
   //save the module
   aList := SIMAN._GetModuleStructuresByKind(cATTRIBUTE);
   if aList.Count > 0 then begin
      wordsList.Add(cATTRIBUTE);
      for i := 1 to aList.Count - 1 do begin
         wordsList.Add(aList.Strings[i]);
      end;
      _WriteInFile(arq, wordsList);
   end;
end;

procedure TModel._SaveResourcesModule(var arq:text);
var i: integer;
    aList: TStringList;
    wordsList: TStringList;
    thisRes: TResource;
begin
   { Saves the Resource Module returning its attributes }
   wordsList := TStringList.Create;
   wordsList.Sorted := false;
   //save description of fields
   wordsList.Add('# ' +cRESOURCE+ '; ID; Name; NumberBusy; Capacity; QueueName');
   _WriteInFile(arq, wordsList);
   wordsList.Clear;
   //save the module
   aList := SIMAN._GetModuleStructuresByKind(cRESOURCE);
   if aList.Count > 0 then begin
      for i := 0 to aList.Count - 1 do begin
         wordsList.Clear;
         wordsList.Add(cRESOURCE);
         thisRes := TResource(aList.Objects[i]);
         wordsList.Add(IntToStr(thisRes.ID));
         wordsList.Add(thisRes.Name);
         wordsList.Add(IntToStr(thisRes.NumberBusy));
         wordsList.Add(IntToStr(thisRes.Capacity));
         wordsList.Add(thisRes.QueueName);
         _WriteInFile(arq, wordsList);
      end;
   end;
end;

procedure TModel._SaveVariablesModule(var arq:text);
var i,j: integer;
    aList: TStringList;
    wordsList: TStringList;
    thisVariable: TVariable;
begin
   { Saves the VAriable Module returning its names, dimensions and initial values }
   wordsList := TStringList.Create;
   wordsList.Sorted := false;
   //save description of fields
   wordsList.Add('# ' +cVARIABLE+ '; Name; Dimension1; Dimension2; Value[1,1]; Value[2,1]; ...; Value[Dimension1,1]; Value[1,2]; Value[2,2]...; Value[2,Dimension1]; Value[3,1]; ... Value[Dimension1,Dimension2]');
   _WriteInFile(arq, wordsList);
   wordsList.Clear;
   //save the module
   aList := SIMAN._GetModuleStructuresByKind(cVARIABLE);
   if aList.Count > 0 then begin
      for i := 0 to aList.Count - 1 do begin
         wordsList.Clear;
         wordsList.Add(cVARIABLE);
         thisVariable := TVariable(aList.Objects[i]);
         //wordsList.Add(IntToStr(thisVariable.ID));
         wordsList.Add(thisVariable.Name);
         wordsList.Add(IntToStr(thisVariable.Dimension1));
         wordsList.Add(IntToStr(thisVariable.Dimension2));
         for j := 0 to thisVariable.InitialValues.Count - 1 do begin
            wordsList.Add(thisVariable.InitialValues.Strings[j]);
         end;
         _WriteInFile(arq, wordsList);
      end;
   end;
end;

procedure TModel._SaveFailureModule(var arq: text);
var wordsList, aList: TStringList;
    i,j: integer;
    thisFailure: TFailure;
begin
   {Saves the sets modules}
   wordsList := TStringList.Create;
   wordsList.Sorted := false;
   //save description of fields
   wordsList.Add('# ' +cFAILURE+ '; ID; Name; FailureType; Count; UpTime; UpTimeUnit; DownTime; DownTimeUnit; StateOnly; UpTimeInThisStateOnly');
   _WriteInFile(arq, wordsList);
   wordsList.Clear;
   {save modules}
   aList := SIMAN._GetModuleStructuresByKind(cFAILURE);
   if aList.Count > 0 then begin
      for i := 0 to aList.Count - 1 do begin
         wordsList.Clear;
         wordsList.Add(cSET);
         thisFailure := TFailure(aList.Objects[i]);
         wordsList.Add(IntToStr(thisFailure.ID));
         wordsList.Add(thisFailure.Name);
         if thisFailure.aType = ftCount then
            wordsList.Add('0')
         else
            wordsList.Add('1');
         wordsList.Add(thisFailure.aCount);
         wordsList.Add(thisFailure.aUpTime);
         wordsList.Add(IntToStr(Genesys.AuxFunctions.TimeUnitToInt(thisFailure.aUpTimeUnit)));
         wordsList.Add(thisFailure.aDownTime);
         wordsList.Add(IntToStr(Genesys.AuxFunctions.TimeUnitToInt(thisFailure.aDownTimeUnit)));
         if thisFailure.aStateOnly then
            wordsList.Add('1')
         else
            wordsList.Add('0');
         wordsList.Add(IntToStr(Genesys.AuxFunctions.ResourceStateToInt(thisFailure.aUpTimeInThisStateOnly)));
         _WriteInFile(arq, wordsList);
      end;
   end;
end;

procedure TModel._SaveSetsModule(var arq: text);
var wordsList, aList: TStringList;
    i,j: integer;
    thisSet: TSet;
begin
   {Saves the sets modules}
   wordsList := TStringList.Create;
   wordsList.Sorted := false;
   //save description of fields
   wordsList.Add('# ' +cSET+ '; ID; Name; MemberType; Member1; Member2; ...; MemberN');
   _WriteInFile(arq, wordsList);
   wordsList.Clear;
   {save modules}
   aList := SIMAN._GetModuleStructuresByKind(cSET);
   if aList.Count > 0 then begin
      for i := 0 to aList.Count - 1 do begin
         wordsList.Clear;
         wordsList.Add(cSET);
         thisSet := TSet(aList.Objects[i]);
         wordsList.Add(IntToStr(thisSet.ID));
         wordsList.Add(thisSet.Name);
         wordsList.Add(thisSet.MemberType);
         for j := 0 to thisSet.aMembers.Count-1 do begin
            wordsList.Add(thisSet.MemberName[j]);
         end;
         _WriteInFile(arq, wordsList);
      end;
   end;
end;

procedure TModel._SaveQueuesModule(var arq:text);
var i: integer;
    aList: TStringList;
    wordsList: TStringList;
    thisQueue: TQueue;
begin
   { Saves the Queue Modules returning its attributes }
   wordsList := TStringList.Create;
   wordsList.Sorted := false;
   //save description of fields
   wordsList.Add('# ' +cQUEUE+ '; ID; Name; Type; Attribute');
   _WriteInFile(arq, wordsList);
   wordsList.Clear;
   //save the module
   aList := SIMAN._GetModuleStructuresByKind(cQUEUE);
   if aList.Count > 0 then begin
      for i := 0 to aList.Count - 1 do begin
         wordsList.Clear;
         wordsList.Add(cQUEUE);
         thisQueue := TQueue(aList.Objects[i]);
         wordsList.Add(IntToStr(thisQueue.ID));
         wordsList.Add(thisQueue.Name);
         case thisQueue.QueueType of
            qtFIFO: wordsList.Add('0');
            qtLVF:  wordsList.Add('1');
            qtHVF:  wordsList.Add('2');
         end;
         wordsList.Add(thisQueue.Attribute);
         _WriteInFile(arq, wordsList);
      end;
   end;
end;


function TModel._LoadTextModel(fileName: string): integer;
var arq: text; //file of text
    texto: string;
    wordsList: TStringList;
    i: integer;
    umPlugIn: TPlugIn;
    umPointer, umPointer2: pointer;
begin
   { Loads a model from a file }
   if not FileExists(fileName) then
      result := -1 //erro. Arquivo não existe
   else begin
      result := 0; //assume que o arquivo está ok.
      aFullName := fileName;
      Genesys.AuxFunctions.SeparatePathAndFileName(fileName, aPath, aFileName);
      wordsList := TStringList.Create;
      wordsList.Sorted := false; {não pode ser ordenado}
      assignFile(arq, fileName);
      FileMode := 0; //read-only
      reset(arq);
      Trace(cTLTransfer,'Loading  model "' + fileName + '"...');
      while not EOF(arq) do begin
         readln(arq, texto);
         texto := Trim(texto);
         if texto <> '' then begin
            if texto[1] <> '#' then begin
               //Cada campo da linha lida é separado por ";". Separa agora esses campos
               Genesys.AuxFunctions.SeparateWords(texto, ';', wordsList);
               { [0] = Tipo ; [1] = ID ; [2] = NOME ; [3] = IDPROX1,IDPROX2,... ; [4] = X ; [5] = Y ; [6] = Z ;
                 [7] = reservado para uso futuro ; [8] = reservado para uso futuro ; [9] = reservado para uso futuro ; [10] = reservado para uso futuro }
               wordsList.Strings[0] := UpperCase(wordsList.Strings[0]);
               Trace(4, Genesys.AuxFunctions.StrIdent(1)+'- '+texto);
               //conforme o tipo envia para o gerenciador adequado
               i := Genesys.PlugInIndexOf(wordsList.Strings[0]);
               if i >= 0 then begin
                  //é um PlugIn do modelo
                  umPlugIn := Genesys.PlugIn[i];
                  //invoca o método da classe gerenciadora associada ao bloco lido
                  try
                     umPointer := @wordsList;
                     umPlugIn.aAcessa_Metodo(pmReadModule, umPointer, umPointer2);
                  except
                     Trace(cTLError, Genesys.AuxFunctions.StrIdent(1)+'ERROR: PlugIn "' + wordsList.Strings[0] + '" doen''t respond to the "Read" command');
                  end;
                  end
               else begin
                  //não é um PlugIn. Testa outros blocos
                  if      wordsList.Strings[0] = cPROJECT      then _ReadProjectModule(wordsList)
                  else if wordsList.Strings[0] = cATTRIBUTE    then _ReadAttributesModule(wordsList)
                  else if wordsList.Strings[0] = cRESOURCE     then _ReadResourcesModule(wordsList)
                  else if wordsList.Strings[0] = cENTITYTYPE   then _ReadEntityTypeModule(wordsList)
                  else if wordsList.Strings[0] = cQUEUE        then _ReadQueuesModule(wordsList)
                  else if wordsList.Strings[0] = cCSTAT        then _ReadCSTATModule(wordsList)
                  else if wordsList.Strings[0] = cVARIABLE     then _ReadVariablesModule(wordsList)
                  else if wordsList.Strings[0] = cFORMULA      then _ReadFormulaModule(wordsList)
                  else if wordsList.Strings[0] = cSET          then _ReadSetsModule(wordsList)
                  else if wordsList.Strings[0] = cFAILURE      then _ReadFailureModule(wordsList)
                  else begin
                     Trace(cTLError, Genesys.AuxFunctions.StrIdent(1)+'ERROR: "' +wordsList.Strings[0] + '" is unknown');
                     result := -1; //erro
                  end;
               end;
            end;
         end;
      end;
      CloseFile(arq);
   end;
end;

function TModel._LoadXMLModel(fileName: string): integer;
var XMLDocument: TXMLDocument;
    i, j: integer;
    version, text: string;
    XMLNode, XMLSubNode: IXMLNode;
begin
   { Loads a model from a file }
   if not FileExists(fileName) then
      result := -1 //erro. Arquivo não existe
   else begin
      result := 0; //assume que o arquivo está ok.
      aFullName := fileName;
      Genesys.AuxFunctions.SeparatePathAndFileName(fileName, aPath, aFileName);
      Trace(cTLTransfer,'Loading  model "' + fileName + '"...');
      try
         XMLDocument := TXMLDocument.Create(nil);
         XMLDocument.DOMVendor := MSXML_DOM;
         XMLDocument.Options := [doNodeAutoCreate,doAttrNull,doAutoPrefix,doNamespaceDecl];
         XMLDocument.ParseOptions := [];
         XMLDocument.FileName := filename;
         XMLDocument.Active := true;
         XMLDocument.Refresh;
         if XMLDocument.DocumentElement.LocalName <> 'GenesysModel' then begin
            Trace(cTLError, Genesys.AuxFunctions.StrIdent(1)+'ERROR: File is not a Genesys model');
         end else begin
            {file is a genesys model}
            {takes the version of XML model and verify if it can be readed}
            version := XMLDocument.DocumentElement.Attributes['version'];
            {open 1st level structure (comments, project, structures, modeules)}
            for i := 0 to XMLDocument.ChildNodes.Count-1 do begin
               XMLNode := XMLDocument.ChildNodes.Get(i);
               text := UpperCase(XMLNode.LocalName);
               if text = 'COMMENTS' then begin
                  {do nothing}
               end else if text = 'PROJECT' then begin
               end else if text = 'STRUCTURES' then begin
                  for j := 0 to XMLNode.ChildNodes.Count-1 do begin
                     XMLSubNode := XMLDocument.ChildNodes.Get(i);
                     text := UpperCase(XMLSubNode.LocalName);
                     if      text = cAttribute  then _ReadXMLAttributesModule(XMLSubNode)
                     else if text = cResource   then _ReadXMLResourcesModule(XMLSubNode)
                     else if text = cEntityType then _ReadXMLEntityTypeModule(XMLSubNode)
                     else if text = cQueue      then _ReadXMLQueuesModule(XMLSubNode)
                     else if text = cCSTAT      then _ReadXMLCSTATModule(XMLSubNode)
                     else if text = cVariable   then _ReadXMLVariablesModule(XMLSubNode)
                     else if text = cFormula    then _ReadXMLFormulaModule(XMLSubNode)
                     else if text = cSet        then _ReadXMLSetsModule(XMLSubNode)
                     else if text = cFailure    then _ReadXMLFailureModule(XMLSubNode)
                     else begin
                        Trace(cTLError, Genesys.AuxFunctions.StrIdent(1)+'ERROR: Structure "' + text + '" is unknown');
                        result := -1; //erro
                     end;
                  end;
               end else if text = 'MODULES' then begin
               end else begin
                  Trace(cTLError, Genesys.AuxFunctions.StrIdent(1)+'ERROR: "' + text + '" is unknown');
                  result := -1; //erro
               end;
            end;
         end;
      except
         Trace(cTLTransfer,'Loading  model "' + fileName + '"...');
      end;
   end;
end;


function TModel.Load(fileName: string): integer;
begin
   if not FileExists(fileName) then
      result := -1 //erro. Arquivo não existe
   else begin
      result := 0; //assume que o arquivo está ok.
      aFullName := fileName;
      Genesys.AuxFunctions.SeparatePathAndFileName(fileName, aPath, aFileName);
      if UpperCase(Genesys.AuxFunctions.StrRight(aFileName,3)) = 'XML' then begin
         result := _LoadXMLModel(filename);
      end else begin
         result := _LoadTextModel(filename);
      end;
   end;
   _CorrectIDs;
   Trace(cTLTransfer,'OK');
   Trace(cTLTransfer,'');
   if result >= 0 then begin {terminou com sucesso}
      {verifica se o evento deve ser manipulado}
      if @aOnDocumentOpen <> nil then aOnDocumentOpen;
   end;
end;


procedure TModel._ReadXMLAttributesModule(XMLNode: IXMLNode);
begin

end;

procedure TModel._ReadXMLCSTATModule(XMLNode: IXMLNode);
begin

end;

procedure TModel._ReadXMLEntityTypeModule(XMLNode: IXMLNode);
begin

end;

procedure TModel._ReadXMLFailureModule(XMLNode: IXMLNode);
begin

end;

procedure TModel._ReadXMLFormulaModule(XMLNode: IXMLNode);
begin

end;

procedure TModel._ReadXMLProjectModule(XMLNode: IXMLNode);
begin
   try
      aAnalystName := XMLNode.ChildValues['AnalystName']; //   wordsList.Strings[1];
      aBaseTimeUnit := Genesys.AuxFunctions.IntToTimeUnit(XMLNode.ChildValues['BaseTimeUnit']); //StrToInt(wordsList.Strings[2]));
      aInitializeStatistics := XMLNode.ChildValues['InitializStatistics']; //StrToInt(wordsList.Strings[3]) <> 0;
      aInitializeSystem := XMLNode.ChildValues['InitializeSystem']; //StrToInt(wordsList.Strings[4]) <> 0;
      aNumberOfReplications := XMLNode.ChildValues['NumberOfReplications']; //StrToInt(wordsList.Strings[5]);
      aPauseBetween := XMLNode.ChildValues['PauseBetween'] <> 0; //StrToInt(wordsList.Strings[6]) <> 0;
      aProjectTitle := XMLNode.ChildValues['Title']; //wordsList.Strings[7];
      aReplicationLenght := XMLNode.ChildValues['ReplicationLenght']; //StrToFloat(wordsList.Strings[8]);
      aReplicationLenghtTimeUnit := Genesys.AuxFunctions.IntToTimeUnit(XMLNode.ChildValues['ReplicationLenghtTimeUnit']); //StrToInt(wordsList.Strings[9]));
      aTerminatingCondition := XMLNode.ChildValues['TerminateCondition']; //wordsList.Strings[10];
      aWarmUpPeriod := XMLNode.ChildValues['WarmUpPeriod']; //StrToFloat(wordsList.Strings[11]);
      aWarmUpPeriodTimeUnit := Genesys.AuxFunctions.IntToTimeUnit(XMLNode.ChildValues['WarmUpPeriodTimeUnit']); //StrToInt(wordsList.Strings[12]));
   except
      Trace(cTLError,'Error loading "Project" structure');
   end;
end;

procedure TModel._ReadXMLQueuesModule(XMLNode: IXMLNode);
begin

end;

procedure TModel._ReadXMLResourcesModule(XMLNode: IXMLNode);
begin

end;

procedure TModel._ReadXMLSetsModule(XMLNode: IXMLNode);
begin

end;

procedure TModel._ReadXMLVariablesModule(XMLNode: IXMLNode);
begin

end;


procedure TModel._ReadSetsModule(wordsList: TStringList);
var newID: word;
    i: integer;
begin
   try
      newID := aSIMAN.SetInsert(StrToInt(wordsList.Strings[1]), Genesys.AuxFunctions.Underscore(wordsList.Strings[2]), wordsList.Strings[3]);
      for i := 4 to wordsList.Count-1 do begin
         aSIMAN.SetInsertMember(newID, Genesys.AuxFunctions.Underscore(wordsList.Strings[i]), -1);
      end;
   except
      Trace(cTLError,'Error loading "' + wordsList.Strings[0] + '" module');
   end;
end;

procedure TModel._ReadAttributesModule(wordsList: TStringList);
var i: integer;
    attrs: TStringList;
begin
   try
      attrs := SIMAN._GetModuleStructuresByKind(cATTRIBUTE);
      for i := 1 to wordsList.Count - 1 do begin
         if attrs.IndexOf(wordsList.Strings[i]) = -1 then begin
            attrs.Add(Genesys.AuxFunctions.Underscore(wordsList.Strings[i]));
         end;
      end;
   except
      Trace(cTLError,'Error loading "' + wordsList.Strings[0] + '" module');
   end;
end;

procedure TModel._ReadProjectModule(wordsList: TStringList);
begin
   try
      aAnalystName := wordsList.Strings[1];
      aBaseTimeUnit := Genesys.AuxFunctions.IntToTimeUnit(StrToInt(wordsList.Strings[2]));
      aInitializeStatistics := StrToInt(wordsList.Strings[3]) <> 0;
      aInitializeSystem := StrToInt(wordsList.Strings[4]) <> 0;
      aNumberOfReplications := StrToInt(wordsList.Strings[5]);
      aPauseBetween := StrToInt(wordsList.Strings[6]) <> 0;
      aProjectTitle := wordsList.Strings[7];
      aReplicationLenght := StrToFloat(wordsList.Strings[8]);
      aReplicationLenghtTimeUnit := Genesys.AuxFunctions.IntToTimeUnit(StrToInt(wordsList.Strings[9]));
      aTerminatingCondition := wordsList.Strings[10];
      aWarmUpPeriod := StrToFloat(wordsList.Strings[11]);
      aWarmUpPeriodTimeUnit := Genesys.AuxFunctions.IntToTimeUnit(StrToInt(wordsList.Strings[12]));
   except
      Trace(cTLError,'Error loading "' + wordsList.Strings[0] + '" module');
   end;
end;

procedure TModel._ReadQueuesModule(wordsList: TStringList);
var queueType: TQueueType;
    qID: word;
    queue: TQueue;
begin
   try
      case StrToInt(wordsList.Strings[3]) of
         0:   queueType := qtFIFO;
         1:   queueType := qtLVF;
         2:   queueType := qtHVF;
         else queueType := qtFIFO;
      end;
      qID := SIMAN.QueueInsert(StrToInt(wordsList.Strings[1]), Genesys.AuxFunctions.Underscore(wordsList.Strings[2]), queueType, Genesys.AuxFunctions.Underscore(wordsList.Strings[4]));
      if (wordsList.Count = 7) then begin
         {is a queue associated with a module}
         queue := SIMAN._GetQueueByID(qID);
         queue.ModuleID := StrToInt(wordsList.Strings[5]);
         queue.ModuleInput := StrToInt(wordsList.Strings[6]);
      end;
   except
      Trace(cTLError,'Error loading "' + wordsList.Strings[0] + '" module');
   end;
end;

procedure TModel._ReadResourcesModule(wordsList: TStringList);
begin
   try
     SIMAN.ResourceInsert(StrToInt(wordsList.Strings[1]), Genesys.AuxFunctions.Underscore(wordsList.Strings[2]), StrToInt(wordsList.Strings[3]), StrToInt(wordsList.Strings[4]), Genesys.AuxFunctions.Underscore(wordsList.Strings[5]));
   except
      Trace(cTLError,'Error loading "' + wordsList.Strings[0] + '" module');
   end;
end;

procedure TModel._ReadVariablesModule(wordsList: TStringList);
var umaVar: TVariable;
    Variaveis: TStringList;
    i, j, k: integer;
    newID: word;
begin
  try
   variaveis := SIMAN._GetModuleStructuresByKind(cVARIABLE) ;
   i := 1;
   while i < wordsList.Count do begin
      newID := variaveis.Count + 1;
      umaVar := TVariable.Create(newID,'');
      umaVar.Name := Genesys.AuxFunctions.Underscore(wordsList.Strings[i]);
      umaVar.Dimension1 := StrToInt(wordsList.Strings[i+1]);
      umaVar.Dimension2 := StrToInt(wordsList.Strings[i+2]);
      umaVar.Values := TStringList.Create;
      umaVar.Values.Sorted := false;  {não pode estar ordenado}
      i := i + 3;
      for j := 1 to umaVar.Dimension1 do begin
         for k := 1 to umaVar.Dimension2 do begin
            umaVar.Values.Add(wordsList.Strings[i]);
            umaVar.InitialValues.Add(wordsList.Strings[i]);
            i := i + 1;
          end;
      end;
      variaveis.AddObject(umaVar.Name, TObject(umaVar));  {ordenado por nome, não ID - até poderia ser por ID}
   end;
  except
      Trace(cTLError,'Error loading "' + wordsList.Strings[0] + '" module');
  end;
end;

procedure TModel._ReadCSTATModule(wordsList: TStringList);
begin
   { TODO 3 -oRafael Cancian -cNúcleo : Implementar _ReadCSTATModule }
   Genesys.Model.Trace(cTLError,'Not implemented');
end;

procedure TModel._SaveStatisticsModule(var arq:text);
begin
   { TODO 3 -oRafael Cancian -cNúcleo : Implementar _SaveStatisticsModule }
   Genesys.Model.Trace(cTLError,'Not implemented');
end;


function TModel._GenerateNewModuleName(kind:string): string;
var i: integer;
    newlist: TStringList;
begin
   i := aModules.IndexOf(kind);
   if i >=0 then
      result := kind + ' ' + IntToStr(TStringList(aModules.Objects[i]).Count+1)
   else begin
      newList := TStringList.Create;
      newList.Sorted := true;
      aModules.AddObject(kind, newList);  ///////////// ????????
      result := kind + ' 1';
   end;
end;

function TModel._GenerateNewModuleID: word;
var i, index: integer;
    newID: word;
    found: boolean;
    aList: TStringList;
begin
   newID := 100;
   repeat
      i := 0;
      found := false;
      while (i < aModules.Count) do begin
         aList := TStringList(aModules.Objects[i]);
         index := aList.IndexOf(IntToSTr(newID));
         if index >=0 then begin
            i := aModules.Count; {exits}
            found := true;
            end
         else
            i := i + 1; {continue searching}
      end;
      newID := newID + 1;
   until not found;
   result := newID -1;
end;


procedure TModel._ReadFailureModule(wordsList: TStringList);
var fID: word;
    newFailure: TFailure;
    failures:TStringList;

begin
   try
      failures := aSIMAN._GetModuleStructuresByKind(cFAILURE); 
      newFailure := TFailure.Create(StrToInt(wordsList.Strings[1]), Genesys.AuxFunctions.Underscore(wordsList.Strings[2]));
      if StrToInt(wordsList.Strings[3]) = 0 then
         newFailure.aType := ftCount
      else
         newFailure.aType := ftTime;
      newFailure.aUpTime := wordsList.Strings[4];
      newFailure.aUpTimeUnit := Genesys.AuxFunctions.IntToTimeUnit(StrToInt(wordsList.Strings[5]));
      newFailure.aDownTime := wordsList.Strings[6];
      newFailure.aDownTimeUnit := Genesys.AuxFunctions.IntToTimeUnit(StrToInt(wordsList.Strings[7]));
      newFailure.aStateOnly := StrToInt(wordsList.Strings[8]) = 1;
      newFailure.aUpTimeInThisStateOnly := Genesys.AuxFunctions.IntToResourceState(StrToInt(wordsList.Strings[9]));
      failures.AddObject(IntToStr(newFailure.aId), newFailure);
   except
      Trace(cTLError,'Error loading "' + wordsList.Strings[0] + '" module');
   end;
end;

procedure TModel._ReadEntityTypeModule(wordsList: TStringList);
var anType: TEntityType;
    aList: TStringList;
begin
   try
      aList := SIMAN._GetModuleStructuresByKind(cENTITYTYPE);
      if aList.IndexOf(wordsList.Strings[1]) = -1 then begin
         anType := TEntityType.Create(StrToInt(wordsList.Strings[1]), Genesys.AuxFunctions.Underscore(wordsList.Strings[2]));
         anType.InitialPicture := wordsList.Strings[3];
         anType.InitialVACost := StrToFloat(wordsList.Strings[4]);
         anType.InitialNVACost := StrToFloat(wordsList.Strings[5]);
         anType.InitialOtherCost := StrToFloat(wordsList.Strings[6]);
         anType.InitialWaitingCost := StrToFloat(wordsList.Strings[7]);
         aList.AddObject(wordsList.Strings[1], anType);
      end;
   except
      Trace(cTLError,'Error loading "' + wordsList.Strings[0] + '" module');
   end;
end;

procedure TModel._SaveCStatsModule(var arq: text);
begin
   { TODO 3 -oRafael Cancian -cNúcleo : Implementar _SaveCStatsModule }
   Genesys.Model.Trace(cTLError,'Not implemented');
end;

procedure TModel._SaveEntityTypesModule(var arq: text);
var i: integer;
    aList: TStringList;
    wordsList: TStringList;
    thisType: TEntityType;
begin
   wordsList := TStringList.Create;
   wordsList.Sorted := false;
   //save description of fields
   wordsList.Add('# ' +cENTITYTYPE+ '; ID; Name; InitialPicture; InitialVACost; InitialNVACost; InitialOtherCost; InitialWaitingCost');
   _WriteInFile(arq, wordsList);
   wordsList.Clear;
   //save the module
   aList := SIMAN._GetModuleStructuresByKind(cENTITYTYPE);
   if aList.Count > 0 then begin
      for i := 0 to aList.Count - 1 do begin
         wordsList.Clear;
         wordsList.Add(cENTITYTYPE);
         thisType := TEntityType(aList.Objects[i]);
         wordsList.Add(IntToStr(thisType.ID));
         wordsList.Add(thisType.Name);
         wordsList.Add(thisType.InitialPicture);
         wordsList.Add(FloatToStr(thisType.InitialVACost));
         wordsList.Add(FloatToStr(thisType.InitialNVACost ));
         wordsList.Add(FloatToStr(thisType.InitialOtherCost));
         wordsList.Add(FloatToStr(thisType.InitialWaitingCost));
         _WriteInFile(arq, wordsList);
      end;
   end;
end;

procedure TModel.TraceSimulation(level:byte; moduleID, entityID: word; text: string);
var txtfinal: string;
    timestr: string;
begin
 try
   if (level <= aTraceLevel) and (@aTraceSimulation <> nil) then begin
      if (aTNOW > aLastTimeTraceSimulation) and (@aTraceSimulation = @aTrace) then Trace(3,'');
       txtfinal := '';  //IntToStr(level) + '-';
       timeStr := FormatFloat('0.000e+00',aTNOW);
       txtfinal :=  txtFinal + 'T:' + timeStr + ' ';
       txtfinal := txtfinal + 'E:' + IntToStr(entityID) + ' ';
       txtfinal := txtfinal + 'M:' + intToStr(moduleID) + '> ';
       txtFinal := txtFinal + text;
       aLastTimeTraceSimulation := aTNOW;
       aLastEntityTraceSimulation := entityID;
       aLastModuleTraceSimulation := moduleID;
       //text := 'L:'+IntToStr(level)+' '+text;
       aTraceSimulation(txtfinal);
    end;
 except
   writeln('Error in TraceSimulation');
 end;
end;

function TModel._GetEntityPicture(index: integer): TEntityPicture;
begin
   result := aEntityPictures.Strings[index];
end;


procedure TModel._SetEntityPicture(index: integer; picture: TEntityPicture);
begin
   aEntityPictures.Strings[index] := picture;
end;


procedure TModel.ModuleTypeInsert(newModuleType: string);
var newlist: TStringList;
begin
   if aModules.IndexOf(newModuleType) = -1 then begin
      newList := TStringList.Create;
      newList.Sorted := true;
      aModules.AddObject(newModuleType, newList);
   end;
end;

function TModel.ModuleCount: integer;
var i,aux: integer;
    umaLista: TStringList;
begin
   aux := 0;
   for i := 0 to aModules.Count-1 do begin
      umaLista := TStringList(aModules.Objects[i]);
      if umaLista <> nil then
          aux := aux + umaLista.Count;
   end;
   result := aux;
end;

function TModel.ModuleType(index: word): string;
var i, aux: integer;
    thisList: TStringList;
begin
   aux := 0;
   i := 0;
   thisList := TStringList.Create;
   while (i < aModules.Count) and (aux <= index) do begin
      thisList := TStringList(aModules.Objects[i]);
      aux := aux + thisList.Count;
      i := i + 1;
   end;
   if (i <= aModules.Count) and (aux >= index) then
      result := TModule(thisList.Objects[index-(aux-thisList.Count)]).Kind
   else
     result := '';

end;

procedure TModel.BreakOnTime(time: double);
begin
   { DONE 3 -oRafael Cancian -cNúcleo : Implementar BreakOnTime }
   aBreakOnTime := time;
end;

destructor TModel.Destroy;
var i,j: integer;
    aList: TStringList;
    aModule: TModule;
begin
   SIMAN.Destroy;
   //Delete model lists
   aEntityPictures.Clear;
   aEntityPictures.Destroy;
   aResourcePictures.Clear;
   aResourcePictures.Destroy;
   for i := 0 to aModules.Count-1 do begin
      aList := TStringList(aModules.Objects[0]);
      for j := 0 to aList.Count-1 do begin;
         aModule := TModule(aList.Objects[0]);
         aModule.Destroy;
         aList.Delete(0);
      end;
      aModules.Delete(0);
   end;
   aModules.Destroy;
   inherited;
end;

function TModel._CheckAndAddInternalLiters: integer;
var i, j, k: integer;
    form: TFormula;
    expression: string;
    value: double;
begin
   { TODO 4 -oRafael Cancian -cNúcleio : Implementar a verificação de declaração de liteirais. Possivelmente declarar automaticamente }
   ////// TO IMPLEMENT -> Verify if there are symbols that were not yet declared
   Trace(cTLModuleIntern, Genesys.AuxFunctions.StrIdent(1)+'- Verifying Internal Literals');
   result := 0;
   yynerrs := 0;
   i := 0;
   while (i < SIMAN.FormulaCount) and (yynerrs = 0) do begin
       form := SIMAN.Formula[i];
       j := 1;
       Trace(ctlModuleIntern,Genesys.AuxFunctions.StrIdent(2)+'- Verifying formula "'+form.aName+'"');
       while (j <= form.Dimension1) and (yynerrs = 0) do begin
          k := 1;
          while (k <= form.Dimension2) and (yynerrs = 0) do begin
             expression := SIMAN.Formulas[i,j,k];
             value := SIMAN.StringEvaluateFormula(expression);
             if  (yynerrs > 0) then begin
                Trace(ctlError,Genesys.AuxFunctions.StrIdent(1)+'Error: Formula "'+form.aName+'" has an error in expression "' + expression + '"');
                result := -1;
             end;
             k := k + 1;
          end;
          j := j + 1;
       end;
       i := i + 1;
   end;
end;

procedure TModel._RecursiveConnectedTo(thisModule:TModule; var visited:TStringList; var unconnected: TStringList; var drenofound:boolean);
var plugin: TPlugin;
    index: integer;
    nextModule: TModule;
    i: integer;
begin
   visited.Add(IntToStr(thisModule.ID)); {include this module as visited}
   index := Genesys.PlugInIndexOf(thisModule.Kind);
   Trace(cTLModuleDetail, Genesys.AuxFunctions.StrIdent(2)+'- Connected to ' + thisModule.Kind +': '+ thisModule.Name+' ('+IntToStr(thisModule.ID)+')');
   if index = -1 then begin
      {the module has no associated plugin. Impossible. Should do more, but will mark module as unconnected}
      unconnected.Add(IntToStr(thisModule.ID));
      Trace(cTLError,'Error: Module named "'+thisModule.Name+'" id "'+IntToStr(thisModule.ID)+'" has no valid plugin "'+thisModule.Kind+'").');
      end
   else begin
      plugin := Genesys.PlugIn[index];
      if plugin.Dreno then begin
         index := 0; {singal to stop searching. Found a dreno}
         i := 0;
         while (i < thisModule.NextCount) and (index = 0) do begin
            if thisModule.NextID[i] <> thisModule.ID then
               index := 1; {need continue searching}
            i := i + 1;
         end;
         if index = 0 then begin
            {found a dreno that has no connection with other modules. Stop walking}
            drenoFound := true;
         end;
      end;
      if not drenoFound then begin
         if thisModule.NextCount = 0 then begin
            //this module is not a DRENO and it has no next modules - it is a dead end
            unconnected.Add(IntToStr(thisModule.ID));
            Trace(cTLError,'Error: Module named "'+thisModule.Name+'" id "'+IntToStr(thisModule.ID)+'" is unconnected (no next module).');
            end
         else begin
            //continue the pathway throught the next modules
            for index := 0 to thisModule.NextCount - 1 do begin
               drenoFound := false;
               nextModule := ModuleByID(thisModule.NextID[index]);
               if (nextModule = nil) then begin
                  {can be an invalid ID or a queue associated with a module}
                  i := SIMAN.QueueIndex(thisModule.NextID[index]);
                  if (i >= 0) then begin
                     {is a queue. Try to get the module associated}
                     nextModule := ModuleByID(SIMAN.Queue[i].ModuleID);
                  end;
                  if (nextModule = nil) then begin
                     {invalid ID}
                     unconnected.Add(IntToStr(thisModule.ID));
                     Trace(cTLError,'Error: Module named "'+thisModule.Name+'" id "'+IntToStr(thisModule.ID)+'" is unconnected (invalid next id "'+IntToStr(thisModule.NextID[index])+'").');
                     DrenoFound := true; {only one error is suficient}
                  end;
               end;
               if (nextModule <> nil) then begin
                  if visited.IndexOf(IntToStr(nextModule.ID)) = -1 then
                     _RecursiveConnectedTo(nextModule, visited, unconnected, drenoFound) {continue searching}
                  else
                     drenoFound := true; {arrived at an already visited module}
               end;
            end;
            if not DrenoFound then begin
               Trace(cTLError,'Error: Module named "'+thisModule.Name+'" id "'+IntToStr(thisModule.ID)+'" is unconnected (takes to no dreno).');
               DrenoFound := true;
            end;
         end;
      end;
   end;
end;

function TModel._CheckConnected: integer;
var i, j: integer;
    kind: string;
    moduleID: word;
    criacoes,
    visited, unconnected,nonvisual: TStringList;
    thisModule: TModule;
    drenoFound: boolean;
begin
   { Returns 0 if model is correctlly connected, or the -ID of the first unconnected module}
   result := -1;  {is wrong by default}
   Trace(cTLModuleIntern, Genesys.AuxFunctions.StrIdent(1)+'- Verifying modules connections');
   visited := TStringList.Create;
   visited.Sorted := true;
   unconnected := TStringList.Create;
   unconnected.Sorted := true;
   {takes all source modules in the model}
   i := 0;
   while (i < Genesys.PlugInCount) do begin
      if Genesys.PlugIn[i].Source then begin
         kind := Genesys.PlugIn[i].Kind;
         //A SOURCE block has been found. Start searching a pathway
         Criacoes := ModulesOfKind[kind];
         if Criacoes <> nil then begin
            for j := 0 to Criacoes.Count - 1 do begin
               //for each SOURCE block, searchs for a pathway throught a DRENO
               drenoFound := false;
               thisModule := TModule(Criacoes.Objects[j]);
               _RecursiveConnectedTo(thisModule,visited,unconnected, drenoFound);
            end;
         end;
      end;
      // Non-visual blocks don´t need to be connected
      if not Genesys.PlugIn[i].Visual then begin
         kind := Genesys.PlugIn[i].Kind;
         nonvisual := ModulesOfKind[kind];
         if nonvisual <> nil then begin
            for j := 0 to nonvisual.Count - 1 do begin
               visited.Add(IntToStr(TModule(nonvisual.Objects[j]).ID));
            end;
         end;
      end;
      i := i + 1;
   end;
   {finished to walk throught the model}
   {verify if there are modules that were not visited}
   for i := 0 to aModules.Count - 1 do begin
      criacoes := TStringList(aModules.Objects[i]);
      for j := 0 to criacoes.Count - 1 do begin
         moduleID := TModule(criacoes.Objects[j]).ID;
         if visited.IndexOf(IntToStr(moduleID)) = -1 then begin
            {this module couldn't be visited by any source module. It is inaccessible. Mark as unconnected}
            unconnected.Add(IntToStr(moduleID));
            Trace(cTLError,'Error: Module id "'+IntToStr(moduleID)+'" is unconnected (not accessible).');
         end;
      end;
   end;
   if unconnected.Count = 0 then
      result := 0 {ok}
   else
      result := -1;  {model has problems}
end;

function TModel._CheckPathway: integer;
begin
   { TODO 4 -oRafael Cancian -cNúcleo : Implementar, ou verificar se é necessário implementar }
   ///// TO IMPLEMENT???? WHAT IT´S SUPOSED TO DO?
   result := 0;
end;

procedure TModel.Close;
begin
  {changes active model}
  if Genesys.aActiveModelIndex >= Genesys.aModels.Count-1 then begin
     Genesys.aActiveModelIndex := Genesys.aModels.Count-2;
  end else begin
  end;
  { Destroy the whole model and changes active model}
  Genesys.aActiveModel.Destroy;
  Genesys.aActiveModel := nil;
end;

function TModel.ModuleAdd(kind: string): word;
var i,j: integer;
    plugIn: TPlugIn;
    newModule: TModule;
    aList: TStringList;
    pointer1, pointer2: pointer;
begin
   i := Genesys.PlugInIndexOf(kind);
   if i = -1 then
      result := 0  {kinf doesn´t exists}
   else begin
      plugin := Genesys.PlugIn[i];
      plugin.aAcessa_Metodo(pmINCLUDEMODULE,pointer1,pointer2);
      newModule := TModule(pointer1);
      if newModule.ID = 0    then newModule.ID := _GenerateNewModuleID;
      if newModule.Name = '' then begin
         newModule.Name := Genesys.AuxFunctions.Underscore(_GenerateNewModuleName(kind));
         ///newModule.Description := newModule.Name;
      end;
      i := aModules.IndexOf(kind);
      if i >= 0 then begin
         aList := TStringList(aModules.Objects[i]);
         j := aList.IndexOf(IntToStr(newModule.ID));
         if j = -1 then begin
            aList.AddObject(IntToStr(newModule.ID), newModule);
            result := newModule.ID;
            end
         else
            result := 0;
         end
      else
         result := 0;
   end;
end;

procedure TModel.ModeleEdite(moduleNumBer: word; pointer1: pointer);
begin

end;

procedure TModel._CorrectIDs;
var i, j:integer;
   umaLista: TStringList;
   novaLista: TStringList;
   umModulo: TModule;
begin
   for i := 0 to aModules.Count - 1 do begin
      umaLista := TStringList(aModules.Objects[i]);
      if umaLista <> nil then begin
         novaLista := TStringList.Create;
         novaLista.Sorted := true;
         for j := 0 to umaLista.Count - 1 do begin
            umModulo := TModule(umaLista.Objects[0]);
            umaLista.Delete(0);
            novaLista.AddObject(IntToStr(umModulo.ID), umModulo);
         end;
         aModules.Objects[i].Destroy;
         aModules.Objects[i] := novaLista;
      end;
   end;
end;

procedure TModel._EndOfReplicationCleaness;
var ents: TStringList;
begin
   {dispose all living entities}
   ents := SIMAN._GetModuleStructuresByKind(cENTITY);
   while ents.Count > 0 do begin
      SIMAN.EntityDispose(TEntity(ents.Objects[0]).ID, false);
   end;
end;

procedure TModel._ReinitializeStatistics;
var i: integer;
    cstats: TStringList;
begin
   cstats := aSIMAN._GetModuleStructuresByKind(cCSTAT);
   for i := 0 to cstats.Count-1 do begin
      TCStat(cstats.Objects[i]).Clear;
   end;
end;

procedure TModel._ReinitializeSystem;
var i: integer;
    thisList: TStringList;
begin
   { TODO 2 -oRafael Luiz Cancian -cNúcleo :
Implementar _ReinitializeSystem
Pode ter que alterar o template, incluindo um método para reinicializar cada módulo }
   {clear all queues}
   thisList := aSIMAN._GetModuleStructuresByKind(cQUEUE);
   for i := 0 to thisList.Count-1 do begin
      TQueue(thisList.Objects[i]).Clear;
   end;
   {clear all resources}
   thisList := aSIMAN._GetModuleStructuresByKind(cRESOURCE);
   for i := 0 to thisList.Count-1 do begin
      TResource(thisList.Objects[i]).Clear;
   end;
   {clear all variables}
   thisList := aSIMAN._GetModuleStructuresByKind(cVARIABLE);
   for i := 0 to thisList.Count-1 do begin
      TVariable(thisList.Objects[i]).Clear;
   end;
   {clear calendar}
   thisList := aSIMAN._GetModuleStructuresByKind(cEVENT);
   thisList.Clear;
end;

{ TGenesysApplication }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}


function TGenesysApplication.SerialNumber:string;
var
   Serial, DirLen, Flags : DWord;
   DLabel                : Array[0..11] of Char;
   thisMachineSerial: string;
begin
   try
      GetVolumeInformation(PChar('c:\'), dLabel, 12, @Serial, DirLen, Flags, nil, 0);
      thisMachineSerial := IntToHex(Serial,8);
      result := thisMachineSerial;
   except
      Result := '';
   end;
end;

function TGenesysApplication.SetActivationCode(activationCode:string): boolean;
begin
   aValidActivationCode := (GenerateActivationCode(cKERNELVERSION, SerialNumber) = activationCode);
   result := aValidActivationCode;
end;


function TGenesysApplication.PlugInAdd(fileName: string): string;
var umPlugIn: TPlugIn;
    i: integer;
{$IFDEF IsDLLPlugin}
    handle: integer;
    umProc: TPluginInitiation;
{$ENDIF}
    procAcessa: TPluginAccess;
    texto: string;
    newPlugInID: word;
    informacoes: TStringList;
begin
   { Adds a data structure and dynamic links for a DLL Plugin }
   //IF Genesys = NIL THEN BEGIN
   //   APPLICATION.MessageBox('Genesys É NULO NO INICIO','GENESYS',0);
   //END;
   PlugInVerify(filename, texto);
   if texto <> '' then begin
      {abre a DLL e obtem o endereço da classe do novo PlugIn}
{$IFDEF IsDLLPlugin}
      Handle := LoadLibrary(PChar(fileName));
      @umProc := GetProcAddress(Handle, 'GetComponentMethods');
      umProc(@Genesys, procAcessa);
{$ELSE}
         procAcessa := __EXTERNAL__GetProcAddress(fileName);
{$ENDIF}
      {cria uma nova entrada para o novo PlugIn}
      informacoes := TStringList.Create;
      informacoes.Sorted := false;
      //Model.Trace(texto);
      Genesys.AuxFunctions.SeparateWords(texto, ';', informacoes);
      umPlugIn := TPlugIn.Create;
      umPlugIn.aAcessa_Metodo := procAcessa;
      umPlugIn.aDLL := fileName;
      umPlugIn.aTipo := informacoes.Strings[0];
      i := aPlugIns.IndexOf(umPlugIn.aTipo);
      if i = -1 then begin
         //inclui o novo PlugIn apenas se não existe algum com o mesmo tipo
         umPlugIn.aAutor := informacoes.Strings[1];
         umPlugIn.aVersao := informacoes.Strings[2];
         umPlugIn.aDescricao := informacoes.Strings[3];
         umPlugIn.aFonte  := informacoes.Strings[4] = '1';
         umPlugIn.aDreno := informacoes.Strings[5] = '1';
         umPlugIn.aVisual := informacoes.Strings[6] = '1';
         umPlugIn.aDependencies := informacoes.Strings[7];
         newPlugInID := aPlugIns.Count + 1;
         umPlugIn.aID := newPlugInID;
         aPlugIns.AddObject(informacoes.Strings[0], umPlugIn);
         result := informacoes.Strings[0];
         {inclui uma nova entrada na lista de módulos do modelo atual}
         //-//Model.ModuleTypeInsert(umPlugIn.Kind);
         {Verifica se todos os plug-ins do qual este depende já foram incluídos. Senao inclui cada um.}
         informacoes.Clear;
         Genesys.AuxFunctions.SeparateWords(umPlugIn.aDependencies, ';', informacoes);
         for i := 0 to informacoes.Count-1 do begin
            if informacoes.Strings[i] <> '' then begin
               PlugInAdd(informacoes.Strings[i]);
            end;
         end;
      end else begin
         result := '';
      end;
   end else begin
      {retorna tipo vazio para indicar erro}
      result := '';
   end;
end;

constructor TGenesysApplication.Create;
begin
   inherited;
   {initialize all atributes}
   aActiveModelIndex := -1;  {no active model}
   aActiveModel := nil;
   aModels := TStringList.Create;
//   aModels.Sorted := true;
   aPlugIns := TStringList.Create;
   aPlugIns.Sorted := true;  {sorted by Kind (Type)}
   aFullName := 'Genesys Application';
   aName := 'Genesys Application';
   aVersion  := cKERNELVERSION;
   aLicenseType := 'Academic Mode. In academic mode this software has full functionality and executing training-size simulation models. This software may be duplicated and used for educational purposes only; any commercial application is a violation of the license agreement.';
   aVisible := true;
   aSafeMode := false;
   aFLAG := 0;
   aAuxFuncs := TAuxiliarFunctions.Create;
   aValidActivationCode := false;
end;

function TGenesysApplication.PlugInDelete(fileName: string): string;
var i: integer;
    found: boolean;
begin
   { Removes a plugin }
   i := 0;
   found := false;
   while (i < aPlugIns.Count) and (not found) do begin
       found := TPlugIn(aPlugIns.Objects[i]).DLL = fileName;
       i := i + 1;
   end;
   if found then begin
      aPlugIns.Delete(i-1);
      //some opened models may be invalides now
   end;
end;

function TGenesysApplication._GetActiveModel: TModel;
begin
{ DONE 3 -oRafael Cancian -cNúcleo : Melhorar o desempenho desse procedimento. Repensar na maneira de acessar o modelo atual -> Muito involcado }
{$IFDEF IsDllPlugIn}
   Genesys := self;  //// NAO DEVIA PRECISAR, MAS PERDE O PONTEIRO SE ESSA LINHA É RETIRADA
   // CADA DLL TEM UMA CÓPIA DO CÓDIGO DO NÚCLEO, POIS O MESMO É INCLUÍDO COMO UNIT À DLL
   // SAFE MODE DEVE VERIFICAR PONTEIROS E VERSAO DO NÚCLEO
{$ENDIF}
   result := aActiveModel;
{   if aActiveModelIndex = -1 then
      result := nil   //this can´t happen
   else begin
      if safeMode and (aFLAG = 0) then begin
         aFLAG := 1;
         self._VerifyInternalStructures;
         aFLAG := 0;
      end;
      result := TModel(aModels.Objects[aActiveModelIndex]);
      //TModel(aModels.Objects[aActiveModel]).Trace(cTLError,'Memória alocada:'+IntToStr(aLLOCmEMsIZE));
   end;
}
end;

procedure TGenesysApplication._SetActiveModel(model: TModel);
begin
   if aActiveModelIndex >= 0 then begin
      aModels.Objects[aActiveModelIndex] := model;
      aActiveModel := TModel(aModels.Objects[aActiveModelIndex]);
   end;
end;

procedure TGenesysApplication.PlugInVerify(fileName: string; var infos:string);
var Handle: integer;
{$IFDEF IsDLLPlugin}
    umProc: TPluginInitiation;
{$ENDIF}
    procAcessa: TPluginAccess;
    point1, point2: pointer;
    i: integer;
    st: string;
begin
   {--- Verifica se o arquivo informado é realmente uma DLL com um componente do Genesys ---}
   infos := ''; {fails. Its not a valid plug-in. Returna a null string}
   try
      {abre o arquivo, se existir}
{$IFDEF IsDLLPlugin}
      Handle := LoadLibrary(PChar(fileName));
{$ELSE}
      Handle := 1;
{$ENDIF}
      if Handle <> 0 then begin
         {é uma DLL}
{$IFDEF IsDllPlugin}
         @umProc := GetProcAddress(Handle, 'GetComponentMethods');
         if @umProc <> nil then begin
            {e possui o procedimento GetComponentMethods exportado. }
            umProc(@Genesys, procAcessa);
{$ELSE}
         procAcessa := __EXTERNAL__GetProcAddress(fileName);
{$ENDIF}
            {try to get plug-in informations}
            if @procAcessa <> nil then begin
               point1 := @Genesys;
               procAcessa(pmGetInfos, point1, point2);
               {if it could get the informations, then it is considered a valid plug-in}
{ATENÇÂO: a linha de código a seguir é uma fonte de erros constante, embora não sejam erros fatais
          Nenhum motivo aparente para esses erros foi jamais detectado }
               try
                  if point1 <> nil then begin
                     st := string(point1^);
                     for i := 1 to Genesys.AuxFunctions.StrLenght(st) do begin
                        infos := infos + st[i];
                     end;
                  end;
               except
               end;
            end;
{$IFDEF IsDllPlugin}
         end;
         FreeLibrary(Handle);
{$ENDIF}         
      end;
   except
      FreeLibrary(Handle);
   end;
end;

function TGenesysApplication._GetPlugIn(index: integer): TPlugIn;
begin
   if index < aPlugIns.Count then
      result := TPlugIn(aPlugIns.Objects[index])
   else
      result := nil;
end;

function TGenesysApplication._GetPlugInCount: integer;
begin
   result := aPlugIns.Count;
end;


function TGenesysApplication.PlugInIndexOf(kind: string): integer;
var i: integer;
begin
   try
      i := aPlugIns.IndexOf(kind);
      result := i;
   except
      result := -1;
   end;
end;

procedure TGenesysApplication.ModelCreate;
var newModel: TModel;
begin
   newModel := TModel.Create(self);
   //i := aModels.Count;
   //newModel.Name := 'Model '+IntToStr(i+1);
   aModels.AddObject(newModel.Name, newModel);
   aActiveModelIndex := aModels.IndexOf(newModel.Name);
   aActiveModel := TModel(aModels.Objects[aActiveModelIndex]);
end;

function TGenesysApplication._GetModel(name:string):TModel;
var i: integer;
begin
   i := aModels.IndexOf(name);
   if i > -1 then begin
      result := TModel(aModels.Objects[i])
      end
   else
      result := nil;
end;

function TGenesysApplication.PlugInID(kind:string):word;
var i: integer;
begin
   i := Genesys.PlugInIndexOf(kind);
   if i > -1 then
      result := Genesys.PlugIn[i].ID
   else
      result := 0;
end;

procedure TGenesysApplication.Quit;
begin
   // TO DO confirme before quit and destroy ALL models and other structures
//   Model.Destroy;
   Destroy;
end;

destructor TGenesysApplication.Destroy;
var
   i: integer;
begin
   for i := 0 to aModels.Count - 1 do
      TModel(aModels.Objects[i]).Destroy;

   for i := 0 to aPlugIns.Count - 1 do
      TPlugin(aPlugIns.Objects[i]).Destroy;

   inherited;
end;

procedure TGenesysApplication.ModelSetActual(modelName: string);
var i: integer;
begin
   i := aModels.IndexOf(ModelName);
   if i > -1 then begin
      self.aActiveModelIndex := i;
      aActiveModel := TModel(aModels.Objects[i]);
   end;
end;

procedure TGenesysApplication._VerifyInternalStructures;
var i,j: integer;
    tnow: double;
    thisList: TStringList;
    texto,kind: string;
    thisPlugIn: TPlugin;
    thisModule: TModule;
    thisStructure: TModuleStructure;
begin
   try
      {verify plug-ins}
   //   Model.Trace(cTLError,'SafeMode Starting');
      texto := 'verifying plugins';
      for i := 0 to aPlugIns.Count-1 do begin
         thisPlugIn := TPlugin(aPlugIns.Objects[i]);
//         if StrToInt(aPlugIns.Strings[i]) <> thisPlugIn.aID then begin
//            Model.Trace(cTLError,'SafeMode: ID of plugin "'+ thisPlugIn.aTipo +'" differs from string.');
//         end;
         //thisPlugIn.aAcessa_Metodo(
      end;
      {verify modules}
      for i := 0 to Model.aModules.Count-1 do begin
         kind := Model.aModules.Strings[i];
         texto := 'verifying modules of kind "'+kind+'"';
         if (trim(kind) = '') then begin
            Model.Trace(cTLError,'SafeMode: Kind in module list is null string.');
         end;
         thisList := TStringList(Model.aModules.Objects[i]);
         if (thisList = nil) then begin
            Model.Trace(cTLError,'SafeMode: List in module list is nil.');
         end;
         for j := 0 to thisList.Count-1 do begin
            thisModule := TModule(thisList.Objects[j]);
            if thisModule.Kind <> kind then begin
               Model.Trace(cTLError,'SafeMode: Module ID '+IntToStr(thisModule.aID)+' has kind different of the list "'+kind+'".');
            end;
            if StrToInt(thisList.Strings[j]) <> thisModule.ID then begin
               Model.Trace(cTLError,'SafeMode: ID of Module "'+thisModule.aName+'" ID "'+IntToStr(thisModule.aID)+'" and differs from the string "'+thisList.Strings[j]+'"');
            end;
         end;
      end;
      {verify structures}
      tnow := Genesys.Model.TNOW;
      for i := 0 to Model.SIMAN.aModuleStructures.Count-1 do begin
         kind := Model.SIMAN.aModuleStructures.Strings[i];
         texto := 'verifying structures of kind "'+kind+'"';
         if (kind = '') then begin
            Model.Trace(cTLError,'SafeMode: Kind in moduleStructure list is null string.');
         end;
         thisList := TStringList(Model.SIMAN.aModuleStructures.Objects[i]);
         if (thisList = nil) then begin
            Model.Trace(cTLError,'SafeMode: List in moduleStructure list is nil.');
         end;
         for j := 0 to thisList.Count-1 do begin
            if (kind <> cATTRIBUTE) and (kind <> cVARIABLE) then begin
               thisStructure := TModuleStructure(thisList.Objects[j]);
               if thisStructure.Kind <> kind then begin
                  Model.Trace(cTLError,'SafeMode: ModuleStructure ID '+IntToStr(thisStructure.aID)+' has kind different of the list "'+kind+'".');
               end;
               if kind = cEVENT then begin
                  if StrToFloat(thisList.Strings[j]) < tnow then begin
                     Model.Trace(cTLError,'SafeMode: Time of Event ModuleStructure "'+thisStructure.aName+'" before TNOW');
                  end;
               end else if StrToInt(thisList.Strings[j]) <> thisStructure.ID then begin
                  Model.Trace(cTLError,'SafeMode: ID of ModuleStructure "'+thisStructure.aName+'" differs from the string');
               end;
            end;
         end;
      end;
   except
      Model.Trace(cTLError,'SafeMode error: '+texto);
   end;
end;


{ TPROBDISTRIBS }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

constructor TProbDistribs.Create;
begin
   inherited Create;
   aSeed := 1000000000;
   aMultiplier := 950706376;
   aModulo := 2147483647;
   aNormalFlag:=True;
end;

procedure TProbDistribs.Reset;
begin
   aNormalFlag := True;
   aSeed := aSeedInit;
end;


procedure TProbDistribs._SetSeed(Value: comp);
begin
   if (Value<1) or (Value>(aModulo-1)) then begin
      GenesyserrorMessage := 'Seed must be in range 2...2147483646';
      aSeed := 1000000000;
      end
   else
      aSeed  := Value;
   aSeedInit := aSeed;
end;

function TProbDistribs._GetSeed: comp;
begin
   if (aSeed<1) or (aSeed>(aModulo-1)) then begin
      aSeed := 1000000000;
      aSeedInit := aSeed;
   end;
   result := aSeed;
end;


procedure TProbDistribs._SetMultiplier(Value: comp);
begin
   if (Value<2) or (Value>(aModulo-1)) then begin
      GenesyserrorMessage := 'Multiplier must be in range 2...2147483646';
      aMultiplier  := 950706376;
      end
   else
      aMultiplier := Value;
end;

function TProbDistribs._GetMultiplier: comp;
begin
   if (aMultiplier<2) or (aMultiplier>(aModulo-1)) then
      aMultiplier := 950706376;
   Result := aMultiplier;
end;

function TProbDistribs._Uni01: double;
begin
   aSeed  := aSeed * aMultiplier;
   aSeed  := aSeed - Int(aSeed/aMODULO) * aMODULO;
   Result := aSeed / aMODULO;
end;


function TProbDistribs.Uniform(limiteInf: double; limiteSup: double): double;
begin
   if (limiteInf<0) or (limiteSup<0) or (limiteSup<limiteInf) then begin
      GenesyserrorMessage := 'Parâmetros incorretos de Uniform';
      result := 0.0;
      Exit;
   end;
   Result := limiteInf + (limiteSup-limiteInf) * _Uni01
end;


function TProbDistribs.Exponential(media: double): double;
begin
   if media>=0.0 then
      result := media*(-ln(_Uni01))
   else begin
      GenesyserrorMessage := 'Parâmetro incorreto de Exponential';
      result := 0;
   end;
end;


function TProbDistribs.Erlang(media: double; M: integer): double;
var
   i: integer;
   P: double;
begin
   if (media<0.0) or (M<=0) then begin
      GenesyserrorMessage := 'Parâmetros incorretos de Erlang';
      result := 0.0;
      exit;
   end;
   P := 1;
   for i := 1 to M do
     P := P * _Uni01;
   result := (media/M) * (-ln(P));
end;


function TProbDistribs.Normal(media: double; desvio: double): double;
var U1,U2: double;
    W,Y: double;
begin
   if (media<=0.0) or (desvio<=0.0) then begin
      GenesyserrorMessage := 'Parâmetro "desvio" incorreto de Normal';
      result := 0.0;
      Exit;
   end;

   if aNormalFlag then begin
      repeat
         U1 := 2 * _Uni01-1.0;
         U2 := 2 * _Uni01-1.0;
         W  := U1 * U1+U2*U2;
      until not (W>=1.0);
      Y:= sqrt((-2* ln (W)) / W);
      result := media + U1*Y*desvio;
      aNormalresult := media + U2*Y*desvio;
      aNormalFlag := False;
   end
   else begin
      result := aNormalResult;
      aNormalFlag:=True;
   end;
end;


function TProbDistribs._GammaJonk(Alpha: double ): double;
var R,R1,R2,X,Y:double;
begin
   repeat
       repeat
         R1 := _Uni01;
         R2 := _Uni01;
       until ((R1>1e-30) and (R2>1e-30));
       if (ln(R2)/alpha<-1e3) then
          X := 0
       else
          X := exp(ln(R2)/alpha);
       if (ln(R1)/(1-alpha)<-1e3) then
          Y := 0
       else
          Y := exp(ln(R1)/(1-alpha));
   until (X+Y <= 1);
   repeat
      R := _Uni01;
   until (R>1e-20);
   result := -ln(R)*X/(Y+X);
end;


function TProbDistribs.Gamma(media: double; Alpha: double): double;
   var
   i: integer;
   P: double;
   IntAlpha: integer;
   OstAlpha: double;
begin

   if (media<=0.0) or (Alpha<=0.0) then
   begin
      GenesyserrorMessage := 'Parâmetros incorretos de Gamma';
      result := 0.0;
      Exit;
   end;
   if Alpha<1.0 then
      result := (media/Alpha) * _GammaJonk(Alpha)
   else begin
      if Alpha=1.0 then
         result := media*(-ln(_Uni01))
      else begin
         IntAlpha := round(Int(Alpha));
         OstAlpha := Alpha-IntAlpha;
         repeat
            P := 1;
            for i := 1 to IntAlpha do
               P := P * _Uni01;
         until P > 0;
         if OstAlpha > 0 then
            result := (media/Alpha)*((-ln(P)) + _GammaJonk(OstAlpha))
         else
            result := (media/Alpha)*(-ln(P));
      end;
   end;
end;


function TProbDistribs.Beta(ShapeAlpha: double; ShapeBeta: double;
                         limiteInf: double; limiteSup: double): double;
var
   X,Y1,Y2: double;
begin

   if (ShapeAlpha<=0.0) or (ShapeBeta<=0.0) or (limiteInf>limiteSup) or
      (limiteInf<0) or (limiteSup<0) then begin
      GenesyserrorMessage := 'Parâmetros incorretos de Beta';
      result := 0.0;
      Exit;
   end;

   repeat
     Y1 := Gamma(ShapeAlpha,ShapeAlpha);
     Y2 := Gamma(ShapeBeta,ShapeBeta);
     X  := Y1 / (Y1+Y2);
   until (X>=0) and (X<=1.0);
   result :=  limiteInf + (limiteSup - limiteInf ) * X;
end;


function TProbDistribs.Weibull(Alpha: double; Scale: double): double;
begin
   if (Alpha<=0.0) or (Scale<=0.0) then begin
      GenesyserrorMessage := 'Parâmetros incorretos de Weibull';
      result := 0.0;
      Exit;
   end;
   result :=  exp(ln(Scale*(-ln(_Uni01)))/Alpha);
end;


function TProbDistribs.Lognormal(media: double; desvio: double): double;
var
   mediaNorm,DispNorm: double;
begin

   if (media<=0.0) or (desvio<=0.0) then begin
      GenesyserrorMessage := 'Parâmetros incorretos de Lognormal';
      result := 0.0;
      Exit;
   end;

   DispNorm  := ln((desvio*desvio) / (media*media)+1.0);
   mediaNorm := ln(media)- 0.5*DispNorm;
   result := Exp(Normal(mediaNorm, SQRT(DispNorm)));
end;


function TProbDistribs.Triangular(Min: double; Mode: double; Max: double): double;
var
    Part1,Part2,Full,R: double;
begin

   if (Min>Mode) or (Max<Mode) or (Min>Max) or
      (Min<0) or (Max<0) or (Mode<0) then begin
      GenesyserrorMessage := 'Parâmetros incorretos de Triangular';
      result := 0.0;
      Exit;
   end;

   Part1 := Mode-Min;
   Part2 := Max-Mode;
   Full := Max-Min;
   R := _Uni01;
   if R <= Part1/Full then
      result := Min+sqrt(Part1*Full*R)
   else
      result := Max-sqrt(Part2*Full*(1.0-R));
end;



{ TWaitingResource }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

constructor TWaitingResource.Create(novaEntid, novoIdBloco: word;
  novaQuant: integer);
begin
   inherited Create(novaEntid, novoIDBloco);
   aQuantidade := novaQuant;
end;


{ TSourceModule }
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

constructor TSourceModule.Create(novoId: word; novoNome, novoKind: string);
begin
   inherited;
   aFirstCreation := 0;
   aEntitiesPerCreation := '1';
   aEntityTypeID := 1;
end;



{ TAuxiliarFuncions }

{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

procedure TAuxiliarFunctions.AdjustFloatFormat(var floatValue:string);
var i: integer;
begin
   { TODO 5 -oRafael Cancian -cFunções de auxílio : Resolver questão de ponto e vírgula dependendo da configuração }
   // Troca "." por ","  ////DEPENDE DA CONFIGURACAO DE IDIOMA
   repeat
      i := StrPos(floatValue, '.');
      if i > 0 then
         floatValue[i] := ',';
   until i = 0;
end;

function  TAuxiliarFunctions.Underscore(texto: string): string;
var i: integer;
begin
   // Troca " " por "_". Impede nomes com espaços no meio
   repeat
      i := StrPos(texto, ' ');
      if i > 0 then
         texto[i] := '_';
   until i = 0;
   result := texto;
end;

function TAuxiliarFunctions.FillValueWithZeros(valor: double; tamanho: integer): string;
var i: integer;
    final: string;
begin
  final := '';
  for i := 1 to tamanho do
     final := final + '0';
  final := FormatFloat(final+'.'+final, valor);
   result := final;
end;

function TAuxiliarFunctions.StrIdent(num: integer): string;
begin
   { Returns a string with spaces for identation }
   result := StringOfChar(' ', num*5);
end;

procedure TAuxiliarFunctions.SeparateWords(texto: string; separador: char; var wordsList: TStringList);
var i: integer;
    aux: string;
begin
   { Receives a 'texto' string and returns a list of strings, wich are the words in the 'texto' string separetad by a 'separador' character' }
   wordsList.Clear;
   i := 1;
   aux := '';
   while (i <= StrLen(PChar(texto))) do begin
      if (texto[i] = separador) then begin
         wordsList.Add(Trim(aux));
         aux := '';
         end
      else begin
         aux := aux + texto[i];
      end;
      i := i + 1;
   end;
   if texto <> '' then begin
      wordsList.Add(Trim(aux)); {inclui a última wordsList}
   end;
end;

function TAuxiliarFunctions.Substring(texto: string; inicio, chars: integer): string;
var aux: string;
    i, tam: integer;
begin
   { Returns a substring of 'texto' }
   aux := '';
   i := inicio;
   tam := StrLenght(texto);
   while (chars > 0) and (i <=tam) do begin
      aux := aux + texto[i];
      i := i + 1;
      chars := chars - 1;
   end;
   result := aux;
end;

function TAuxiliarFunctions.LookForChar(texto: string; caract: char; inicio: integer): integer;
var achou: boolean;
    i, tam: integer;
begin
   { Returns de first occurance of 'caract' char on the 'texto' string }
   achou := false;
   i := inicio;
   tam := StrLenght(texto);
   while not achou and (i <= tam) do begin
      achou := texto[i] = caract;
      i := i + 1;
   end;
   if (achou) then
      result := i - 1
   else
      result := 0;
end;

function TAuxiliarFunctions.StrLenght(texto: string): integer;
begin
   { Returns the string lenght }
   result := Length(PChar(texto));
end;

function TAuxiliarFunctions.StrLeft(texto: string; chars: integer): string;
var i, tam: integer;
    aux: string;
begin
   { Returns the 'chars' leftmost in the 'texto' string }
   tam := StrLenght(texto);
   if chars > tam then
      chars := tam;
   aux := '';
   i := 1;
   for i := i to chars do
      aux := aux + texto[i];
   result := aux;
end;

function TAuxiliarFunctions.StrRight(texto: string; chars: integer): string;
var i, tam: integer;
    aux: string;
begin
   { Returns the 'chars' rightmost in the 'texto' string }
   aux := '';
   tam := StrLenght(texto);
   if chars > tam then
      chars := tam;
   for i := tam-chars+1 to tam do
      aux := aux + texto[i];
   result := aux;
end;

function TAuxiliarFunctions.StrPos(texto, substr: string): integer;
begin
   { Returns the first occurance of 'substr' in 'texto' }
   result := Pos(substr, texto);
end;

procedure TAuxiliarFunctions.SeparatePathAndFileName(caminho: string; var diretorio:string; var arquivo:string);
begin
   diretorio := ExtractFilePath(caminho);
   arquivo   := ExtractFileName(caminho);
end;


procedure TAuxiliarFunctions.ReadInitialModule(Module_Kind:string; var thisModule:TModule; var wordsList:TStringList);
var listaIDs: TStringList;
    i: integer;
begin
   try
      listaIDs := TStringList.Create;
      listaIDs.Sorted := false;
      {modelStructure}
//      newID := Genesys.Model.ModuleAdd(MODULE_KIND);
//      thisModule := TNewModule(Genesys.Model.ModuleByID(newID));
      thisModule.Kind := wordsList.Strings[0];
      thisModule.Id := StrToInt(wordsList.Strings[1]); {ID of module}
      thisModule.Name := Genesys.AuxFunctions.Underscore(wordsList.Strings[2]);
      {model basics}
      ///thisModule.description := wordsList.Strings[4];
      listaIDs.Clear;
      Get_Lista_Proximos(wordsList.Strings[3], listaIDs);
      for i := 0 to listaIDs.Count - 1 do begin
        thisModule.NextID[i] := StrToInt(listaIDs.Strings[i]);
      end;
      thisModule.aInterfaceReserved := wordsList.Strings[4];
      {exclude 5 first words [0,4] from list}
      for i := 0 to 4 do begin
         wordsList.Delete(0);
      end;
      //listaIDs.Free;
   except
       Genesys.Model.Trace(1, 'Error: Plugin "' + MODULE_KIND + '" could not read basic part of module: ' + thisModule.Name);
   end;
end;

procedure TAuxiliarFunctions.SaveInitialModule(Module_Kind:string; thisModule:TModule; var wordsList:TStringList);
var texto: string;
    i: integer;
begin
   wordsList.Clear;
   {module structure}
   wordsList.Add(MODULE_KIND);             {[0]}
   wordsList.Add(IntToStr(thisModule.ID)); {[1]}
   wordsList.Add(thisModule.Name);         {[2]}
   {module basics}
   texto := '';
   for i := 0 to thisModule.NextCount-1 do begin
      texto := texto + thisModule.NextIDs.Strings[i] + ','
   end;
   wordsList.Add(texto);                          {[3]}
   wordsList.Add(thisModule.aInterfaceReserved ); {[4]}
   //for i := 4 to 9 do
   //   wordsList.Add('-');
end;


procedure TAuxiliarFunctions.Get_Lista_Proximos(texto: string; var IDProximos: TStringList);
var inicio, pos1: integer;
    proximo: string;
begin
   {-- Recebe um texto no formato ID1,ID2,...,IDn --}
   {-- e devolve uma Lista: com os IDs desses blocos no formato [ID1],[ID2],...,[IDn] --}
   if IDProximos = nil then IDProximos := TStringList.Create;
   IDProximos.Sorted := false;
   IDProximos.Clear;
   if Genesys.AuxFunctions.StrRight(texto,1) <> ',' then texto := texto + ',';
   inicio := 1;
   pos1 := 1;
   while pos1 < Genesys.AuxFunctions.StrLenght(texto) do begin
      pos1 := Genesys.AuxFunctions.LookForChar(texto, ',', inicio);
      proximo := Genesys.AuxFunctions.Substring(texto, inicio, pos1-inicio);
      IDProximos.Add(trim(proximo));
      inicio := pos1 + 1;
   end;
end;

procedure TAuxiliarFunctions.VerifySymbol(moduleName,expressionName, expression, resultType: string; mandatory: boolean);
var res: double;
    i: integer;
begin
   try
      if GenesysErrorMessage = '' then begin
         Genesys.Model.Trace(cTLModuleDetail, Genesys.AuxFunctions.StrIdent(2)+'- Verifying module ' + moduleName + ' with ' + expressionName + ': ' + expression);
         if mandatory and (expression = '') then
            GenesysErrorMEssage := expressionname + ' in "' + moduleName + '" has a null expression'
         else if expression <> '' then begin
            if resultType = cEXPRESSION then begin
               yynerrs := 0;
               res := Genesys.Model.SIMAN.StringEvaluateFormula(expression);
               if yynerrs > 0 then
                  GenesysErrorMessage := expressionname + ' in "' + moduleName + '" has an error in expression "' + expression + '"';
               end
            else if resultType = cRESOURCE then begin
               i := Genesys.Model.SIMAN.ResourceIndex(expression);
               if i =-1 then
                  GenesysErrorMessage := expressionname + ' in "' + moduleName + '" has an inexistent resource specified as "' + expression + '"';
               end
            else if resultType = cQUEUE then begin
               i := Genesys.Model.SIMAN.QueueIndex(expression);
               if i =-1 then
                  GenesysErrorMessage := expressionname + ' in "' + moduleName + '" has an inexistent queue specified as "' + expression + '"';
               end
            else if resultType = cATTRIBUTE then begin
               i := Genesys.Model.SIMAN.AttributeIndex(expression);
               if i =-1 then
                  GenesysErrorMessage := expressionname + ' in "' + moduleName + '" has an inexistent attribute specified as "' + expression + '"';
               end
            else if resultType = cRESOURCE then begin
               i := Genesys.Model.SIMAN.ResourceIndex(expression);
               if i =-1 then
                  GenesysErrorMessage := expressionname + ' in "' + moduleName + '" has an inexistent resource specified as "' + expression + '"';
               end
            else if resultType = cSET then begin
               i := Genesys.Model.SIMAN.SetIndex(expression);
               if i =-1 then
                  GenesysErrorMessage := expressionname + ' in "' + moduleName + '" has an inexistent set specified as "' + expression + '"';
               end
            else if resultType = cFORMULA then begin
               i := Genesys.Model.SIMAN.FormulaIndex(expression);
               if i =-1 then
                  GenesysErrorMessage := expressionname + ' in "' + moduleName + '" has an inexistent formula specified as "' + expression + '"';
               end
            else begin
               //what else could be
            end;
         end;
         if GenesysErrorMessage <> '' then Genesys.Model.Trace(cTLError,Genesys.AuxFunctions.STrIdent(1)+GenesysErrorMessage);
      end;
   except
      GenesysErrorMessage := expressionname + ' in "' + moduleName + '" has a fatal error in expression "' + expression + '"';
      Genesys.Model.Trace(cTLError, Genesys.AuxFunctions.StrIdent(1)+GenesysErrorMessage);
   end;
end;


function TAuxiliarFunctions.TimeUnitToInt(timeunit:TTimeUnit): integer;
begin
    if timeunit = tups then result := 0
    else if timeunit = tuns then result := 1
    else if timeunit = tuus then result := 2
    else if timeunit = tums then result := 3
    else if timeunit = tus then result := 4
    else if timeunit = tumin then result := 5
    else if timeunit = tuh then result := 6
    else if timeunit = tuday then result := 7
    else if timeunit = tuweek then result := 8
    else if timeunit = tumounth then result := 9
    else if timeunit = tuyear then result := 10
    else if timeunit = tudecade then result := 11
    else if timeunit = tucentury then result := 12
    else result := -1 {unknown};
end;

function TAuxiliarFunctions.IntToTimeUnit(value:integer): TTimeUnit;
begin
   case value of
      0: result := tups;
      1: result := tuns;
      2: result := tuus;
      3: result := tums;
      4: result := tus;
      5: result := tumin;
      6: result := tuh;
      7: result := tuday;
      8: result := tuweek;
      9: result := tumounth;
     10: result := tuyear;
     11: result := tudecade;
     12: result := tucentury;
      else result := tups;
   end;
end;

function TAuxiliarFunctions.IntToResourceState(
  value: integer): TResourceState;
begin
   case value of
      0: result := rsIdle;
      1: result := rsBusy;
      2: result := rsFailed;
      3: result := rsInactive;
   else
      result := rsOther;
   end;
end;

function TAuxiliarFunctions.ResourceStateToInt(
  state: TResourceState): integer;
begin
   case state of
      rsIdle: result := 0;
      rsBusy: result := 1;
      rsFailed: result := 2;
      rsInactive: result := 3;
      rsOther: result := 4;
   end;
end;


constructor TAuxiliarFunctions.Create;
begin
   inherited;
end;

function TAuxiliarFunctions.TimeUnitConvert(timeunit1, timeunit2:TTimeUnit): double;
var scalevalues: array[0..12] of double;
    ini,fim, i: integer;
    res: double;
begin
   {base unit: s}
   scalevalues[0]  := 1;
   scalevalues[1]  := 1000;
   scalevalues[2]  := 1000;
   scalevalues[3]  := 1000;
   scalevalues[4]  := 1000;
   scalevalues[5]  := 60;
   scalevalues[6]  := 60;
   scalevalues[7]  := 24;
   scalevalues[8]  := 7;
   scalevalues[9]  := 365.25/12/7;
   scalevalues[10] := 12;
   scalevalues[11] := 10;
   scalevalues[12] := 10;
   ini := TimeUnitToInt(timeunit1);
   fim := TimeUnitToInt(timeUnit2);
   res := 1;
   if ini <= fim then begin
      for i := ini+1 to fim do
         res := res / scaleValues[i];
      end
   else begin
      for i := fim+1 to ini do
         res := res * scaleValues[i];
   end;
   result := res;
end;


{ TSet }

{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}

constructor TSet.Create(novoId: word; novoNome: string);
begin
   inherited Create(novoID, novoNome, cSET);
   aMembersType := cRESOURCE;
   aMembers := TStringList.Create;
   aMembers.Sorted := false;
end;

function TSet._GetCount: integer;
begin
   result := aMembers.Count;
end;

function TSet._GetName(index: word): string;
begin
   if index < aMembers.Count then
      result := aMembers.Strings[index]
   else
      result := '';
end;

{ TFailure }

constructor TFailure.Create(novoId: word; novoNome: string);
begin
   inherited Create(novoID, novoNome, cFAILURE);
   aType := ftCount;
   aCount := '';
   aUpTime := '';
   aUpTimeUnit := tuPs;
   aStateOnly := false;
   aUpTimeInThisStateOnly := rsBusy;
   aDownTime := '';
   aDownTimeUnit := tuPs;
end;


{ TFormula }

constructor TFormula.Create(novoId: word; novoNome: string);
begin
  inherited;
  aKind := cFORMULA;
end;


{ INITIALIZATION }
begin
   CoInitialize(nil);
end.

//Initialization
//   CoInitialize(nil);

