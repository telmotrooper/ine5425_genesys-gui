/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FactorOrInteractionContribution.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 10 de Outubro de 2018, 20:08
 */

#include "FactorOrInteractionContribution.h"

FactorOrInteractionContribution::FactorOrInteractionContribution(double contribution, double modelCoefficient, std::list<SimulationControl*>* controls) {
    _contribution = contribution;
    _modelCoefficient = modelCoefficient;
    _controls = controls;
}

FactorOrInteractionContribution::FactorOrInteractionContribution(const FactorOrInteractionContribution& orig) {
}

FactorOrInteractionContribution::~FactorOrInteractionContribution() {
}

double FactorOrInteractionContribution::getModelCoefficient() const {
    return _modelCoefficient;
}

std::list<SimulationControl*>* FactorOrInteractionContribution::getControls() const {
    return _controls;
}

double FactorOrInteractionContribution::getContribution() const {
    return _contribution;
}
