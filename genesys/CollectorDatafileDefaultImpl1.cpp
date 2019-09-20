/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CollectorDatafileDefaultImpl11.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 1 de Agosto de 2018, 20:58
 */

#include "CollectorDatafileDefaultImpl1.h"

CollectorDatafileDefaultImpl1::CollectorDatafileDefaultImpl1() {
}

CollectorDatafileDefaultImpl1::CollectorDatafileDefaultImpl1(const CollectorDatafileDefaultImpl1& orig) {
}

CollectorDatafileDefaultImpl1::~CollectorDatafileDefaultImpl1() {
}

void CollectorDatafileDefaultImpl1::clear() {
}

void CollectorDatafileDefaultImpl1::addValue(double value) {
}

double CollectorDatafileDefaultImpl1::getLastValue() {
    return 0.0; //TODO
}

unsigned long CollectorDatafileDefaultImpl1::numElements() {
    return 0.0; //TODO
}

double CollectorDatafileDefaultImpl1::getValue(unsigned int num) {
    return 0.0; //TODO
}

double CollectorDatafileDefaultImpl1::getNextValue() {
    return 0.0; //TODO
}

void CollectorDatafileDefaultImpl1::seekFirstValue() {
}

std::string CollectorDatafileDefaultImpl1::getDataFilename() {
    return _filename;
}

void CollectorDatafileDefaultImpl1::setDataFilename(std::string filename) {
    _filename = filename;
}

void CollectorDatafileDefaultImpl1::setAddValueHandler(CollectorAddValueHandler addValueHandler) {

}

void CollectorDatafileDefaultImpl1::setClearHandler(CollectorClearHandler clearHandler) {

}