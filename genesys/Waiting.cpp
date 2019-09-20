/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Waiting.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 29 de Agosto de 2018, 17:09
 */

#include "Waiting.h"

Waiting::Waiting(Entity* entity, ModelComponent* component, double timeStartedWaiting) {
    _entity = entity;
    _component = component;
    _timeStartedWaiting = timeStartedWaiting;
}

Waiting::Waiting(const Waiting& orig) {
}

Waiting::~Waiting() {
}

double Waiting::getTimeStartedWaiting() const {
    return _timeStartedWaiting;
}

std::string Waiting::show() {
    return //ModelElement::show()+
    ",entity=" + std::to_string(_entity->getId()) +
	    ",component=\"" + _component->getName() + "\"" +
	    ",timeStatedWaiting=" + std::to_string(_timeStartedWaiting);
}

ModelComponent* Waiting::getComponent() const {
    return _component;
}

Entity* Waiting::getEntity() const {
    return _entity;
}