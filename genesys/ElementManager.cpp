/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ElementManager.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 7 de Novembro de 2018, 12:48
 */

#include "ElementManager.h"
#include "Model.h"

ElementManager::ElementManager(Model* model) {
    _model = model;
    /* TODO: -- Sort methods for elements should be a decorator */
    _elements = new std::map<std::string, List<ModelElement*>*>(); /// Elements are organized as a map from a string (key), the type of an element, and a list of elements of that type 
    //_elements->setSortFunc([](const ModelElement* a, const ModelElement * b) {
    //	return a->getId() < b->getId();
    //});

}

ElementManager::ElementManager(const ElementManager& orig) {
}

ElementManager::~ElementManager() {
}

bool ElementManager::insert(std::string infraTypename, ModelElement* infra) {
    List<ModelElement*>* listElements = getElements(infraTypename);
    if (listElements->find(infra) == listElements->getList()->end()) { //not found
	//if (dynamic_cast<ModelElement*> (infra) == nullptr) { // how? remove it. test only because of seg faults
	//	return false;
	//}
	//infra->SaveInstance(infra);
	listElements->insert(infra);
	return true;
    }
    return false;
}

void ElementManager::remove(std::string infraTypename, ModelElement* infra) {
    List<ModelElement*>* listElements = getElements(infraTypename);
    listElements->remove(infra);
    infra->~ModelElement(); /* TODO: Check: Should really destroy infra here? */
}

bool ElementManager::check(std::string infraTypename, std::string infraName, std::string expressionName, bool mandatory, std::string* errorMessage) {
    if (infraName == "" && !mandatory) {
	return true;
    }
    bool result = getElement(infraTypename, infraName) != nullptr;
    if (!result) {
	std::string msg = infraTypename + " \"" + infraName + "\" for '" + expressionName + "' is not in the model.";
	errorMessage->append(msg);
    }
    return result;
}

bool ElementManager::check(std::string infraTypename, ModelElement* infra, std::string expressionName, std::string* errorMessage) {
    bool result = infra != nullptr;
    if (!result) {
	std::string msg = infraTypename + " for '" + expressionName + "' is null.";
	errorMessage->append(msg);
    } else {
	result = check(infraTypename, infra->getName(), expressionName, true, errorMessage);
    }
    return result;
}

void ElementManager::clear() {
    this->_elements->clear();
}

unsigned int ElementManager::getNumberOfElements(std::string infraTypename) {
    List<ModelElement*>* listElements = getElements(infraTypename);
    return listElements->size();
}

unsigned int ElementManager::getNumberOfElements() {
    unsigned int total = 0;
    for (std::map<std::string, List<ModelElement*>*>::iterator it = _elements->begin(); it != _elements->end(); it++) {
	total += (*it).second->size();
    }
    return total;
}

void ElementManager::show() {
    _model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, "Model Elements:");
    //std::map<std::string, List<ModelElement*>*>* _elements;
    std::string key;
    List<ModelElement*>* list;
    Util::IncIndent();
    {
	for (std::map<std::string, List<ModelElement*>*>::iterator infraIt = _elements->begin(); infraIt != _elements->end(); infraIt++) {
	    key = (*infraIt).first;
	    list = (*infraIt).second;
	    _model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, key + ": (" + std::to_string(list->size()) + ")");
	    Util::IncIndent();
	    {
		for (std::list<ModelElement*>::iterator it = list->getList()->begin(); it != list->getList()->end(); it++) {
		    _model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, (*it)->show());
		}
	    }
	    Util::DecIndent();
	}
    }
    Util::DecIndent();
}

Model* ElementManager::getParentModel() const {
    return _model;
}

List<ModelElement*>* ElementManager::getElements(std::string infraTypename) const {
    std::map<std::string, List<ModelElement*>*>::iterator it = this->_elements->find(infraTypename);
    if (it == this->_elements->end()) {
	// list does not exists yet. Create it and set a valid iterator
	List<ModelElement*>* newList = new List<ModelElement*>();
	newList->setSortFunc([](const ModelElement* a, const ModelElement * b) {
	    return a->getId() < b->getId();
	});
	_elements->insert(std::pair<std::string, List<ModelElement*>*>(infraTypename, newList));
	it = this->_elements->find(infraTypename);
    }
    List<ModelElement*>* infras = it->second;
    return infras;
}

ModelElement* ElementManager::getElement(std::string infraTypename, Util::identitifcation id) {
    List<ModelElement*>* list = getElements(infraTypename);
    for (std::list<ModelElement*>::iterator it = list->getList()->begin(); it != list->getList()->end(); it++) {
	if ((*it)->getId() == id) { // found
	    return (*it);
	}
    }
    return nullptr;
}

int ElementManager::getRankOf(std::string infraTypename, std::string name) {
    int rank = 0;
    List<ModelElement*>* list = getElements(infraTypename);
    for (std::list<ModelElement*>::iterator it = list->getList()->begin(); it != list->getList()->end(); it++) {
	if ((*it)->getName() == name) { // found
	    return rank;
	} else {
	    rank++;
	}
    }
    return -1;
}

std::list<std::string>* ElementManager::getElementTypenames() const {
    std::list<std::string>* keys = new std::list<std::string>();
    for (std::map<std::string, List<ModelElement*>*>::iterator it = _elements->begin(); it != _elements->end(); it++) {
	keys->insert(keys->end(), (*it).first);
    }
    return keys;
}

ModelElement* ElementManager::getElement(std::string infraTypename, std::string name) {
    List<ModelElement*>* list = getElements(infraTypename);
    for (std::list<ModelElement*>::iterator it = list->getList()->begin(); it != list->getList()->end(); it++) {
	if ((*it)->getName() == name) { // found
	    return (*it);
	}
    }
    return nullptr;
}