/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SecondExampleOfSimulation.cpp
 * Author: rlcancian
 * 
 * Created on 3 de Setembro de 2019, 18:59
 */

#include "SecondExampleOfSimulation.h"
#include "SinkModelComponent.h"

// you have to included need libs

// GEnSyS Simulator
#include "Simulator.h"

// Model Components
#include "Create.h"
#include "Delay.h"
#include "Dispose.h"

// Model elements
#include "EntityType.h"

SecondExampleOfSimulation::SecondExampleOfSimulation() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int SecondExampleOfSimulation::main(int argc, char** argv) {
    Simulator* simulator = new Simulator();

    // insert "fake plugins" since plugins based on dynamic loaded library are not implemented yet
    this->insertFakePluginsByHand(simulator);

    // creates an empty model
    Model* model = new Model(simulator);

    // Handle traces and simulation events to output them
    TraceManager* tm = model->getTraceManager();
    this->setDefaultTraceHandlers(tm);

    // get easy access to classes used to insert components and elements into a model
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();

    //
    // build the simulation model
    //
    
    // set general info about the model
    ModelInfo* infos = model->getInfos();
    infos->setAnalystName("Your name");
    infos->setProjectTitle("The title of the project");
    infos->setDescription("This simulation model tests one of the most basic models possible.");
    infos->setReplicationLength(30);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::minute); // each replication will last 30 minutes (simulated time)
    infos->setNumberOfReplications(3); // replicates the simulation 3 times
    
    // set the trace level of simulation to "blockArrival" level, which is an intermediate level of tracing
    simulator->getTraceManager()->setTraceLevel(Util::TraceLevel::blockArrival);

    // create a (Source)ModelElement of type EntityType, used by a ModelComponent that follows
    EntityType* entityType1 = new EntityType(elements, "Type_of_Representative_Entity");
    elements->insert(Util::TypeOf<EntityType>(), entityType1);

    // create a ModelComponent of type Create, used to insert entities into the model
    Create* create1 = new Create(model);
    create1->setEntityType(entityType1);
    create1->setTimeBetweenCreationsExpression("Expo(2)");
    create1->setTimeUnit(Util::TimeUnit::minute);
    create1->setEntitiesPerCreation(1);
    components->insert(create1);

    // create a ModelComponent of type Delay, used to represent a time delay 
    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("NORM(1,0.2)");
    delay1->setDelayTimeUnit(Util::TimeUnit::minute);
    components->insert(delay1);

    // create a (Sink)ModelComponent of type Dispose, used to remove entities from the model
    Dispose* dispose1 = new Dispose(model);
    components->insert(dispose1);

    // connect model components to create a "workflow" 
    create1->getNextComponents()->insert(delay1);
    delay1->getNextComponents()->insert(dispose1);

    // insert the model into the simulator 
    simulator->getModelManager()->insert(model);

    // if the model is ok then save the model into a text file 
    if (model->checkModel()) {
	model->saveModel("./temp/secondExampleOfSimulation.txt");
    }

    // execute the simulation
    model->getSimulation()->startSimulation();

    return 0;
};

