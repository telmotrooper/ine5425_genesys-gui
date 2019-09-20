/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LinkedBy.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 22 de Agosto de 2018, 07:35
 */

#include "LinkedBy.h"

LinkedBy::LinkedBy() {
}

LinkedBy::LinkedBy(const LinkedBy& orig) {
}

LinkedBy::~LinkedBy() {
}

void LinkedBy::addLink() {
    this->_linkedBy++;
}

void LinkedBy::removeLink() {
    this->_linkedBy--;
}

bool LinkedBy::isLinked() {
    return this->_linkedBy > 0;
}