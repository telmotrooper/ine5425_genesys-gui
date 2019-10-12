/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyReGenESYsApplication.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 20 de Maio de 2019, 21:01
 */

#include "BuildSimulationModel03.h"
#include "GenesysConsole.h"

// GEnSyS Simulator
#include "Simulator.h"

// Model Components
#include "Create.h"
#include "Delay.h"
#include "Dispose.h"
#include "Seize.h"
#include "Release.h"
#include "Assign.h"
#include "Record.h"
#include "Decide.h"
#include "Dummy.h"

// Model elements
#include "ElementManager.h"
#include "EntityType.h"
#include "Attribute.h"
#include "Variable.h"
#include "ProbDistrib.h"
#include "EntityGroup.h"
#include "Formula.h"
#include "ODE.h"

BuildSimulationModel03::BuildSimulationModel03() {
}

void _buildMostCompleteModel(Model* model) {
    // buildModelWithAllImplementedComponents
    ModelInfo* infos = model->getInfos();
    infos->setAnalystName("Your name");
    infos->setProjectTitle("The title of the project");
    infos->setDescription("The description of the project");
    infos->setReplicationLength(1e3);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::minute);
    infos->setNumberOfReplications(10);
    infos->setWarmUpPeriod(50);
    infos->setWarmUpPeriodTimeUnit(Util::TimeUnit::minute);
    infos->setDescription("./models/model99_AllTogether.txt");

    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();

    EntityType* entityType1 = new EntityType(elements, "Representative_EntityType");
    elements->insert(Util::TypeOf<EntityType>(), entityType1);

    Create* create1 = new Create(model);
    create1->setEntityType(entityType1);
    create1->setTimeBetweenCreationsExpression("EXPO(5)");
    create1->setTimeUnit(Util::TimeUnit::minute);
    create1->setEntitiesPerCreation(1);
    components->insert(create1);

    Attribute* attribute1 = new Attribute("Attribute_1");
    elements->insert(Util::TypeOf<Attribute>(), attribute1);
    Variable* variable1 = new Variable("Variable_1");
    elements->insert(Util::TypeOf<Variable>(), variable1);

    Assign* assign1 = new Assign(model);
    Assign::Assignment* attrib2Assignment = new Assign::Assignment(Assign::DestinationType::Variable, "Variable_1", "Variable_1 + 1");
    assign1->getAssignments()->insert(attrib2Assignment);
    Assign::Assignment* attrib1Assignment = new Assign::Assignment(Assign::DestinationType::Attribute, "Attribute_1", "Variable_1");
    assign1->getAssignments()->insert(attrib1Assignment);
    components->insert(assign1);

    Decide* decide1 = new Decide(model);
    //decide1->getConditions()->insert("UNIF(0,1)>=0.5");
    decide1->getConditions()->insert("NQ(Queue_Machine_1) <= 2*NQ(Queue_Machine_2)");

    Resource* machine1 = new Resource(elements, "Machine_1");
    machine1->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), machine1);

    Queue* queueSeize1 = new Queue(elements, "Queue_Machine_1");
    queueSeize1->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), queueSeize1);

    Seize* seize1 = new Seize(model);
    seize1->setResource(machine1);
    seize1->setQueue(queueSeize1);
    components->insert(seize1);

    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("NORM(5,1.5)");
    delay1->setDelayTimeUnit(Util::TimeUnit::minute);
    components->insert(delay1);

    Release* release1 = new Release(model);
    release1->setResource(machine1);
    components->insert(release1);

    Record* record1 = new Record(model);
    record1->setExpressionName("Time in system after releasing machine 1");
    record1->setExpression("TNOW - Entity.ArrivalTime");
    record1->setFilename("./temp/TimeAfterMachine1.txt");
    components->insert(record1);

    Dispose* dispose1 = new Dispose(model);
    components->insert(dispose1);

    Resource* machine2 = new Resource(elements, "Machine_2");
    machine2->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), machine2);

    Queue* queueSeize2 = new Queue(elements, "Queue_Machine_2");
    queueSeize2->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), queueSeize2);

    Seize* seize2 = new Seize(model);
    seize2->setResource(machine2);
    seize2->setQueue(queueSeize2);
    components->insert(seize2);

    Delay* delay2 = new Delay(model);
    delay2->setDelayExpression("NORM(5,1.5)");
    delay2->setDelayTimeUnit(Util::TimeUnit::minute);
    components->insert(delay2);

    Release* release2 = new Release(model);
    release2->setResource(machine2);
    components->insert(release2);

    Record* record2 = new Record(model);
    record2->setExpressionName("Time in system after releasing machine 2");
    record2->setExpression("TNOW - Entity.ArrivalTime");
    record2->setFilename("./temp/TimeAfterMachine2.txt");
    components->insert(record2);

    Dummy* dummy1 = new Dummy(model);
    components->insert(dummy1);

    // connect model components to create a "workflow" -- should always start from a SourceModelComponent and end at a SinkModelComponent (it will be checked)
    create1->getNextComponents()->insert(assign1);
    assign1->getNextComponents()->insert(decide1);
    decide1->getNextComponents()->insert(seize1);
    decide1->getNextComponents()->insert(seize2);
    seize1->getNextComponents()->insert(delay1);
    delay1->getNextComponents()->insert(release1);
    release1->getNextComponents()->insert(record1);
    record1->getNextComponents()->insert(dispose1);
    seize2->getNextComponents()->insert(delay2);
    delay2->getNextComponents()->insert(release2);
    release2->getNextComponents()->insert(record2);
    record2->getNextComponents()->insert(dummy1);
    dummy1->getNextComponents()->insert(dispose1);
}

/**
 * This function shows an example of how to create a simulation model.
 * It creates some handlers for tracing (debug) and for events, set model infos and than creates the model itself.
 * The model is a composition of components (and elements that they use), connected to form a process/fluxogram 
 * @param model - The instance returned that will contains the built model
 */
void BuildSimulationModel03::builAndRunSimulationdModel() {
    Simulator* simulator = new Simulator();

    // traces handle and simulation events to output them
    TraceManager* tm = simulator->getTraceManager();
    //tm->addTraceHandler(&traceHandlerFunction);
    //tm->addTraceReportHandler(&traceHandlerFunction);
    //tm->addTraceSimulationHandler(&traceSimulationHandlerFunction);  

    // Insert some fake plugins, since components and elements are NOT dynamic linked. 
    // Basically all ModelComponents and ModelElements classes that may de used to buikd simulation models and to be persisted to files, should be "declared" by plugins.
    this->insertFakePluginsByHand(simulator);

    Model* model = new Model(simulator);

    OnEventManager* ev = model->getOnEventManager();
    //ev->addOnSimulationStartHandler(&onSimulationStartHandlerFunction);
    //ev->addOnReplicationStartHandler(&onReplicationStartHandlerFunction);
    //ev->addOnReplicationEndHandler(&onReplicationEndHandlerFunction);
    //ev->addOnProcessEventHandler(&onProcessEventHandlerFunction);
    
    _buildMostCompleteModel(model);

    //simulator->getModelManager()->insert(model);
    //model->saveModel(model->getInfos()->getDescription());

    //simulator->getModelManager()->loadModel("./models/model99_AllTogether.txt");
    //simulator->getModelManager()->loadModel("./models/model01_CreDelDis.txt");

    //model->checkModel();
    //model->show();
    model->getSimulation()->startSimulation();
}

int BuildSimulationModel03::main(int argc, char** argv) {
    this->builAndRunSimulationdModel();
    return 0;
}