/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ComponentManager.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 28 de Maio de 2019, 10:41
 */

#include "ComponentManager.h"
#include "List.h"

ComponentManager::ComponentManager(Model* model) {
    _model = model;
    _components = new List<ModelComponent*>();
    _components->setSortFunc([](const ModelComponent* a, const ModelComponent * b) {
	return a->getId() < b->getId(); /// Components are sorted by ID
    });
}

ComponentManager::ComponentManager(const ComponentManager& orig) {
}

ComponentManager::~ComponentManager() {
}

bool ComponentManager::insert(ModelComponent* comp) {
    _components->insert(comp);
}

void ComponentManager::remove(ModelComponent* comp) {
    _components->remove(comp);
}

void ComponentManager::clear(){
    this->_components->clear();
}

ModelComponent* ComponentManager::getComponent(Util::identitifcation id) {
}

ModelComponent* ComponentManager::getComponent(std::string name) {
    //_components->f
}

unsigned int ComponentManager::getNumberOfComponents() {
    _components->size();
}

std::list<ModelComponent*>::iterator ComponentManager::begin() {
    return _components->getList()->begin();
}

std::list<ModelComponent*>::iterator ComponentManager::end() {
    return _components->getList()->end();
}