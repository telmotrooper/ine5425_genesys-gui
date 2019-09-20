/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ProcessAnalyserDefaultImpl1.cpp
 * Author: rlcancian
 * 
 * Created on 20 de Maio de 2019, 20:45
 */

#include "ProcessAnalyserDefaultImpl1.h"

ProcessAnalyserDefaultImpl1::ProcessAnalyserDefaultImpl1() {
}

ProcessAnalyserDefaultImpl1::ProcessAnalyserDefaultImpl1(const ProcessAnalyserDefaultImpl1& orig) {
}

ProcessAnalyserDefaultImpl1::~ProcessAnalyserDefaultImpl1() {
}

List<SimulationScenario*>* ProcessAnalyserDefaultImpl1::getScenarios() const {
}

List<SimulationControl*>* ProcessAnalyserDefaultImpl1::getControls() const {
    return _controls;
}

List<SimulationResponse*>* ProcessAnalyserDefaultImpl1::getResponses() const {
}

List<SimulationControl*>* ProcessAnalyserDefaultImpl1::extractControlsFromModel(std::string modelFilename) const {
}

List<SimulationResponse*>* ProcessAnalyserDefaultImpl1::extractResponsesFromModel(std::string modelFilename) const {
}

void ProcessAnalyserDefaultImpl1::startSimulationOfScenario(SimulationScenario* scenario) {
}

void ProcessAnalyserDefaultImpl1::startSimulation() {
}

void ProcessAnalyserDefaultImpl1::stopSimulation() {
}

void ProcessAnalyserDefaultImpl1::addTraceSimulationHandler(traceSimulationProcessListener traceSimulationProcessListener) {
}