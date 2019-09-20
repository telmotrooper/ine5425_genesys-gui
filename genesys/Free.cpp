/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Free.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:16
 */

#include "Free.h"

#include "Model.h"

Free::Free(Model* model) : ModelComponent(model, Util::TypeOf<Free>()) {
}

Free::Free(const Free& orig) : ModelComponent(orig) {
}

Free::~Free() {
}

std::string Free::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Free::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Free* newComponent = new Free(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Free::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Free::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Free::_initBetweenReplications() {
}

std::map<std::string, std::string>* Free::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Free::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Free::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Free>(), &Free::LoadInstance);
    // ...
    return info;
}


