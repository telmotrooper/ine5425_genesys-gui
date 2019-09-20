/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IntegratorDummyImpl.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 23 de Agosto de 2018, 17:28
 */

#include "IntegratorDummyImpl.h"

IntegratorDummyImpl::IntegratorDummyImpl() {
}

IntegratorDummyImpl::IntegratorDummyImpl(const IntegratorDummyImpl& orig) {
}

IntegratorDummyImpl::~IntegratorDummyImpl() {
}

void IntegratorDummyImpl::setPrecision(double e) {
    _precision = e;
}

double IntegratorDummyImpl::getPrecision() {
    return _precision;
}

double IntegratorDummyImpl::integrate(double min, double max, double (*f)(double, double), double p2) {
}

double IntegratorDummyImpl::integrate(double min, double max, double (*f)(double, double, double), double p2, double p3) {
}

double IntegratorDummyImpl::integrate(double min, double max, double (*f)(double, double, double, double), double p2, double p3, double p4) {
}

double IntegratorDummyImpl::integrate(double min, double max, double (*f)(double, double, double, double, double), double p2, double p3, double p4, double p5) {
}