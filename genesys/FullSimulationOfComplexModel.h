/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   buildSimpleModel1.h
 * Author: rafael.luiz.cancian
 *
 * Created on 2 de Outubro de 2018, 19:18
 */

#ifndef BUILDSIMULATIONMODEL02_H
#define BUILDSIMULATIONMODEL02_H

#include "BaseConsoleGenesysApplication.h"
#include "Model.h"

class FullSimulationOfComplexModel: public BaseConsoleGenesysApplication {
public:
    FullSimulationOfComplexModel();
public:
    virtual int main(int argc, char** argv);
};

#endif /* BUILDSIMULATIONMODEL02_H */

