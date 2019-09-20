/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Match.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:14
 */

#include "Match.h"

#include "Model.h"

Match::Match(Model* model) : ModelComponent(model, Util::TypeOf<Match>()) {
}

Match::Match(const Match& orig) : ModelComponent(orig) {
}

Match::~Match() {
}

std::string Match::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Match::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Match* newComponent = new Match(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Match::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Match::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Match::_initBetweenReplications() {
}

std::map<std::string, std::string>* Match::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Match::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Match::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Match>(), &Match::LoadInstance);
    // ...
    return info;
}

