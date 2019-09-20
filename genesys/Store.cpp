/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Store.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:07
 */

#include "Store.h"
#include "Model.h"

Store::Store(Model* model) : ModelComponent(model, Util::TypeOf<Store>()) {
}

Store::Store(const Store& orig) : ModelComponent(orig) {
}

Store::~Store() {
}

std::string Store::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Store::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Store* newComponent = new Store(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Store::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Store::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Store::_initBetweenReplications() {
}

std::map<std::string, std::string>* Store::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Store::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Store::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Store>(), &Store::LoadInstance);
    // ...
    return info;
}


