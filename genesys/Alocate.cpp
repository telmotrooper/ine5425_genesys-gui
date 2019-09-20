/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Alocate.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:16
 */

#include "Alocate.h"

#include "Model.h"

Alocate::Alocate(Model* model) : ModelComponent(model, Util::TypeOf<Alocate>()) {
}

Alocate::Alocate(const Alocate& orig) : ModelComponent(orig) {
}

Alocate::~Alocate() {
}

std::string Alocate::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Alocate::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Alocate* newComponent = new Alocate(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Alocate::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Alocate::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Alocate::_initBetweenReplications() {
}

std::map<std::string, std::string>* Alocate::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Alocate::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Alocate::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Alocate>(), &Alocate::LoadInstance);
    // ...
    return info;
}


