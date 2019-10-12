/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OnEventManager.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 7 de Novembro de 2018, 12:28
 */

#include "OnEventManager.h"

OnEventManager::OnEventManager() {
}

OnEventManager::OnEventManager(const OnEventManager& orig) {
}

OnEventManager::~OnEventManager() {
}

void OnEventManager::addOnReplicationStartHandler(simulationEventHandler EventHandler) {
    this->_onReplicationStartHandlers->insert(this->_onReplicationStartHandlers->end(), EventHandler);
}

void OnEventManager::addOnReplicationStepHandler(simulationEventHandler EventHandler) {
    this->_onReplicationStepHandlers->insert(this->_onReplicationStepHandlers->end(), EventHandler);
}

void OnEventManager::addOnProcessEventHandler(simulationEventHandler EventHandler) {
    this->_onProcessEventHandlers->insert(this->_onProcessEventHandlers->end(), EventHandler);
}

void OnEventManager::addOnEntityMoveHandler(simulationEventHandler EventHandler) {
    this->_onEntityMoveHandlers->insert(this->_onEntityMoveHandlers->end(), EventHandler);
}

void OnEventManager::addOnReplicationEndHandler(simulationEventHandler EventHandler) {
    this->_onReplicationEndHandlers->insert(this->_onReplicationEndHandlers->end(), EventHandler);
}

void OnEventManager::addOnSimulationStartHandler(simulationEventHandler EventHandler) {
    this->_onSimulationStartHandlers->insert(this->_onSimulationStartHandlers->end(), EventHandler);
}

void OnEventManager::addOnSimulationEndHandler(simulationEventHandler EventHandler) {
    this->_onSimulationEndHandlers->insert(this->_onSimulationEndHandlers->end(), EventHandler);
}

void OnEventManager::_NotifyHandlers(std::list<simulationEventHandler>* list, SimulationEvent* se) {
    for (std::list<simulationEventHandler>::iterator it = list->begin(); it != list->end(); it++) {
	(*it)(se);
    }
}

void OnEventManager::NotifyReplicationStartHandlers(SimulationEvent* se) {
    this->_NotifyHandlers(this->_onReplicationStartHandlers, se);

}

void OnEventManager::NotifyReplicationStepHandlers(SimulationEvent* se) {
    this->_NotifyHandlers(this->_onReplicationStepHandlers, se);

}

void OnEventManager::NotifyReplicationEndHandlers(SimulationEvent* se) {
    this->_NotifyHandlers(this->_onReplicationEndHandlers, se);
}

void OnEventManager::NotifyEntityMoveHandlers(SimulationEvent* se) {
    this->_NotifyHandlers(this->_onEntityMoveHandlers, se);
}

void OnEventManager::NotifyProcessEventHandlers(SimulationEvent* se) {
    this->_NotifyHandlers(this->_onProcessEventHandlers, se);
}

void OnEventManager::NotifySimulationStartHandlers(SimulationEvent* se) {
    this->_NotifyHandlers(this->_onReplicationEndHandlers, se);
}

void OnEventManager::NotifySimulationEndHandlers(SimulationEvent* se) {
    this->_NotifyHandlers(this->_onSimulationEndHandlers, se);
}