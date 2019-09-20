/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParserDefaultImpl1.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 2 de Agosto de 2018, 01:25
 */

#include "ParserDefaultImpl1.h"

ParserDefaultImpl1::ParserDefaultImpl1(Model* model) {
    _model = model;
}

ParserDefaultImpl1::ParserDefaultImpl1(const ParserDefaultImpl1& orig) {
}

ParserDefaultImpl1::~ParserDefaultImpl1() {
}

double ParserDefaultImpl1::parse(const std::string expression) { // may throw exception
    double result = std::atof(expression.c_str()); // change by a real parser
    return result;
}

std::string* ParserDefaultImpl1::getErrorMessage() {
    std::string* errorMsg = new std::string();
    return errorMsg; /* @TODO */
}

double ParserDefaultImpl1::parse(const std::string expression, bool* success, std::string* errorMessage) {
    try {
	double result = this->parse(expression);
	std::string temp(""); /* TODO: CHECK SCOPE OF VARIABLE */
	errorMessage = &temp;
	*success = true;
	return result;
    } catch (...) {
	std::string temp("Error parsing...");
	errorMessage = &temp;
	*success = false;
	return 0.0;
    }
}

