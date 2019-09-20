/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Route.cpp
 * Author: rlcancian
 * 
 * Created on 03 de Junho de 2019, 15:15
 */

#include "Route.h"
#include "Model.h"
#include "Attribute.h"
#include "Simulator.h"

Route::Route(Model* model) : ModelComponent(model, Util::TypeOf<Route>()) {
}

Route::Route(const Route& orig) : ModelComponent(orig) {
}

Route::~Route() {
}

std::string Route::show() {
    std::string msg= ModelComponent::show() + 
	    ",destinationType="+std::to_string(static_cast<int>(this->_routeDestinationType))+
	    ",timeExpression="+this->_routeTimeExpression+" "+Util::StrTimeUnit(this->_routeTimeTimeUnit);
    if (_station != nullptr)
	msg += ",station="+this->_station->getName();
    return msg;
}

ModelComponent* Route::LoadInstance(Model* model, std::map<std::string, std::string>* fields) {
    Route* newComponent = new Route(model);
    try {
	newComponent->_loadInstance(fields);
    } catch (const std::exception& e) {

    }
    return newComponent;
}

void Route::setStation(Station* _station) {
    this->_station = _station;
}

Station* Route::getStation() const {
    return _station;
}

void Route::setRouteTimeExpression(std::string _routeTimeExpression) {
    this->_routeTimeExpression = _routeTimeExpression;
}

std::string Route::getRouteTimeExpression() const {
    return _routeTimeExpression;
}

void Route::setRouteTimeTimeUnit(Util::TimeUnit _routeTimeTimeUnit) {
    this->_routeTimeTimeUnit = _routeTimeTimeUnit;
}

Util::TimeUnit Route::getRouteTimeTimeUnit() const {
    return _routeTimeTimeUnit;
}

void Route::setRouteDestinationType(DestinationType _routeDestinationType) {
    this->_routeDestinationType = _routeDestinationType;
}

Route::DestinationType Route::getRouteDestinationType() const {
    return _routeDestinationType;
}

void Route::_execute(Entity* entity) {
    // adds the route time to the TransferTime statistics / attribute related to the Entitys 
    double routeTime = _model->parseExpression(_routeTimeExpression) * Util::TimeUnitConvert(_routeTimeTimeUnit, _model->getInfos()->getReplicationLengthTimeUnit());
    entity->getEntityType()->getStatisticsCollector("Transfer Time")->getStatistics()->getCollector()->addValue(routeTime);
    entity->setAttributeValue("Entity.TransferTime", entity->getAttributeValue("Entity.TransferTime") + routeTime);
    if (routeTime > 0.0) {
	// calculates when this Entity will reach the end of this route and schedule this Event
	double routeEndTime = _model->getSimulation()->getSimulatedTime() + routeTime;
	Event* newEvent = new Event(routeEndTime, entity, _station->getEnterIntoStationComponent());
	_model->getEvents()->insert(newEvent);
	_model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "End of route of entity " + std::to_string(entity->getEntityNumber()) + " to the component \"" + _station->getEnterIntoStationComponent()->getName() + "\" was scheduled to time " + std::to_string(routeEndTime));
    } else {
	// send without delay
	_model->sendEntityToComponent(entity, _station->getEnterIntoStationComponent(), 0.0);
    }
}

bool Route::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
	this->_routeTimeExpression = (*fields->find("routeTimeExpression")).second;
	this->_routeTimeTimeUnit = static_cast<Util::TimeUnit> (std::stoi((*fields->find("routeTimeTimeUnit")).second));
	this->_routeDestinationType = static_cast<Route::DestinationType> (std::stoi((*fields->find("routeDestinationType")).second));
	std::string stationName = ((*(fields->find("stationName"))).second);
	Station* station = dynamic_cast<Station*> (_model->getElementManager()->getElement(Util::TypeOf<Station>(), stationName));
	this->_station = station;
    }
    return res;
}

void Route::_initBetweenReplications() {
}

std::map<std::string, std::string>* Route::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    fields->emplace("stationId", std::to_string(this->_station->getId()));
    fields->emplace("stationName", (this->_station->getName()));
    fields->emplace("routeTimeExpression", this->_routeTimeExpression);
    fields->emplace("routeTimeTimeUnit", std::to_string(static_cast<int> (this->_routeTimeTimeUnit)));
    fields->emplace("routeDestinationType", std::to_string(static_cast<int> (this->_routeDestinationType)));
    return fields;
}

bool Route::_check(std::string* errorMessage) {
    //include attributes needed
    ElementManager* elements = _model->getElementManager();
    std::vector<std::string> neededNames = {"Entity.TransferTime", "Entity.Station"};
    std::string neededName;
    for (unsigned int i = 0; i < neededNames.size(); i++) {
	neededName = neededNames[i];
	if (elements->getElement(Util::TypeOf<Attribute>(), neededName) == nullptr) {
	    Attribute* attr1 = new Attribute(neededName);
	    elements->insert(Util::TypeOf<Attribute>(), attr1);
	}
    } 
    // include StatisticsCollector needed in EntityType
    std::list<ModelElement*>* enttypes = elements->getElements(Util::TypeOf<EntityType>())->getList();
    for (std::list<ModelElement*>::iterator it= enttypes->begin(); it!= enttypes->end(); it++) {
	static_cast<EntityType*>((*it))->getStatisticsCollector("Transfer Time"); // force create this CStat before simulation starts
    }
    bool resultAll = true;
    resultAll &= _model->checkExpression(_routeTimeExpression, "Route time expression", errorMessage);
    resultAll &= _model->getElementManager()->check(Util::TypeOf<Station>(), _station, "Station", errorMessage);
    if (resultAll) {
	resultAll &= _station->getEnterIntoStationComponent() != nullptr;
	if (!resultAll) {
	    errorMessage->append("Station has no component to enter into it");
	}
    }
    //_model->getParent()->getPluginManager()->
    return resultAll;
}

PluginInformation* Route::GetPluginInformation() {
    PluginInformation* info = new PluginInformation(Util::TypeOf<Route>(), &Route::LoadInstance);
    info->setSendTransfer(true);
    info->insertDynamicLibFileDependence("station.so");
    return info;
}


