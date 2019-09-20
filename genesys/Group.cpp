/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Group.cpp
 * Author: rlcancian
 * 
 * Created on 12 de Junho de 2019, 19:00
 */

#include "Group.h"
#include "Model.h"
#include "Attribute.h"

Group::Group(ElementManager* elems) : ModelElement(Util::TypeOf<Group>()) {
    _elements = elems;
    _initCStats(); 
}

Group::Group(ElementManager* elems, std::string name) : ModelElement(Util::TypeOf<Group>()) {
    _name = name;
    _elements = elems;
    _initCStats();
}

void Group::_initCStats() {
    _cstatNumberInGroup = new StatisticsCollector(_elements, "Number In Group", this);
    _elements->insert(Util::TypeOf<StatisticsCollector>(), _cstatNumberInGroup);
}

Group::Group(const Group& orig) : ModelElement(orig) {
}

Group::~Group() {
    _elements->remove(Util::TypeOf<StatisticsCollector>(), _cstatNumberInGroup);
}

std::string Group::show() {
    return ModelElement::show() +
	    ",entities=" + this->_list->show();
}

void Group::insertElement(Entity* element) {
    _list->insert(element);
    this->_cstatNumberInGroup->getStatistics()->getCollector()->addValue(_list->size());
}

void Group::removeElement(Entity* element) {
    double tnow = this->_elements->getParentModel()->getSimulation()->getSimulatedTime();
    _list->remove(element);
    this->_cstatNumberInGroup->getStatistics()->getCollector()->addValue(_list->size());
}

void Group::initBetweenReplications() {
    this->_list->clear();
}

unsigned int Group::size() {
    return _list->size();
}

Entity* Group::first() {
    return _list->front();
}

//List<Waiting*>* Group::getList() const {
//	return _list;
//}

PluginInformation* Group::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<Group>(), &Group::LoadInstance); return info;
}

ModelElement* Group::LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields) {
    Group* newElement = new Group(elems);
    try {
	newElement->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newElement;
}

bool Group::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelElement::_loadInstance(fields);
    if (res) {
	try {
	} catch (...) {
	}
    }
    return res;
}

std::map<std::string, std::string>* Group::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelElement::_saveInstance(); //Util::TypeOf<Group>());
    return fields;
}

bool Group::_check(std::string* errorMessage) {
    std::string newNeededAttributeName = "Entity.Group";
    if (_elements->getElement(Util::TypeOf<Attribute>(), newNeededAttributeName ) == nullptr) {
	    Attribute* attr1 = new Attribute(newNeededAttributeName );
	    _elements->insert(Util::TypeOf<Attribute>(), attr1);
	}
    return true;
}

