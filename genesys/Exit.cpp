/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Exit.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:15
 */

#include "Exit.h"

#include "Model.h"

Exit::Exit(Model* model) : ModelComponent(model, Util::TypeOf<Exit>()) {
}

Exit::Exit(const Exit& orig) : ModelComponent(orig) {
}

Exit::~Exit() {
}

std::string Exit::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Exit::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Exit* newComponent = new Exit(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Exit::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Exit::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Exit::_initBetweenReplications() {
}

std::map<std::string, std::string>* Exit::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Exit::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Exit::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Exit>(), &Exit::LoadInstance);
    // ...
    return info;
}


