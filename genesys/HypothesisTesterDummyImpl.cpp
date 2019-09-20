/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HypothesisTester.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 7 de Agosto de 2018, 19:03
 */

#include "HypothesisTesterDummyImpl.h"

HypothesisTesterDummyImpl::HypothesisTesterDummyImpl() {
}

HypothesisTesterDummyImpl::HypothesisTesterDummyImpl(const HypothesisTesterDummyImpl& orig) {
}

HypothesisTesterDummyImpl::~HypothesisTesterDummyImpl() {
}

double HypothesisTesterDummyImpl::testAverage(double confidencelevel, double avg, H1Comparition comp) {
}

double HypothesisTesterDummyImpl::testProportion(double confidencelevel, double prop, H1Comparition comp) {
}

double HypothesisTesterDummyImpl::testVariance(double confidencelevel, double var, H1Comparition comp) {
}

double HypothesisTesterDummyImpl::testAverage(double confidencelevel, std::string secondPopulationDataFilename, H1Comparition comp) {
}

double HypothesisTesterDummyImpl::testProportion(double confidencelevel, std::string secondPopulationDataFilename, H1Comparition comp) {
}

double HypothesisTesterDummyImpl::testVariance(double confidencelevel, std::string secondPopulationDataFilename, H1Comparition comp) {
}

void HypothesisTesterDummyImpl::setDataFilename(std::string dataFilename) {
}

std::string HypothesisTesterDummyImpl::getDataFilename() {
}