/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModelElement.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 21 de Junho de 2018, 19:40
 */

//#include <typeinfo>
#include <iostream>   
#include "ModelElement.h"

ModelElement::ModelElement(std::string thistypename) {
    // ID is UNIQUE FOR EVERY ELEMENT AND COMPONENT in the entire simulator
    _id = Util::GenerateNewId(); //GenerateNewIdOfType(thistypename);
    _name = thistypename + " " + std::to_string(Util::GenerateNewIdOfType(thistypename)); //std::to_string(_id);
    _typename = thistypename;
}

ModelElement::ModelElement(const ModelElement& orig) {
}

ModelElement::~ModelElement() {
}

bool ModelElement::_loadInstance(std::map<std::string, std::string>* fields) {
    //this->_id = std::stoi((*fields->find("id")).second);
    bool res = true;
    std::map<std::string, std::string>::iterator it;
    // WE DO NOT LOAD ID!!! IDs ARE UNIQUELLY GENERATED WHEN OBJECTS ARE CREATED
    //it = fields->find("id");
    //it != fields->end() ? this->_id = std::stoi((*it).second) : res = false;
    it = fields->find("name");
    if (it != fields->end()) {
	this->_name = (*it).second;
    } else
	res = false;
    //it != fields->end() ? this->_name = (*it).second : res = false;
    return res;
}

std::map<std::string, std::string>* ModelElement::_saveInstance() {
    std::map<std::string, std::string>* fields = new std::map<std::string, std::string>();
    fields->emplace("typename", this->_typename);
    fields->emplace("id", std::to_string(this->_id));
    fields->emplace("name", this->_name);
    return fields;
}

bool ModelElement::_check(std::string* errorMessage) {
    return true; // if there is no ovveride, return true
}

ParserChangesInformation* ModelElement::_getParserChangesInformation() {
    return new ParserChangesInformation(); // if there is no override, return no changes
}

/*
std::list<std::map<std::string,std::string>*>* ModelElement::_saveInstance(std::string type) {
    std::list<std::map<std::string,std::string>*>* fields = ModelElement::_saveInstance();
    fields->push_back(type);
    return fields;
}
 */

std::string ModelElement::show() {
    return "id=" + std::to_string(_id) + ",name=\"" + _name + "\"";
}


Util::identitifcation ModelElement::getId() const {
    return _id;
}

void ModelElement::setName(std::string _name) {
    this->_name = _name;
}

std::string ModelElement::getName() const {
    return _name;
}

std::string ModelElement::getTypename() const {
    return _typename;
}

//std::list<std::map<std::string,std::string>*>* ModelElement::_saveInstance() { /* TODO: REMOVE - IS PURE VIRTUAL  TEMP */
//	std::list<std::map<std::string,std::string>*>* fiels = new std::map<std::string,std::string>();
//	return fields;
//}

ModelElement* ModelElement::LoadInstance(std::map<std::string, std::string>* fields) {
    ModelElement* newElement = new ModelElement("ModelElement");
    try {
	newElement->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newElement;
}

std::map<std::string, std::string>* ModelElement::SaveInstance(ModelElement* element) {
    std::map<std::string, std::string>* fields; // = new std::list<std::string>();
    try {
	fields = element->_saveInstance();
    } catch (const std::exception& e) {
	//element->_model->getTrace()->traceError(e, "Error saving infra " + element->show());
    }
    return fields;
}

bool ModelElement::Check(ModelElement* element, std::string* errorMessage) {
    //    element->_model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, "Checking " + element->_typename + ": " + element->_name); //std::to_string(element->_id));
    bool res = false;
    Util::IncIndent();
    {
	try {
	    res = element->_check(errorMessage);
	    if (!res) {
		//                element->_model->getTraceManager()->trace(Util::TraceLevel::errors, "Error: Checking has failed with message '" + *errorMessage + "'");
	    }
	} catch (const std::exception& e) {
	    //            element->_model->getTraceManager()->traceError(e, "Error verifying element " + element->show());
	}
    }
    Util::DecIndent();
    return res;
}
