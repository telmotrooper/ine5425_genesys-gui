/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestSimulationControlAndSimulationResponse.h
 * Author: rlcancian
 *
 * Created on 11 de Setembro de 2019, 17:44
 */

#ifndef TESTSIMULATIONCONTROLANDSIMULATIONRESPONSE_H
#define TESTSIMULATIONCONTROLANDSIMULATIONRESPONSE_H

#include "BaseConsoleGenesysApplication.h"

class TestSimulationControlAndSimulationResponse: public BaseConsoleGenesysApplication {
public:
    TestSimulationControlAndSimulationResponse();
    TestSimulationControlAndSimulationResponse(const TestSimulationControlAndSimulationResponse& orig);
    virtual ~TestSimulationControlAndSimulationResponse();
public:
    virtual int main(int argc, char** argv);
private:

};

#endif /* TESTSIMULATIONCONTROLANDSIMULATIONRESPONSE_H */

