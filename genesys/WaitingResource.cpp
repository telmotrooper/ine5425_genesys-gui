/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WaitingResource.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 29 de Agosto de 2018, 17:10
 */

#include "WaitingResource.h"

WaitingResource::WaitingResource(Entity* entity, ModelComponent* component, double timeStartedWaiting, unsigned int quantity) : Waiting(entity, component, timeStartedWaiting) {
    _quantity = quantity;
}

WaitingResource::WaitingResource(const WaitingResource& orig) : Waiting(orig) {
}

WaitingResource::~WaitingResource() {
}

std::string WaitingResource::show() {
    return Waiting::show() +
	    ",quantity=" + std::to_string(this->_quantity);
}

unsigned int WaitingResource::getQuantity() const {
    return _quantity;
}



