/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Remove.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:20
 */

#include "Remove.h"
#include "Model.h"

Remove::Remove(Model* model) : ModelComponent(model, Util::TypeOf<Remove>()) {
}

Remove::Remove(const Remove& orig) : ModelComponent(orig) {
}

Remove::~Remove() {
}

std::string Remove::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Remove::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Remove* newComponent = new Remove(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Remove::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Remove::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Remove::_initBetweenReplications() {
}

std::map<std::string, std::string>* Remove::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Remove::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Remove::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Remove>(), &Remove::LoadInstance);
    // ...
    return info;
}


