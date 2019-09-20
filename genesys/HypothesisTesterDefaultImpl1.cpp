/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HypothesisTesterDefaultImpl1.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 10 de Agosto de 2018, 10:27
 */

#include "HypothesisTesterDefaultImpl1.h"
#include "Traits.h"

HypothesisTesterDefaultImpl1::HypothesisTesterDefaultImpl1() {
    _integrator = new Traits<HypothesisTester_if>::IntegratorImplementation();
}

HypothesisTesterDefaultImpl1::HypothesisTesterDefaultImpl1(const HypothesisTesterDefaultImpl1& orig) {
}

HypothesisTesterDefaultImpl1::~HypothesisTesterDefaultImpl1() {
}

double HypothesisTesterDefaultImpl1::testAverage(double confidencelevel, double avg, H1Comparition comp) {
    return 0.0; //todo
}

double HypothesisTesterDefaultImpl1::testProportion(double confidencelevel, double prop, H1Comparition comp) {
    return 0.0; //todo
}

double HypothesisTesterDefaultImpl1::testVariance(double confidencelevel, double var, H1Comparition comp) {
    return 0.0; //todo
}

double HypothesisTesterDefaultImpl1::testAverage(double confidencelevel, std::string secondPopulationDataFilename, H1Comparition comp) {
    return 0.0; //todo
}

double HypothesisTesterDefaultImpl1::testProportion(double confidencelevel, std::string secondPopulationDataFilename, H1Comparition comp) {
    return 0.0; //todo
}

double HypothesisTesterDefaultImpl1::testVariance(double confidencelevel, std::string secondPopulationDataFilename, H1Comparition comp) {
    return 0.0; //todo
}

void HypothesisTesterDefaultImpl1::setDataFilename(std::string dataFilename) {
}

std::string HypothesisTesterDefaultImpl1::getDataFilename() {
    return ""; //todo
}
