/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ParserDefaultImpl2.cpp
 * Author: Joao Ortigara rafael.luiz.cancian (20181208-...(
 *
 *
 */

#include "ParserDefaultImpl2.h"

ParserDefaultImpl2::ParserDefaultImpl2(Model* model) {
    _model = model;
    _wrapper = genesyspp_driver(_model, false);
}

ParserDefaultImpl2::ParserDefaultImpl2(Model* model, bool throws) {
    _model = model;
    _wrapper = genesyspp_driver(_model, throws);
}

ParserDefaultImpl2::ParserDefaultImpl2(const ParserDefaultImpl2& orig) {
}

ParserDefaultImpl2::~ParserDefaultImpl2() {
}

double ParserDefaultImpl2::parse(const std::string expression) { // may throw exception
    _wrapper.setThrowsException(true);
    try {
	int res = _wrapper.parse_str(expression);
	if (res == 0) {
	    return _wrapper.getResult();
	} else {
	    throw std::string("Error parsing expression \"" + expression + "\"");
	}
    } catch (std::string e) {
	_model->getTraceManager()->trace(Util::TraceLevel::errors, e);
	return _wrapper.getResult();
    }
}

std::string* ParserDefaultImpl2::getErrorMessage() {
    std::string* errorMessage = new std::string(_wrapper.getErrorMessage());
    return errorMessage;
}

double ParserDefaultImpl2::parse(const std::string expression, bool* success, std::string* errorMessage) {
    _wrapper.setThrowsException(false);
    int res = _wrapper.parse_str(expression);
    if (res == 0) {
	*success = true;
	return _wrapper.getResult();
    } else {
	*success = false;
	*errorMessage = _wrapper.getErrorMessage();
	return _wrapper.getResult();
    }
}
