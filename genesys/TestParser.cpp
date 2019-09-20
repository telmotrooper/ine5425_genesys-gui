/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestParser.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 7 de Novembro de 2018, 20:17
 */

#include "TestParser.h"
#include <string>
#include "Model.h"
#include "Simulator.h"

TestParser::TestParser() {
}

TestParser::TestParser(const TestParser& orig) {
}

TestParser::~TestParser() {
}

int TestParser::main(int argc, char** argv) {
    Simulator* simulator = new Simulator();
    Model* model = new Model(simulator);
    simulator->getModelManager()->insert(model);
    double value;
    bool success;
    std::string errorMsg = "";
    value = model->parseExpression("NORM(20,10)", &success, &errorMsg);
    std::cout << value << std::endl;
    value = model->parseExpression("-10+1+2+3", &success, &errorMsg);
    std::cout << value << std::endl;
    value = model->parseExpression("1+2+3-10", &success, &errorMsg);
    std::cout << value << std::endl;
}