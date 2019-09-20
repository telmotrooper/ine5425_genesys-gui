/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Signal.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:20
 */

#include "Signal.h"

#include "Model.h"

Signal::Signal(Model* model) : ModelComponent(model, Util::TypeOf<Signal>()) {
}

Signal::Signal(const Signal& orig) : ModelComponent(orig) {
}

Signal::~Signal() {
}

std::string Signal::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Signal::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Signal* newComponent = new Signal(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Signal::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Signal::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Signal::_initBetweenReplications() {
}

std::map<std::string, std::string>* Signal::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Signal::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Signal::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Signal>(), &Signal::LoadInstance);
    // ...
    return info;
}


