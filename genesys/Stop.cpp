/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stop.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:15
 */

#include "Stop.h"

#include "Model.h"

Stop::Stop(Model* model) : ModelComponent(model, Util::TypeOf<Stop>()) {
}

Stop::Stop(const Stop& orig) : ModelComponent(orig) {
}

Stop::~Stop() {
}

std::string Stop::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Stop::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Stop* newComponent = new Stop(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Stop::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Stop::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Stop::_initBetweenReplications() {
}

std::map<std::string, std::string>* Stop::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Stop::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Stop::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Stop>(), &Stop::LoadInstance);
    // ...
    return info;
}


