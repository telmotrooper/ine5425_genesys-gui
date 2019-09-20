/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TraceManager.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 7 de Novembro de 2018, 11:59
 */

#include "TraceManager.h"
#include "Traits.h"

TraceManager::TraceManager(Simulator* simulator) {//(Model* model) {
    _simulator = simulator;
    _debugged = Traits<Model>::debugged;
    _traceLevel = Traits<Model>::traceLevel;
}

TraceManager::TraceManager(const TraceManager& orig) {
}

TraceManager::~TraceManager() {
}

void TraceManager::setTraceLevel(Util::TraceLevel _traceLevel) {
    this->_traceLevel = _traceLevel;
}

Util::TraceLevel TraceManager::getTraceLevel() const {
    return _traceLevel;
}

Simulator* TraceManager::getSimulator() const {
    return _simulator;
}

/*
 void TraceManager::traceSimulation(Util::TraceLevel tracelevel, std::string text) {
	if (_traceConditionPassed(tracelevel)) {
		TraceSimulationEvent e = TraceEvent(tracelevel, text);
		for (std::list<traceSimulationListener>::iterator it = this->_traceSimulationHandlers->begin(); it != _traceSimulationHandlers->end(); it++) {
			(*it)(e);
		}
	}
}
 */

void TraceManager::addTraceHandler(traceListener traceListener) {
    this->_traceHandlers->insert(_traceHandlers->end(), traceListener);
}

//void TraceManager::addTraceSimulationHandler(traceListener traceListener) {
//	this->_traceSimulationHandlers->insert(_traceSimulationHandlers->end(), traceListener);
//}

void TraceManager::addTraceSimulationHandler(traceSimulationListener traceSimulationListener) {
    this->_traceSimulationHandlers->insert(_traceSimulationHandlers->end(), traceSimulationListener);
}

void TraceManager::addTraceErrorHandler(traceErrorListener traceErrorListener) {
    this->_traceErrorHandlers->insert(_traceErrorHandlers->end(), traceErrorListener);
}

void TraceManager::addTraceReportHandler(traceListener traceReportListener) {
    this->_traceReportHandlers->insert(_traceReportHandlers->end(), traceReportListener);
}

void TraceManager::trace(Util::TraceLevel tracelevel, std::string text) {
    if (_traceConditionPassed(tracelevel)) {
	text = Util::Indent() + text;
	TraceEvent e = TraceEvent(tracelevel, text);
	/* TODO--: somewhere in future it should be interesting to use "auto" and c++17 at least */
	for (std::list<traceListener>::iterator it = this->_traceHandlers->begin(); it != _traceHandlers->end(); it++) {
	    (*it)(e);
	}
	for (std::list<traceListenerMethod>::iterator it = this->_traceHandlersMethod->begin(); it != _traceHandlersMethod->end(); it++) {
	    (*it)(e);
	}

    }
}

void TraceManager::traceError(std::exception e, std::string text) {
    TraceErrorEvent exceptEvent = TraceErrorEvent(text, e);
    /* TODO--: somewhere in future it should be interesting to use "auto" and c++17 at least */
    for (std::list<traceErrorListener>::iterator it = this->_traceErrorHandlers->begin(); it != _traceErrorHandlers->end(); it++) {
	(*it)(exceptEvent);
    }
    for (std::list<traceErrorListenerMethod>::iterator it = this->_traceErrorHandlersMethod->begin(); it != _traceErrorHandlersMethod->end(); it++) {
	(*it)(exceptEvent);
    }
}

void TraceManager::traceSimulation(Util::TraceLevel tracelevel, double time, Entity* entity, ModelComponent* component, std::string text) {
    if (_traceConditionPassed(tracelevel)) {
	text = Util::Indent() + text;
	TraceSimulationEvent e = TraceSimulationEvent(tracelevel, time, entity, component, text);
	for (std::list<traceSimulationListener>::iterator it = this->_traceSimulationHandlers->begin(); it != _traceSimulationHandlers->end(); it++) {
	    (*it)(e);
	}
	for (std::list<traceSimulationListenerMethod>::iterator it = this->_traceSimulationHandlersMethod->begin(); it != _traceSimulationHandlersMethod->end(); it++) {
	    (*it)(e);
	}
    }
}

void TraceManager::traceReport(Util::TraceLevel tracelevel, std::string text) {
    if (_traceConditionPassed(tracelevel)) {
	text = Util::Indent() + text;
	TraceEvent e = TraceEvent(tracelevel, text);
	for (std::list<traceListener>::iterator it = this->_traceReportHandlers->begin(); it != _traceReportHandlers->end(); it++) {
	    (*it)(e);
	}
	for (std::list<traceListenerMethod>::iterator it = this->_traceReportHandlersMethod->begin(); it != _traceReportHandlersMethod->end(); it++) {
	    (*it)(e);
	}
    }
}

List<std::string>* TraceManager::getErrorMessages() const {
    return _errorMessages;
}

bool TraceManager::_traceConditionPassed(Util::TraceLevel level) {
    return this->_debugged && static_cast<int> (this->_traceLevel) >= static_cast<int> (level);
}
