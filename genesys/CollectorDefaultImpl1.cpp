/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CollectorDefaultImpl1.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 1 de Agosto de 2018, 20:43
 */

#include "CollectorDefaultImpl1.h"

CollectorDefaultImpl1::CollectorDefaultImpl1() {
}

CollectorDefaultImpl1::CollectorDefaultImpl1(const CollectorDefaultImpl1& orig) {
}

CollectorDefaultImpl1::~CollectorDefaultImpl1() {
}

void CollectorDefaultImpl1::clear() {
    _numElements = 0;
    if (_clearHandler != nullptr) {
	_clearHandler();
    }
}

void CollectorDefaultImpl1::addValue(double value) {
    _lastValue = value;
    _numElements++;
    if (_addValueHandler != nullptr) {
	_addValueHandler(value);
    }
}

double CollectorDefaultImpl1::getLastValue() {
    return this->_lastValue;
}

unsigned long CollectorDefaultImpl1::numElements() {
    return this->_numElements;
}

void CollectorDefaultImpl1::setAddValueHandler(CollectorAddValueHandler addValueHandler) {
    _addValueHandler = addValueHandler;
}

void CollectorDefaultImpl1::setClearHandler(CollectorClearHandler clearHandler) {
    _clearHandler = clearHandler;
}