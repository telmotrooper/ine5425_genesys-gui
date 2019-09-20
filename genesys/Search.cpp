/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Search.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:20
 */

#include "Search.h"
#include "Model.h"

Search::Search(Model* model) : ModelComponent(model, Util::TypeOf<Search>()) {
}

Search::Search(const Search& orig) : ModelComponent(orig) {
}

Search::~Search() {
}

std::string Search::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Search::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Search* newComponent = new Search(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Search::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Search::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Search::_initBetweenReplications() {
}

std::map<std::string, std::string>* Search::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Search::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Search::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Search>(), &Search::LoadInstance);
    // ...
    return info;
}


