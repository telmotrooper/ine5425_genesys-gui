/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Write.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 13:06
 */

#include "Write.h"

#include "Model.h"

Write::Write(Model* model) : ModelComponent(model, Util::TypeOf<Write>()) {
}

Write::Write(const Write& orig) : ModelComponent(orig) {
}

Write::~Write() {
}

std::string Write::show() {
    return ModelComponent::show() + "";
}

ModelComponent* Write::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Write* newComponent = new Write(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

List<WriteElement*>* Write::getWriteElements() const {
    return _writeElements;
}

void Write::setFilename(std::string _filename) {
    this->_filename = _filename;
}

std::string Write::getFilename() const {
    return _filename;
}

void Write::setWriteToType(WriteToType _writeToType) {
    this->_writeToType = _writeToType;
}

Write::WriteToType Write::getWriteToType() const {
    return _writeToType;
}

void Write::_execute(Entity* entity) {
    //_model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "I'm just a dummy model and I'll just send the entity forward");
    WriteElement* msgElem;
    if (this->_writeToType == Write::WriteToType::SCREEN) { //@TODO: Write To FILE not implemented
	std::list<WriteElement*>* msgs = this->_writeElements->getList();
	std::string message = "";
	for (std::list<WriteElement*>::iterator it = msgs->begin(); it != msgs->end(); it++) {
	    msgElem = (*it);
	    if (msgElem->isExpression) {
		message += std::to_string(_model->parseExpression(msgElem->text));
	    } else {
		message += msgElem->text;
	    }
	    if (msgElem->newline) {
		_model->getTraceManager()->trace(Util::TraceLevel::report, message);
		message = "";
	    }
	}
	if (message != "") {
	    _model->getTraceManager()->trace(Util::TraceLevel::report, message);
	}
    }
    this->_model->sendEntityToComponent(entity, this->getNextComponents()->frontConnection(), 0.0);
}

bool Write::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	//...
    }
    return res;
}

void Write::_initBetweenReplications() {
}

std::map<std::string, std::string>* Write::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    //...
    return fields;
}

bool Write::_check(std::string* errorMessage) {
    bool resultAll = true;
    WriteElement* msgElem;
    unsigned short i=0;
    std::list<WriteElement*>* msgs = this->_writeElements->getList();
    for (std::list<WriteElement*>::iterator it = msgs->begin(); it != msgs->end(); it++) {
	msgElem = (*it);
	i++;
	if (msgElem->isExpression) {
	    /////////////////////////////// resultAll &= _model->checkExpression(msgElem->text, "writeExpression"+std::to_string(i), errorMessage);
	}
    }
    return resultAll;
}

PluginInformation* Write::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<Write>(), &Write::LoadInstance);
    // ...
    return info;
}


