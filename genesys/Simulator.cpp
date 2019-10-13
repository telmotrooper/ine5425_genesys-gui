/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Genesys.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 21 de Junho de 2018, 12:48
 */

#include "Simulator.h"
#include "LicenceManager.h"
#include "ToolManager.h"

Simulator::Simulator() {
    // This is the ONLY method in the entire software where std::cout is allowed.
    std::cout << "RUNNING " << _name << ", version " << _version << std::endl;
    _licenceManager = new LicenceManager(this);
    _pluginManager = new PluginManager(this);
    _modelManager = new ModelManager(this);
    _toolManager = new ToolManager(this);
    _traceManager = new TraceManager(this);
    std::cout << _licenceManager->showLicence() << std::endl;
    std::cout << _licenceManager->showActivationCode() << std::endl;
    std::cout << _licenceManager->showLimits() << std::endl;
}

PluginManager* Simulator::getPluginManager() const {
    return _pluginManager;
}

ModelManager* Simulator::getModelManager() const {
    return _modelManager;
}

ToolManager* Simulator::getToolManager() const {
    return _toolManager;
}

TraceManager* Simulator::getTraceManager() const {
    return _traceManager;
}

ParserManager* Simulator::getParserManager() const {
    return _parserManager;
}

Simulator::Simulator(const Simulator& orig) {
}

Simulator::~Simulator() {
}

std::string Simulator::getVersion() const {
    return _version;
}

std::string Simulator::getName() const {
    return _name;
}

LicenceManager* Simulator::getLicenceManager() const {
    return _licenceManager;
}

