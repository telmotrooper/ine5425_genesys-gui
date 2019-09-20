/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimulationControl.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 10 de Outubro de 2018, 18:01
 */

#include "SimulationControl.h"

SimulationControl::SimulationControl(std::string type, std::string name, GetterMember getterMember, SetterMember setterMember) : SimulationResponse(type, name, getterMember) {
    this->_type = type;
    this->_setMemberFunction = setterMember;
}

SimulationControl::SimulationControl(const SimulationControl& orig) : SimulationResponse(orig) {
}

SimulationControl::~SimulationControl() {
}

std::string SimulationControl::show() {
    return "name="+this->_name+", type="+this->_type;
}

void SimulationControl::setValue(double value) {
    this->_setMemberFunction(value);
}

