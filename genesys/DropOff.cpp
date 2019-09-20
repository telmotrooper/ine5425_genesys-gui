/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DropOff.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:15
 */

#include "DropOff.h"
#include "Model.h"

DropOff::DropOff(Model* model) : ModelComponent(model, Util::TypeOf<DropOff>()) {
}

DropOff::DropOff(const DropOff& orig) : ModelComponent(orig) {
}

DropOff::~DropOff() {
}

std::string DropOff::show() {
    return ModelComponent::show() + "";
}

ModelComponent* DropOff::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    DropOff* newComponent = new DropOff(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void DropOff::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool DropOff::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void DropOff::_initBetweenReplications() {
}

std::map<std::string, std::string>* DropOff::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool DropOff::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* DropOff::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<DropOff>(), &DropOff::LoadInstance);
    // ...
    return info;
}

