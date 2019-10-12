/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.cpp
 * Author: rlcancian
 * 
 * Created on 20 de Fileembro de 2019, 20:07
 */

#include "File.h"


File::File(ElementManager* elems) : ModelElement(Util::TypeOf<File>()) {
    _elems = elems;
}

File::File(ElementManager* elems, std::string name) : ModelElement(Util::TypeOf<File>()) {
    _name = name;
    _elems = elems;
}

File::File(const File& orig) : ModelElement(orig) {
}

File::~File() {
}

std::string File::show() {
    return ModelElement::show() +
	    "";
}

PluginInformation* File::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<File>(), &File::LoadInstance); 
    return info;
}

ModelElement* File::LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields) {
    File* newElement = new File(elems);
    try {
	newElement->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newElement;
}

bool File::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelElement::_loadInstance(fields);
    if (res) {
	try {
	    //this->_attributeName = (*fields->find("attributeName")).second;
	    //this->_orderRule = static_cast<OrderRule> (std::stoi((*fields->find("orderRule")).second));
	} catch (...) {
	}
    }
    return res;
}

std::map<std::string, std::string>* File::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelElement::_saveInstance(); //Util::TypeOf<File>());
    //fields->emplace("orderRule", std::to_string(static_cast<int> (this->_orderRule)));
    //fields->emplace("attributeName", this->_attributeName);
    return fields;
}

bool File::_check(std::string* errorMessage) {
    bool resultAll = true;
    // resultAll |= ...
    return resultAll;
}

ParserChangesInformation* File::_getParserChangesInformation() {
    ParserChangesInformation* changes = new ParserChangesInformation();
    //changes->getProductionToAdd()->insert(...);
    //changes->getTokensToAdd()->insert(...);
    return changes;
}

