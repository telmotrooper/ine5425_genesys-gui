/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Element.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 21 de Junho de 2018, 15:56
 */

#include "ModelComponent.h"
#include "Model.h"

ModelComponent::ModelComponent(Model* model, std::string componentTypename) : ModelElement(componentTypename) {
    _model = model;
}

ModelComponent::ModelComponent(const ModelComponent& orig) : ModelElement(orig) {
}

ModelComponent::~ModelComponent() {
}

void ModelComponent::Execute(Entity* entity, ModelComponent* component, unsigned int inputNumber) {
    std::string msg = "Entity " + std::to_string(entity->getEntityNumber()) + " has arrived at component \"" + component->_name + "\"";
    //TODO: How can I know the number of inputs?
    if (inputNumber > 0)
	msg += " by input " + std::to_string(inputNumber);
    component->_model->getTraceManager()->trace(Util::TraceLevel::blockArrival, msg);
    Util::IncIndent();
    try {
	component->_execute(entity);
    } catch (const std::exception& e) {
	component->_model->getTraceManager()->traceError(e, "Error executing component " + component->show());
    }
    Util::DecIndent();
}

void ModelComponent::InitBetweenReplications(ModelComponent* component) {
    //component->_model->getTraceManager()->trace(Util::TraceLevel::blockArrival, "Writing component \"" + component->_name + "\""); //std::to_string(component->_id));
    try {
	component->_initBetweenReplications();
    } catch (const std::exception& e) {
	component->_model->getTraceManager()->traceError(e, "Error initing component " + component->show());
    };
}

std::map<std::string, std::string>* ModelComponent::SaveInstance(ModelComponent* component) {
    component->_model->getTraceManager()->trace(Util::TraceLevel::blockArrival, "Writing component \"" + component->_name + "\""); //std::to_string(component->_id));
    std::map<std::string, std::string>* fields = new std::map<std::string, std::string>();
    try {
	fields = component->_saveInstance();
    } catch (const std::exception& e) {
	component->_model->getTraceManager()->traceError(e, "Error executing component " + component->show());
    }
    return fields;
}

bool ModelComponent::Check(ModelComponent* component) {
    component->_model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, "Checking " + component->_typename + ": " + component->_name); //std::to_string(component->_id));
    bool res = false;
    std::string* errorMessage = new std::string();
    Util::IncIndent();
    {
	try {
	    res = component->_check(errorMessage);
	    if (!res) {
		component->_model->getTraceManager()->trace(Util::TraceLevel::errors, "Error: Checking has failed with message '" + *errorMessage + "'");
	    }
	} catch (const std::exception& e) {
	    component->_model->getTraceManager()->traceError(e, "Error verifying component " + component->show());
	}
    }
    Util::DecIndent();
    return res;
}

ConnectionManager* ModelComponent::getNextComponents() const {
    return _nextComponents;
}

std::string ModelComponent::show() {
    return ModelElement::show(); // "{id=" + std::to_string(this->_id) + ",name=\""+this->_name + "\"}"; // , nextComponents[]=(" + _nextComponents->show() + ")}";
}

bool ModelComponent::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelElement::_loadInstance(fields);
    if (res) {
	// Now it shoould load nextComponents. The problem is that the nextCOmponent may not be loaded yet.
	// So, what can be done is to temporarily load the ID of the nextComponents, and to wait until all the components have been loaded to update nextComponents based on the temporarilyIDs now being loaded
	unsigned short nextSize = std::stoi((*fields->find("nextSize")).second);
	this->_tempLoadNextComponentsIDs = new List<Util::identitifcation>();
	for (unsigned short i = 0; i < nextSize; i++) {
	    Util::identitifcation nextId = std::stoi((*fields->find("nextId" + std::to_string(i))).second);
	    this->_tempLoadNextComponentsIDs->insert(nextId);
	}
    }
    return res;
}

std::map<std::string, std::string>* ModelComponent::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelElement::_saveInstance();
    fields->emplace("nextSize", std::to_string(this->_nextComponents->size()));
    unsigned short i = 0;
    for (std::list<Connection*>::iterator it = _nextComponents->getList()->begin(); it != _nextComponents->getList()->end(); it++) {
	fields->emplace("nextId" + std::to_string(i), std::to_string((*it)->first->_id));
	i++;
    }
    return fields;
}

/*
std::list<std::map<std::string,std::string>*>* ModelComponent::_saveInstance(std::string type) {
    std::list<std::map<std::string,std::string>*>* fields = ModelComponent::_saveInstance();
    fields->push_back(std::to_string(this->_nextComponents->size()));
    for (std::list<ModelComponent*>::iterator it=_nextgetComponentManager()->begin(); it!=_nextgetComponentManager()->end(); it++){
	fields->push_back((*it)->_name);
    }
    return fields;
}
 */