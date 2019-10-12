/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Entity.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 21 de Junho de 2018, 16:30
 */

#include <typeinfo>
#include "Entity.h"
#include "Attribute.h"

Entity::Entity(ElementManager* elements) : ModelElement(Util::TypeOf<Entity>()) {
    _elements = elements;
    _entityNumber = Util::GetLastIdOfType(Util::TypeOf<Entity>());
    unsigned int numAttributes = _elements->getNumberOfElements(Util::TypeOf<Attribute>());
    for (unsigned i = 0; i < numAttributes; i++) {
	_attributeValues->insert(0.0);
    }
}

Entity::Entity(const Entity& orig) : ModelElement(orig) {
}

Entity::~Entity() {
}

void Entity::setEntityTypeName(std::string entityTypeName) throw () {
    EntityType* entitytype = dynamic_cast<EntityType*> (this->_elements->getElement(Util::TypeOf<EntityType>(), entityTypeName));
    if (entitytype != nullptr) {
	this->_entityType = entitytype;
    } else {
	throw std::invalid_argument("EntityType does not exist");
    }
}

std::string Entity::getEntityTypeName() const {
    return this->_entityType->getName();
}

void Entity::setEntityType(EntityType* entityType) {
    _entityType = entityType;
}

EntityType* Entity::getEntityType() const {
    return _entityType;
}

std::string Entity::show() {
    std::string message = ModelElement::show();
    if (this->_entityType != nullptr) {
	message += ",entityType=\"" + this->_entityType->getName() + "\"";
    }
    message += ",attributeValues=[";
    _attributeValues->front();
    for (unsigned int i = 0; i < _attributeValues->size(); i++) {
	message += std::to_string(_attributeValues->actual()) + ",";
	_attributeValues->next();
    }
    message += "]";
    return message;
}

double Entity::getAttributeValue(std::string attributeName) {
    int rank = this->_elements->getRankOf(Util::TypeOf<Attribute>(), attributeName);
    if (rank >= 0) {
	return this->_attributeValues->getAtRank(rank);
    } else
	return 0.0; /* TODO: Never should happen. check how to report */
}

double Entity::getAttributeValue(Util::identification attributeID) {
    ModelElement* element = this->_elements->getElement(Util::TypeOf<Attribute>(), attributeID);
    if (element != nullptr) {
	return getAttributeValue(element->getName());
    }
    return 0.0; // attribute not found
}

void Entity::setAttributeValue(std::string attributeName, double value) {
    int rank = this->_elements->getRankOf(Util::TypeOf<Attribute>(), attributeName);
    if (rank >= 0) {
	this->_attributeValues->setAtRank(rank, value);
    }
    /*
    std::map<std::string, AttributeValue*>::iterator it = entity->getAttributeValues()->find('Entity.ArrivalTime');
    if (it != entity->getAttributeValues()::end()) {
	(*it)->second->setValue(this->_model->getSimulationTime());
    }
     */
}

Util::identification Entity::getEntityNumber() const {
    return _entityNumber;
}

bool Entity::_loadInstance(std::map<std::string, std::string>* fields) {
    // never lods an entity
    return true;
}

std::map<std::string, std::string>* Entity::_saveInstance() {
    return new std::map<std::string,std::string>(); 
}

bool Entity::_check(std::string* errorMessage) {
    return true;
}
