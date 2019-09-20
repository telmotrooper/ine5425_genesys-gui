/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Batch.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:14
 */

#include "Batch.h"

#include "Model.h"

Batch::Batch(Model* model) : ModelComponent(model, Util::TypeOf<Batch>()) {
}

Batch::Batch(const Batch& orig) : ModelComponent(orig) {
}

Batch::~Batch() {
}

std::string Batch::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Batch::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Batch* newComponent = new Batch(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Batch::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Batch::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Batch::_initBetweenReplications() {
}

std::map<std::string, std::string>* Batch::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Batch::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Batch::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Batch>(), &Batch::LoadInstance);
    // ...
    return info;
}


