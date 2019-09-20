/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReadWrite.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:06
 */

#include "ReadWrite.h"

#include "Model.h"

ReadWrite::ReadWrite(Model* model) : ModelComponent(model, Util::TypeOf<ReadWrite>()) {
}

ReadWrite::ReadWrite(const ReadWrite& orig) : ModelComponent(orig) {
}

ReadWrite::~ReadWrite() {
}

std::string ReadWrite::show() {
    return ModelComponent::show() + "";
}

ModelComponent* ReadWrite::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    ReadWrite* newComponent = new ReadWrite(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void ReadWrite::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool ReadWrite::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void ReadWrite::_initBetweenReplications() {
}

std::map<std::string, std::string>* ReadWrite::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool ReadWrite::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* ReadWrite::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<ReadWrite>(), &ReadWrite::LoadInstance);
    // ...
    return info;
}


