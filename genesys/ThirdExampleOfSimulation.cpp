/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ThirdExampleOfSimultion.cpp
 * Author: rlcancian
 * 
 * Created on 24 de Setembro de 2019, 16:43
 */

#include "ThirdExampleOfSimultion.h"

// you have to included need libs

// GEnSyS Simulator
#include "Simulator.h"

// Model Components
#include "Create.h"
#include "Seize.h"
#include "Delay.h"
#include "Release.h"
#include "Dispose.h"

// Model elements
#include "EntityType.h"


ThirdExampleOfSimulation::ThirdExampleOfSimulation() {
}

/**
 * This is the main function of the application. 
 * It instanciates the simulator, builds a simulation model and then simulate that model.
 */
int ThirdExampleOfSimulation::main(int argc, char** argv) {
    Simulator* simulator = new Simulator();
    // Handle traces and simulation events to output them
    TraceManager* tm = simulator->getTraceManager();
    this->setDefaultTraceHandlers(tm);
    tm->setTraceLevel(Util::TraceLevel::mostDetailed);
    this->insertFakePluginsByHand(simulator);
    Model* model = new Model(simulator);
    // get easy access to classes used to insert components and elements into a model
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();
    //
    // build the simulation model
    //
    // buildModelWithAllImplementedComponents
    ModelInfo* infos = model->getInfos();
    infos->setReplicationLength(60);
    infos->setReplicationLengthTimeUnit(Util::TimeUnit::second);
    infos->setNumberOfReplications(3);
    //
    EntityType* customer = new EntityType(elements, "Customer");
    elements->insert(Util::TypeOf<EntityType>(), customer);
    //
    Create* create1 = new Create(model);
    create1->setEntityType(customer);
    create1->setTimeBetweenCreationsExpression("norm(3,1)");
    create1->setTimeUnit(Util::TimeUnit::second);
    create1->setEntitiesPerCreation(1);
    components->insert(create1);
    //
    Resource* machine1 = new Resource(elements, "Machine_1");
    machine1->setCapacity(1);
    elements->insert(Util::TypeOf<Resource>(), machine1);
    //
    Queue* queueSeize1 = new Queue(elements, "Queue_Machine_1");
    queueSeize1->setOrderRule(Queue::OrderRule::FIFO);
    elements->insert(Util::TypeOf<Queue>(), queueSeize1);
    //
    Seize* seize1 = new Seize(model);
    seize1->setResource(machine1);
    seize1->setQueue(queueSeize1);
    components->insert(seize1);
    //
    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("norm(3,1)");
    delay1->setDelayTimeUnit(Util::TimeUnit::second);
    components->insert(delay1);
    //
    Release* release1 = new Release(model);
    release1->setResource(machine1);
    components->insert(release1);
    //
    Dispose* dispose1 = new Dispose(model);
    components->insert(dispose1);
    // connect model components to create a "workflow"
    create1->getNextComponents()->insert(seize1);
    seize1->getNextComponents()->insert(delay1);
    delay1->getNextComponents()->insert(release1);
    release1->getNextComponents()->insert(dispose1);
    // insert the model into the simulator 
    simulator->getModelManager()->insert(model);

    // if the model is ok then save the model into a text file 
    if (model->checkModel()) {
	model->saveModel("./temp/thirdExampleOfSimulation.txt");
    }

    // execute the simulation
    model->getSimulation()->startSimulation();

    return 0;
};
