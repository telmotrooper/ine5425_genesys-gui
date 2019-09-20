/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProcessAnalyserDummyImpl.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 10 de Outubro de 2018, 18:27
 */

#include "ProcessAnalyserDummyImpl.h"

ProcessAnalyserDummyImpl::ProcessAnalyserDummyImpl() {
}

ProcessAnalyserDummyImpl::ProcessAnalyserDummyImpl(const ProcessAnalyserDummyImpl& orig) {
}

ProcessAnalyserDummyImpl::~ProcessAnalyserDummyImpl() {
}

List<SimulationScenario*>* ProcessAnalyserDummyImpl::getScenarios() const {
}

List<SimulationControl*>* ProcessAnalyserDummyImpl::getControls() const {
    return _controls;
}

List<SimulationResponse*>* ProcessAnalyserDummyImpl::getResponses() const {
}

List<SimulationControl*>* ProcessAnalyserDummyImpl::extractControlsFromModel(std::string modelFilename) const {
}

List<SimulationResponse*>* ProcessAnalyserDummyImpl::extractResponsesFromModel(std::string modelFilename) const {
}

void ProcessAnalyserDummyImpl::startSimulationOfScenario(SimulationScenario* scenario) {
}

void ProcessAnalyserDummyImpl::startSimulation() {
}

void ProcessAnalyserDummyImpl::stopSimulation() {
}

void ProcessAnalyserDummyImpl::addTraceSimulationHandler(traceSimulationProcessListener traceSimulationProcessListener) {
}