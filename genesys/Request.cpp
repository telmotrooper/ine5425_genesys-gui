/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Request.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:17
 */

#include "Request.h"
#include "Model.h"

Request::Request(Model* model) : ModelComponent(model, Util::TypeOf<Request>()) {
}

Request::Request(const Request& orig) : ModelComponent(orig) {
}

Request::~Request() {
}

std::string Request::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Request::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Request* newComponent = new Request(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Request::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Request::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Request::_initBetweenReplications() {
}

std::map<std::string, std::string>* Request::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Request::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Request::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Request>(), &Request::LoadInstance);
    // ...
    return info;
}


