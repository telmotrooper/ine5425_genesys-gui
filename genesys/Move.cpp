/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Move.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:17
 */

#include "Move.h"

#include "Model.h"

Move::Move(Model* model) : ModelComponent(model, Util::TypeOf<Move>()) {
}

Move::Move(const Move& orig) : ModelComponent(orig) {
}

Move::~Move() {
}

std::string Move::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Move::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Move* newComponent = new Move(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Move::_execute(Entity* entity) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Move::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Move::_initBetweenReplications() {
}

std::map<std::string, std::string>* Move::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Move::_check(std::string* errorMessage) {
    bool resultAll = true;
    //...
    return resultAll;
}

PluginInformation* Move::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Move>(), &Move::LoadInstance);
    // ...
    return info;
}


