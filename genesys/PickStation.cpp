/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PickStation.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:08
 */

#include "PickStation.h"

#include "Model.h"

PickStation::PickStation(Model* model) : ModelComponent(model, Util::TypeOf<PickStation>()) {
}

PickStation::PickStation(const PickStation& orig) : ModelComponent(orig) {
}

PickStation::~PickStation() {
}

std::string PickStation::show() {
    return ModelComponent::show() + "";
}

ModelComponent* PickStation::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    PickStation* newComponent = new PickStation(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void PickStation::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool PickStation::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void PickStation::_initBetweenReplications() {
}

std::map<std::string, std::string>* PickStation::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool PickStation::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* PickStation::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<PickStation>(), &PickStation::LoadInstance);
    // ...
    return info;
}

