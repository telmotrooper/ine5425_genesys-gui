/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExperimentDesignDefaultImpl1.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 10 de Agosto de 2018, 10:19
 */

#include "ExperimentDesignDefaultImpl1.h"

ExperimentDesignDefaultImpl1::ExperimentDesignDefaultImpl1() {
}

ExperimentDesignDefaultImpl1::ExperimentDesignDefaultImpl1(const ExperimentDesignDefaultImpl1& orig) {
}

ExperimentDesignDefaultImpl1::~ExperimentDesignDefaultImpl1() {
}

std::list<FactorOrInteractionContribution*>* ExperimentDesignDefaultImpl1::getContributions() const {
    return _contributions;
}

bool ExperimentDesignDefaultImpl1::generate2krScenarioExperiments() {
    return true;
}

bool ExperimentDesignDefaultImpl1::calculateContributionAndCoefficients() {
    return true;
}

ProcessAnalyser_if* ExperimentDesignDefaultImpl1::getProcessAnalyser() const {
    return _processAnalyser;
}



