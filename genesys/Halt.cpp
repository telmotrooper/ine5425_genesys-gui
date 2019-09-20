/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Halt.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:17
 */

#include "Halt.h"
#include "Model.h"

Halt::Halt(Model* model) : ModelComponent(model, Util::TypeOf<Halt>()) {
}

Halt::Halt(const Halt& orig) : ModelComponent(orig) {
}

Halt::~Halt() {
}

std::string Halt::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Halt::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Halt* newComponent = new Halt(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Halt::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Halt::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Halt::_initBetweenReplications() {
}

std::map<std::string, std::string>* Halt::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Halt::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Halt::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Halt>(), &Halt::LoadInstance);
    // ...
    return info;
}

