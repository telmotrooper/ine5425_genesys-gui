/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Formula.cpp
 * Author: rlcancian
 * 
 * Created on 20 de Junho de 2019, 00:56
 */

#include "Formula.h"
#include <iostream>
#include "ElementManager.h"
#include "Model.h"
#include "Traits.h"

Formula::Formula(ElementManager* elements) : ModelElement(Util::TypeOf<Formula>()) {
    _elements = elements;
    _myPrivateParser = new Traits<Parser_if>::Implementation(elements->getParentModel());
}

void Formula::setFormulaExpression(std::string _formulaExpression) {
    this->_formulaExpression = _formulaExpression;
}

std::string Formula::getFormulaExpression() const {
    return _formulaExpression;
}

double Formula::getValue() const {
    double value = -99.9;//_myPrivateParser->parse(_formulaExpression);
    return value;
}

Formula::Formula(const Formula& orig) : ModelElement(orig) {
}

Formula::~Formula() {
}

std::string Formula::show() {
    return ModelElement::show()+
	    ",formulaExpression=\""+this->_formulaExpression+"\"";
}

PluginInformation* Formula::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<Formula>(), &Formula::LoadInstance); return info;
}

ModelElement* Formula::LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields) {
}

bool Formula::_loadInstance(std::map<std::string, std::string>* fields) {
}

std::map<std::string, std::string>* Formula::_saveInstance() {
}

bool Formula::_check(std::string* errorMessage) {
    std::string errorMsg="";
    bool res  = _elements->getParentModel()->checkExpression(this->_formulaExpression,"formula expression", &errorMsg);
    return res;
}
