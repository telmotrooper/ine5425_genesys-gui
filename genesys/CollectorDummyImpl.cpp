/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CollectorDummyImpl.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 14 de Agosto de 2018, 19:43
 */

#include "CollectorDummyImpl.h"

CollectorDummyImpl::CollectorDummyImpl() {
}

CollectorDummyImpl::CollectorDummyImpl(const CollectorDummyImpl& orig) {
}

CollectorDummyImpl::~CollectorDummyImpl() {
}

void CollectorDummyImpl::clear() {
    _numElements = 0;
    if (_clearHandler != nullptr) {
	_clearHandler();
    }
}

void CollectorDummyImpl::addValue(double value) {
    _lastValue = value;
    _numElements++;
    if (_addValueHandler != nullptr) {
	_addValueHandler(value);
    }
}

double CollectorDummyImpl::getLastValue() {
    return this->_lastValue;
}

unsigned long CollectorDummyImpl::numElements() {
    return this->_numElements;
}

void CollectorDummyImpl::setAddValueHandler(CollectorAddValueHandler addValueHandler) {
    _addValueHandler = addValueHandler;
}

void CollectorDummyImpl::setClearHandler(CollectorClearHandler clearHandler) {
    _clearHandler = clearHandler;
}