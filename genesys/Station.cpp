/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Station.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:12
 */

#include "Station.h"
#include "Entity.h"
#include "Model.h"
#include "Attribute.h"

Station::Station(ElementManager* elems) : ModelElement(Util::TypeOf<Station>()) {
    _elems = elems;
    _initCStats();
}

Station::Station(ElementManager* elems, std::string name) : ModelElement(Util::TypeOf<Station>()) {
    _name = name;
    _elems = elems;
    _initCStats();
}

void Station::_initCStats() {
    _cstatNumberInStation = new StatisticsCollector(_elems, _name+"."+"Number_In_Station", this);
    _cstatTimeInStation = new StatisticsCollector(_elems, _name+"."+"Time_In_Station", this);
    _elems->insert(Util::TypeOf<StatisticsCollector>(), _cstatNumberInStation);
    _elems->insert(Util::TypeOf<StatisticsCollector>(), _cstatTimeInStation);

}

Station::Station(const Station& orig) : ModelElement(orig) {
}

Station::~Station() {
    _elems->remove(Util::TypeOf<StatisticsCollector>(), _cstatNumberInStation);
    _elems->remove(Util::TypeOf<StatisticsCollector>(), _cstatTimeInStation);
}

std::string Station::show() {
    std::string msg = ModelElement::show() + ",enterIntoStationComponent=";
    if (_enterIntoStationComponent == nullptr)
	msg += "NULL";
    else
	msg += _enterIntoStationComponent->getName();
    return msg;
}

void Station::initBetweenReplications() {
    //this->_list->clear();
}

void Station::enter(Entity* entity) {
    std::string attributeName = "Entity.ArrivalAt" + this->getName();
    trimwithin(attributeName);
    entity->setAttributeValue(attributeName, _elems->getParentModel()->getSimulation()->getSimulatedTime());
    entity->setAttributeValue("Entity.Station", _id);
    _numberInStation++;
    this->_cstatNumberInStation->getStatistics()->getCollector()->addValue(_numberInStation);
}

void Station::leave(Entity* entity) {
    std::string attributeName = "Entity.ArrivalAt" + this->getName();
    trimwithin(attributeName);
    double arrivalTime = entity->getAttributeValue(attributeName);
    double timeInStation = _elems->getParentModel()->getSimulation()->getSimulatedTime() - arrivalTime;
    _cstatTimeInStation->getStatistics()->getCollector()->addValue(timeInStation);
    entity->getEntityType()->getStatisticsCollector("Time in Stations")->getStatistics()->getCollector()->addValue(timeInStation);
    entity->setAttributeValue("Entity.Station", 0.0);
    _numberInStation--;
    _cstatNumberInStation->getStatistics()->getCollector()->addValue(_numberInStation);
}

void Station::setEnterIntoStationComponent(ModelComponent* _enterIntoStationComponent) {
    this->_enterIntoStationComponent = _enterIntoStationComponent;
}

ModelComponent* Station::getEnterIntoStationComponent() const {
    return _enterIntoStationComponent;
}

PluginInformation* Station::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<Station>(), &Station::LoadInstance);
    return info;
}

ModelElement* Station::LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields) {
    Station* newElement = new Station(elems);
    try {
	newElement->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newElement;
}

bool Station::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelElement::_loadInstance(fields);
    if (res) {
	try {
	} catch (...) {
	}
    }
    return res;
}

std::map<std::string, std::string>* Station::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelElement::_saveInstance(); //Util::TypeOf<Station>());
    return fields;
}

bool Station::_check(std::string* errorMessage) {
    /* include attributes needed */
    std::vector<std::string> neededNames = {"Entity.Station"};
    neededNames.insert(neededNames.begin(), "Entity.ArrivalAt" + this->getName());
    std::string neededName;
    for (int i = 0; i < neededNames.size(); i++) {
	neededName = neededNames[i];
	if (_elems->getElement(Util::TypeOf<Attribute>(), neededName) == nullptr) {
	    Attribute* attr1 = new Attribute(neededName);
	    _elems->insert(Util::TypeOf<Attribute>(), attr1);
	}
    }
    // include StatisticsCollector needed in EntityType
    std::list<ModelElement*>* enttypes = _elems->getElements(Util::TypeOf<EntityType>())->getList();
    for (std::list<ModelElement*>::iterator it = enttypes->begin(); it != enttypes->end(); it++) {
	static_cast<EntityType*> ((*it))->getStatisticsCollector("Time in Stations"); // force create this CStat before simulation starts
    }
    //
    return true;
}

void Station::_createInternalElements() {
    //_initCStats();
}

