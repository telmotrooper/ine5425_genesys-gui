/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimulationModel.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 21 de Junho de 2018, 15:01
 */

#include <typeinfo>
#include <iostream>
#include <algorithm>
#include <string>

#include "Model.h"
#include "SourceModelComponent.h"
#include "Simulator.h"
#include "StatisticsCollector.h"
#include "Traits.h"

bool EventCompare(const Event* a, const Event * b) {
    return a->getTime() < b->getTime();
}

double getReplicationLengthNotMemberFunction() { // REMOVE IT. JUST AN EXAMPLE FOR PAN TEAM DS3 THEME (1)
    return 10;
}

void setReplicationLengthNotMemberFunction(double value) { // REMOVE IT. JUST AN EXAMPLE FOR PAN TEAM DS3 THEME (1)

}

Model::Model(Simulator* simulator) {
    _parentSimulator = simulator; // a simulator is the "parent" of a model 
    // 1:1 associations (no Traits)
    _modelInfo = new ModelInfo();
    _eventManager = new OnEventManager(); // should be on .h (all that does not depends on THIS)
    _elementManager = new ElementManager(this);
    _componentManager = new ComponentManager(this);
    _traceManager = simulator->getTraceManager(); // every model starts with the same tracer, unless a specific one is set
    // 1:1 associations (Traits)
    _parser = new Traits<Parser_if>::Implementation(this);
    _modelChecker = new Traits<ModelChecker_if>::Implementation(this);
    _modelPersistence = new Traits<ModelPersistence_if>::Implementation(this);
    _simulation = new ModelSimulation(this);
    // 1:n associations
    _events = new List<Event*>(); /// The future events list must be chronologicaly sorted
    //_events->setSortFunc(&EventCompare); // It works too
    _events->setSortFunc([](const Event* a, const Event * b) {
	return a->getTime() < b->getTime(); /// Events are sorted chronologically
    });
    // for process analyser
    _responses = new List<SimulationResponse*>();
    _controls = new List<SimulationControl*>();
    // insert controls
    _controls->insert(new SimulationControl("Model Info", "Number of Replications",
	    DefineGetterMember<ModelInfo>(this->_modelInfo, &ModelInfo::getNumberOfReplications),
	    DefineSetterMember<ModelInfo>(this->_modelInfo, &ModelInfo::setNumberOfReplications))
	    );
    _controls->insert(new SimulationControl("Model Info", "Replication Length",
	    DefineGetterMember<ModelInfo>(this->_modelInfo, &ModelInfo::getReplicationLength),
	    DefineSetterMember<ModelInfo>(this->_modelInfo, &ModelInfo::setReplicationLength))
	    );
    _controls->insert(new SimulationControl("Model Info", "Warmup Period",
	    DefineGetterMember<ModelInfo>(this->_modelInfo, &ModelInfo::getWarmUpPeriod),
	    DefineSetterMember<ModelInfo>(this->_modelInfo, &ModelInfo::setWarmUpPeriod))
	    );
}

Model::Model(const Model& orig) {
}

Model::~Model() {
}

void Model::sendEntityToComponent(Entity* entity, Connection* connection, double timeDelay){
    this->sendEntityToComponent(entity, connection->first, timeDelay, connection->second);
}

void Model::sendEntityToComponent(Entity* entity, ModelComponent* component, double timeDelay, unsigned int componentInputNumber) {
    /* TODO -: event onEntityMove */
    if (timeDelay > 0) {
	// schedule to send it
	Event* newEvent = new Event(this->getSimulation()->getSimulatedTime() + timeDelay, entity, component, componentInputNumber);
	this->getEvents()->insert(newEvent);
    } else {
	// send it now
	/* TODO -: supposed not to be a queue associated to a component */
	Util::DecIndent();
	ModelComponent::Execute(entity, component, componentInputNumber);
	Util::IncIndent();
    }
}

bool Model::saveModel(std::string filename) {
    return this->_modelPersistence->save(filename);
}

bool Model::loadModel(std::string filename) {
    //this->clear(); // clear the model before loading on an existing model
    return this->_modelPersistence->load(filename);
}

double Model::parseExpression(const std::string expression) {
    try{
    return _parser->parse(expression);
    }catch(...){
	return 0.0; //TODO HOW SAY THERE WAS AN ERROR?
    }
}

bool Model::checkExpression(const std::string expression, const std::string expressionName, std::string* errorMessage) {
    bool result;
    parseExpression(expression, &result, errorMessage);
    if (!result) {
	std::string msg = "Expression \"" + expression + "\" for '" + expressionName + "' is incorrect. ";
	errorMessage->append(msg);
    }
    return result;
}

double Model::parseExpression(const std::string expression, bool* success, std::string* errorMessage) {
    double value = _parser->parse(expression, success, errorMessage);
    return value;
}

void Model::show() {
    getTraceManager()->trace(Util::TraceLevel::report, "Simulation Model:");
    Util::IncIndent();
    {
	getTraceManager()->trace(Util::TraceLevel::report, "Information:");
	Util::IncIndent();
	getTraceManager()->trace(Util::TraceLevel::report, this->getInfos()->show());
	Util::DecIndent();
	_showComponents();
	_showElements();
	_showSimulationControls();
	_showSimulationResponses();
    }
    Util::DecIndent();
    getTraceManager()->trace(Util::TraceLevel::report, "End of Simulation Model");
}

void Model::_showElements() const {
    getTraceManager()->trace(Util::TraceLevel::report, "Elements:");
    Util::IncIndent();
    {
	std::string elementType;
	bool result;
	ModelElement* element;
	std::string* errorMessage = new std::string();
	std::list<std::string>* elementTypes = getElementManager()->getElementTypenames();
	for (std::list<std::string>::iterator typeIt = elementTypes->begin(); typeIt != elementTypes->end(); typeIt++) {
	    elementType = (*typeIt);
	    List<ModelElement*>* elements = getElementManager()->getElements(elementType);
	    getTraceManager()->trace(Util::TraceLevel::report, elementType + ":");
	    Util::IncIndent();
	    {
		for (std::list<ModelElement*>::iterator it = elements->getList()->begin(); it != elements->getList()->end(); it++) {
		    element = (*it);
		    getTraceManager()->trace(Util::TraceLevel::report, element->show());
		}
	    }
	    Util::DecIndent();
	}
    }
    Util::DecIndent();
}

void Model::_showComponents() const {
    getTraceManager()->trace(Util::TraceLevel::report, "Components:");
    Util::IncIndent();
    for (std::list<ModelComponent*>::iterator it = getComponentManager()->begin(); it != getComponentManager()->end(); it++) {
	getTraceManager()->trace(Util::TraceLevel::report, (*it)->show()); ////
    }
    Util::DecIndent();
}

void Model::_showSimulationControls() const {
    getTraceManager()->trace(Util::TraceLevel::report, "Simulation Controls:");
    Util::IncIndent();
    for (std::list<SimulationControl*>::iterator it = _controls->getList()->begin(); it != _controls->getList()->end(); it++) {
	getTraceManager()->trace(Util::TraceLevel::report, (*it)->show()); ////
    }
    Util::DecIndent();
}

void Model::_showSimulationResponses() const {
    getTraceManager()->trace(Util::TraceLevel::report, "Simulation Responses:");
    Util::IncIndent();
    for (std::list<SimulationResponse*>::iterator it = _responses->getList()->begin(); it != _responses->getList()->end(); it++) {
	getTraceManager()->trace(Util::TraceLevel::report, (*it)->show()); ////
    }
    Util::DecIndent();
}

void Model::clear() {
    this->_componentManager->clear();
    this->_elementManager->clear();
    //Util::ResetAllIds(); // TODO: To implement
}

bool Model::checkModel() {
    getTraceManager()->trace(Util::TraceLevel::simulation, "Checking model consistency");
    Util::IncIndent();
    bool res = this->_modelChecker->checkAll();
    Util::DecIndent();
    if (res) {
	getTraceManager()->trace(Util::TraceLevel::simulation, "End of Model checking: Success");
    } else {
	//std::exception e = new std::exception();
	//getTrace()->traceError() ;
	getTraceManager()->trace(Util::TraceLevel::errors, "End of Model checking: Failed");
    }
    return res;
}

//bool Model::verifySymbol(std::string componentName, std::string expressionName, std::string expression, std::string expressionResult, bool mandatory) {
//    return this->_modelChecker->verifySymbol(componentName, expressionName, expression, expressionResult, mandatory);
//}

void Model::removeEntity(Entity* entity, bool collectStatistics) {
    /* TODO -: event onEntityRemove */
    std::string entId = std::to_string(entity->getEntityNumber());
    this->getElementManager()->remove(Util::TypeOf<Entity>(), entity);
    getTraceManager()->trace(Util::TraceLevel::blockInternal, "Entity " + entId + " was removed from the system");
}

List<Event*>* Model::getEvents() const {
    return _events;
}

void Model::setTraceManager(TraceManager* _traceManager) {
    this->_traceManager = _traceManager;
}

TraceManager* Model::getTraceManager() const {
    return _traceManager;
}

ComponentManager* Model::getComponentManager() const {
    return _componentManager;
}

List<SimulationControl*>* Model::getControls() const {
    return _controls;
}

List<SimulationResponse*>* Model::getResponses() const {
    return _responses;
}

OnEventManager* Model::getOnEventManager() const {
    return _eventManager;
}

ElementManager* Model::getElementManager() const {
    return _elementManager;
}

ModelInfo* Model::getInfos() const {
    return _modelInfo;
}

Simulator* Model::getParentSimulator() const {
    return _parentSimulator;
}

ModelSimulation* Model::getSimulation() const {
    return _simulation;
}



//List<Entity*>* Model::getEntities() const {
//	List<Entity*>* ents = (List<Entity*>*)(getElementManager()->getElements(Util::TypeOf<Entity>())); // static_cast ??
//	return ents;
//}

Util::identitifcation Model::getId() const {
    return _id;
}

//List<ModelComponent*>* Model::getComponents() const {
//    return _components;
//}


