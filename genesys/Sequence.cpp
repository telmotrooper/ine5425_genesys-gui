/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sequence.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:12
 */

#include "Sequence.h"
#include "Attribute.h"


Sequence::Sequence(ElementManager* elems) : ModelElement(Util::TypeOf<Sequence>()) {
    _elems = elems;
}

Sequence::Sequence(ElementManager* elems, std::string name) : ModelElement(Util::TypeOf<Sequence>()) {
    _name = name;
    _elems = elems;
}

Sequence::Sequence(const Sequence& orig) : ModelElement(orig) {
}

Sequence::~Sequence() {
}

std::string Sequence::show() {
    std::string msg = ModelElement::show();
    return msg;
}


PluginInformation* Sequence::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<Sequence>(), &Sequence::LoadInstance);
    return info;
}

ModelElement* Sequence::LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields) {
    Sequence* newElement = new Sequence(elems);
    try {
	newElement->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newElement;
}

bool Sequence::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelElement::_loadInstance(fields);
    if (res) {
	try {
	} catch (...) {
	}
    }
    return res;
}

std::map<std::string, std::string>* Sequence::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelElement::_saveInstance(); //Util::TypeOf<Sequence>());
    return fields;
}

bool Sequence::_check(std::string* errorMessage) {
    /* include attributes needed */
    std::vector<std::string> neededNames = {"Entity.Sequence"};
    std::string neededName;
    for (int i = 0; i < neededNames.size(); i++) {
	neededName = neededNames[i];
	if (_elems->getElement(Util::TypeOf<Attribute>(), neededName) == nullptr) {
	    Attribute* attr1 = new Attribute(neededName);
	    _elems->insert(Util::TypeOf<Attribute>(), attr1);
	}
    }
    //
    return true;
}

