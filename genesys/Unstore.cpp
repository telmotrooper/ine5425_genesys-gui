/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Unstore.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:08
 */

#include "Unstore.h"
#include "Model.h"

Unstore::Unstore(Model* model) : ModelComponent(model, Util::TypeOf<Unstore>()) {
}

Unstore::Unstore(const Unstore& orig) : ModelComponent(orig) {
}

Unstore::~Unstore() {
}

std::string Unstore::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Unstore::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Unstore* newComponent = new Unstore(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Unstore::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Unstore::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Unstore::_initBetweenReplications() {
}

std::map<std::string, std::string>* Unstore::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Unstore::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Unstore::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Unstore>(), &Unstore::LoadInstance);
    // ...
    return info;
}


