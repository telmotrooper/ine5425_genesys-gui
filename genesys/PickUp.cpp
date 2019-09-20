/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PickUp.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:15
 */

#include "PickUp.h"

#include "Model.h"

PickUp::PickUp(Model* model) : ModelComponent(model, Util::TypeOf<PickUp>()) {
}

PickUp::PickUp(const PickUp& orig) : ModelComponent(orig) {
}

PickUp::~PickUp() {
}

std::string PickUp::show() {
    return ModelComponent::show() + "";
}

ModelComponent* PickUp::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    PickUp* newComponent = new PickUp(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void PickUp::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool PickUp::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void PickUp::_initBetweenReplications() {
}

std::map<std::string, std::string>* PickUp::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool PickUp::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* PickUp::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<PickUp>(), &PickUp::LoadInstance);
    // ...
    return info;
}


