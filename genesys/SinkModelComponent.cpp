/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SinkModelComponent.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 14 de Agosto de 2018, 14:29
 */

#include "SinkModelComponent.h"

SinkModelComponent::SinkModelComponent(Model* model, std::string componentTypename) : ModelComponent(model, componentTypename) {
}

SinkModelComponent::SinkModelComponent(const SinkModelComponent& orig) : ModelComponent(orig) {
}

SinkModelComponent::~SinkModelComponent() {
}

void SinkModelComponent::setCollectStatistics(bool _collectStatistics) {
    this->_collectStatistics = _collectStatistics;
}

bool SinkModelComponent::isCollectStatistics() const {
    return _collectStatistics;
}

bool SinkModelComponent::_loadInstance(std::map<std::string, std::string>* fields) {
    bool res = ModelComponent::_loadInstance(fields);
    if (res) {
    this->_collectStatistics = std::stoi((*fields->find("collectStatistics")).second) != 0;
    }
    return res;
}

void SinkModelComponent::_initBetweenReplications() {
}

std::map<std::string, std::string>* SinkModelComponent::_saveInstance() {
    std::map<std::string, std::string>* fields = ModelComponent::_saveInstance();
    fields->emplace("collectStatistics", std::to_string(this->_collectStatistics));
    return fields;
}

bool SinkModelComponent::_check(std::string* errorMessage) {
}