/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestODE.cpp
 * Author: rlcancian
 * 
 * Created on 26 de Setembro de 2019, 13:00
 */

#include "TestODE.h"
#include "Delay.h"
#include "ComponentManager.h"
#include "Simulator.h"

#include "Create.h"
#include "Dispose.h"
#include "ODE.h"


TestODE::TestODE() {
}

int TestODE::main(int argc, char** argv) {
    Simulator* simulator = new Simulator();
    TraceManager* tm = simulator->getTraceManager();
    tm->setTraceLevel(Util::TraceLevel::mostDetailed);
    this->setDefaultTraceHandlers(tm);
    this->insertFakePluginsByHand(simulator);
    Model* model = new Model(simulator);
    ComponentManager* components = model->getComponentManager();
    ElementManager* elements = model->getElementManager();
    //
    EntityType* entityType1 = new EntityType(elements, "ET1");
    elements->insert(Util::TypeOf<EntityType>(), entityType1);
    Create* create1 = new Create(model);
    create1->setEntityType(entityType1);
    create1->setTimeBetweenCreationsExpression("1.0");
    components->insert(create1);
    Delay* delay1 = new Delay(model);
    delay1->setDelayExpression("1");
    components->insert(delay1); 
    Dispose* dispose1 = new Dispose(model);
    //ODE* ode1 = new ODE(model);
    //components->insert(ode1);
    create1->getNextComponents()->insert(delay1);
    delay1->getNextComponents()->insert(dispose1);
    //
    simulator->getModelManager()->insert(model);
    if (model->checkModel()) {
	model->saveModel("./temp/testODE.txt");
    }
    model->getSimulation()->startSimulation();
    return 0;
}