/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hold.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:20
 */

#include "Hold.h"
#include "Model.h"

Hold::Hold(Model* model) : ModelComponent(model, Util::TypeOf<Hold>()) {
}

Hold::Hold(const Hold& orig) : ModelComponent(orig) {
}

Hold::~Hold() {
}

std::string Hold::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Hold::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Hold* newComponent = new Hold(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Hold::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Hold::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Hold::_initBetweenReplications() {
}

std::map<std::string, std::string>* Hold::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Hold::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Hold::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Hold>(), &Hold::LoadInstance);
    // ...
    return info;
}

