/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MyReGenESYsApplication.h
 * Author: rafael.luiz.cancian
 *
 * Created on 20 de Maio de 2019, 21:01
 */

#ifndef BUILDSIMULATIONMODEL03_H
#define BUILDSIMULATIONMODEL03_H

#include "BaseConsoleGenesysApplication.h"

#include "Simulator.h"

class BuildSimulationModel03 : public BaseConsoleGenesysApplication {
public:
    BuildSimulationModel03();
    BuildSimulationModel03(const BuildSimulationModel03& orig);
    virtual ~BuildSimulationModel03();
public:
    virtual int main(int argc, char** argv);
private:
    void builAndRunSimulationdModel();
};

#endif /* BUILDSIMULATIONMODEL03_H */

