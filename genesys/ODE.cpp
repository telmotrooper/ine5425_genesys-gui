/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ODE.cpp
 * Author: rlcancian
 * 
 * Created on 13 de Junho de 2019, 19:12
 */

#include "ODE.h"
#include "Model.h"

ODE::ODE(ElementManager* elems) : ModelElement(Util::TypeOf<ODE>()) {
    _elems = elems;
}

ODE::ODE(const ODE& orig) : ModelElement(orig) {
}

ODE::~ODE() {
}

std::string ODE::show() {
    std::string txt =  ModelElement::show();
    unsigned short i=0;
    for (std::list<ODEfunction*>::iterator it = _ODEfunctions->getList()->begin(); it != _ODEfunctions->getList()->end(); it++) {
	txt += ",func["+std::to_string(i)+"]=\""+(*it)->expression+"\",(func["+std::to_string(i)+"]["+std::to_string((*it)->initialPoint)+"]="+std::to_string((*it)->initialValue)+")";
    }
    return txt;
}

double ODE::solve() {
    double expressionValue, k1, k2, k3, k4, w;
    expressionValue  = _elems->getParentModel()->parseExpression(this->getODEfunctions()->front()->expression );
    k1 = _stepH*expressionValue;
}


void ODE::setStepH(double _h) {
    this->_stepH = _h;
}

double ODE::getStepH() const {
    return _stepH;
}

void ODE::setEndTime(double _endTime) {
    this->_endTime = _endTime;
}

double ODE::getEndTime() const {
    return _endTime;
}

List<ODEfunction*>* ODE::getODEfunctions() const {
    return _ODEfunctions;
}

PluginInformation* ODE::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<ODE>(), &ODE::LoadInstance); return info;
}

ModelElement* ODE::LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields) {
}

bool ODE::_loadInstance(std::map<std::string, std::string>* fields) {
}

std::map<std::string, std::string>* ODE::_saveInstance() {
}

bool ODE::_check(std::string* errorMessage) {
    bool result = true;
    unsigned short i=0;
    ODEfunction* func;
    for (std::list<ODEfunction*>::iterator it = _ODEfunctions->getList()->begin(); it != _ODEfunctions->getList()->end(); it++) {
	func = (*it);
	result &= _elems->getParentModel()->checkExpression(func->expression, "expression["+std::to_string(i++)+"]", errorMessage);
    }
    return result;
}
