/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TraceManager.h
 * Author: rafael.luiz.cancian
 *
 * Created on 7 de Novembro de 2018, 11:59
 */

#ifndef TRACEMANAGER_H
#define TRACEMANAGER_H

#include "List.h"
#include <functional>

class Model;
class Entity;
class ModelComponent;

class TraceEvent {
public:

    TraceEvent(Util::TraceLevel tracelevel, std::string text) {
	_tracelevel = tracelevel;
	_text = text;
    }

    Util::TraceLevel getTracelevel() const {
	return _tracelevel;
    }

    std::string getText() const {
	return _text;
    }
private:
    Util::TraceLevel _tracelevel;
    std::string _text;
};

class TraceErrorEvent : public TraceEvent {
public:

    TraceErrorEvent(std::string text, std::exception e) : TraceEvent(Util::TraceLevel::errors, text) {
	_e = e;
    }

    std::exception getException() const {
	return _e;
    }
private:
    std::exception _e;
};

class TraceSimulationEvent : public TraceEvent {
public:

    TraceSimulationEvent(Util::TraceLevel tracelevel, double time, Entity* entity, ModelComponent* component, std::string text) : TraceEvent(tracelevel, text) {
	_time = time;
	_entity = entity;
	_component = component;
    }

    ModelComponent* getComponent() const {
	return _component;
    }

    Entity* getEntity() const {
	return _entity;
    }

    double getTime() const {
	return _time;
    }

private:
    double _time;
    Entity* _entity;
    ModelComponent* _component;
};

/*!
 * Events related to simulation "process" (usually process analyser), associated to entire replication or simulation events (begin/end/pause of replication/simulation) 
 * TODO: CLASS NOT FULLY IMPLEMENTED (to be implemented for process analyser)
 */
class TraceSimulationProcess : public TraceEvent {
public:

    TraceSimulationProcess(Util::TraceLevel tracelevel, std::string text) : TraceEvent(tracelevel, text) {
    }
};

// for handlers that are simple functions
typedef void (*traceListener)(TraceEvent);
typedef void (*traceErrorListener)(TraceErrorEvent);
typedef void (*traceSimulationListener)(TraceSimulationEvent);
typedef void (*traceSimulationProcessListener)(TraceSimulationProcess);
// for handlers that are class members (methods)
typedef std::function<void(TraceEvent) > traceListenerMethod;
typedef std::function<void(TraceErrorEvent) > traceErrorListenerMethod;
typedef std::function<void(TraceSimulationEvent) > traceSimulationListenerMethod;
typedef std::function<void(TraceSimulationProcess) > traceSimulationProcessListenerMethod;

/*!
 * The TraceManager is used to trace back model simulation information and track/debug the simulation. 
 * It works as the model simulation output (cout) and allows external methods to hook up such output as listeners.
 */
class TraceManager {
public:
    TraceManager(Simulator* simulator); //(Model* model);
    TraceManager(const TraceManager& orig);
    virtual ~TraceManager();
public: // add trace handlers
    // for handlers that are simple functions
    void addTraceHandler(traceListener traceListener);
    void addTraceReportHandler(traceListener traceReportListener);
    void addTraceSimulationHandler(traceSimulationListener traceSimulationListener);
    void addTraceErrorHandler(traceErrorListener traceErrorListener);
    // for handlers that are class members (methods)
    template<typename Class> void addTraceHandler(Class * object, void (Class::*function)(TraceEvent));
    template<typename Class> void addTraceErrorHandler(Class * object, void (Class::*function)(TraceErrorEvent));
    template<typename Class> void addTraceReportHandler(Class * object, void (Class::*function)(TraceEvent));
    template<typename Class> void addTraceSimulationHandler(Class * object, void (Class::*function)(TraceSimulationEvent));
public: // traces (invoke trace handlers)
    void trace(Util::TraceLevel tracelevel, std::string text);
    void traceError(std::exception e, std::string text);
    void traceReport(Util::TraceLevel tracelevel, std::string text);
    void traceSimulation(Util::TraceLevel tracelevel, double time, Entity* entity, ModelComponent* component, std::string text);
public:
    List<std::string>* getErrorMessages() const;
    void setTraceLevel(Util::TraceLevel _traceLevel);
    Util::TraceLevel getTraceLevel() const;
    Simulator* getSimulator() const;
private:
    bool _traceConditionPassed(Util::TraceLevel level);
private: // trace listener
    // for handlers that are simple functions
    std::list<traceListener>* _traceHandlers = new std::list<traceListener>();
    std::list<traceErrorListener>* _traceErrorHandlers = new std::list<traceErrorListener>();
    std::list<traceListener>* _traceReportHandlers = new std::list<traceListener>();
    std::list<traceSimulationListener>* _traceSimulationHandlers = new std::list<traceSimulationListener>();
    // for handlers that are class members (methods)
    std::list<traceListenerMethod>* _traceHandlersMethod = new std::list<traceListenerMethod>();
    std::list<traceErrorListenerMethod>* _traceErrorHandlersMethod = new std::list<traceErrorListenerMethod>();
    std::list<traceListenerMethod>* _traceReportHandlersMethod = new std::list<traceListenerMethod>();
    std::list<traceSimulationListenerMethod>* _traceSimulationHandlersMethod = new std::list<traceSimulationListenerMethod>();
private:
    //Model* _model;
    Simulator* _simulator;
private:
    Util::TraceLevel _traceLevel; // = Util::TraceLevel::mostDetailed;
    bool _debugged;
    double _lastTimeTraceSimulation = -1.0;
    Util::identitifcation _lastEntityTraceSimulation = 0;
    Util::identitifcation _lastModuleTraceSimulation = 0;
    List<std::string>* _errorMessages; /* todo: 18/08/24 this is a new one. several methods should use it */

};

template<typename Class> void TraceManager::addTraceHandler(Class * object, void (Class::*function)(TraceEvent)) {
    this->_traceHandlersMethod->insert(_traceHandlersMethod->end(), std::bind(function, object, std::placeholders::_1));
}

template<typename Class> void TraceManager::addTraceErrorHandler(Class * object, void (Class::*function)(TraceErrorEvent)) {
    this->_traceErrorHandlersMethod->insert(_traceErrorHandlersMethod->end(), std::bind(function, object, std::placeholders::_1));
}

template<typename Class> void TraceManager::addTraceReportHandler(Class * object, void (Class::*function)(TraceEvent)) {
    this->_traceReportHandlersMethod->insert(_traceReportHandlersMethod->end(), std::bind(function, object, std::placeholders::_1));
}

template<typename Class> void TraceManager::addTraceSimulationHandler(Class * object, void (Class::*function)(TraceSimulationEvent)) {
    this->_traceSimulationHandlersMethod->insert(_traceSimulationHandlersMethod->end(), std::bind(function, object, std::placeholders::_1));
}

#endif /* TRACEMANAGER_H */

