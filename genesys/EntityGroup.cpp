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

#include "EntityGroup.h"
#include "Model.h"
#include "Attribute.h"

EntityGroup::EntityGroup(ElementManager* elems) : ModelElement(Util::TypeOf<EntityGroup>()) {
    _elements = elems;
    _initCStats(); 
}

EntityGroup::EntityGroup(ElementManager* elems, std::string name) : ModelElement(Util::TypeOf<EntityGroup>()) {
    _name = name;
    _elements = elems;
    _initCStats();
}

void EntityGroup::_initCStats() {
    _cstatNumberInGroup = new StatisticsCollector(_elements, "Number In Group", this);
    _elements->insert(Util::TypeOf<StatisticsCollector>(), _cstatNumberInGroup);
}

EntityGroup::EntityGroup(const EntityGroup& orig) : ModelElement(orig) {
}

EntityGroup::~EntityGroup() {
    _elements->remove(Util::TypeOf<StatisticsCollector>(), _cstatNumberInGroup);
}

std::string EntityGroup::show() {
    return ModelElement::show() +
	    ",entities=" + this->_list->show();
}

void EntityGroup::insertElement(Entity* element) {
    _list->insert(element);
    this->_cstatNumberInGroup->getStatistics()->getCollector()->addValue(_list->size());
}

void EntityGroup::removeElement(Entity* element) {
    double tnow = this->_elements->getParentModel()->getSimulation()->getSimulatedTime();
    _list->remove(element);
    this->_cstatNumberInGroup->getStatistics()->getCollector()->addValue(_list->size());
}

void EntityGroup::initBetweenReplications() {
    this->_list->clear();
}

unsigned int EntityGroup::size() {
    return _list->size();
}

Entity* EntityGroup::first() {
    return _list->front();
}

//List<Waiting*>* Group::getList() const {
//	return _list;
//}

PluginInformation* EntityGroup::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<EntityGroup>(), &EntityGroup::LoadInstance); 
    return info;
}

ModelElement* EntityGroup::LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields) {
    EntityGroup* newElement = new EntityGroup(elems);
    try {
	newElement->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newElement;
}

bool EntityGroup::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelElement::_loadInstance(fields);
    if (res) {
	try {
	} catch (...) {
	}
    }
    return res;
}

std::map<std::string, std::string>* EntityGroup::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelElement::_saveInstance(); //Util::TypeOf<Group>());
    return fields;
}

bool EntityGroup::_check(std::string* errorMessage) {
    std::string newNeededAttributeName = "Entity.Group";
    if (_elements->getElement(Util::TypeOf<Attribute>(), newNeededAttributeName ) == nullptr) {
	    Attribute* attr1 = new Attribute(newNeededAttributeName );
	    _elements->insert(Util::TypeOf<Attribute>(), attr1);
	}
    return true;
}

