/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Variable.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 4 de Setembro de 2018, 18:28
 */

#include "Variable.h"
#include "Plugin.h"

Variable::Variable() : ModelElement(Util::TypeOf<Variable>()) {
}

Variable::Variable(std::string name) : ModelElement(Util::TypeOf<Variable>()) {
    _name = name;
}

Variable::Variable(const Variable& orig) : ModelElement(orig) {
}

Variable::~Variable() {
}

std::string Variable::show() {
    return ModelElement::show(); // @TODO: include values
}

PluginInformation* Variable::GetPluginInformation(){
    PluginInformation* info = new PluginInformation(Util::TypeOf<Variable>(), &Variable::LoadInstance); return info;
}

double Variable::getValue() {
    return getValue("");
}

double Variable::getValue(std::string index) {
    std::map<std::string, double>::iterator it = _values->find(index);
    if (it == _values->end()) {
	return 0.0; // index does not exist. Assuming sparse matrix, it's zero. 
    } else {
	return it->second;
    }
}

void Variable::setValue(double value) {
    setValue("", value);
}

void Variable::setValue(std::string index, double value) {
    std::map<std::string, double>::iterator it = _values->find(index);
    if (it == _values->end()) {
	// index does not exist. Create it.
	_values->insert(std::pair<std::string, double>(index, value));
    } else {
	it->second = value;
    }
}

ModelElement* Variable::LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields) {
    Variable* newElement = new Variable();
    try {
	newElement->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newElement;
}

bool Variable::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res= ModelElement::_loadInstance(fields);
    if (res) {
	this->_numCols=std::stoi((*(fields->find("numCols"))).second);
	this->_numRows=std::stoi((*(fields->find("numRows"))).second);
	unsigned int nv = std::stoi((*(fields->find("numValues"))).second);
	std::string pos;
	double value;
	for (unsigned int i=0; i<nv; i++){
	    pos = ((*(fields->find("pos"+std::to_string(i)))).second);
	    value=std::stod((*(fields->find("value"+std::to_string(i)))).second);
	    this->_values->emplace(pos,value);
	}
    }
    return res;
}

std::map<std::string, std::string>* Variable::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelElement::_saveInstance(); //Util::TypeOf<Variable>());
    fields->emplace("numCols" , std::to_string(this->_numCols));
    fields->emplace("numRows" , std::to_string(this->_numRows));
    fields->emplace("numValues", std::to_string(this->_values->size()));
    unsigned int i=0;
    for (std::map<std::string, double>::iterator it = this->_values->begin(); it != _values->end(); it++) {
	fields->emplace("pos"+std::to_string(i) , (*it).first);
	fields->emplace("value"+std::to_string(i) , std::to_string((*it).second));
	i++;
    }
    return fields;
}

bool Variable::_check(std::string* errorMessage) {
    return true;
}
