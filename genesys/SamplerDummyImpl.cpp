/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SamplerDummyImpl.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 23 de Agosto de 2018, 13:08
 */

#include "SamplerDummyImpl.h"
#include <iostream> //remove
#include <cmath>

SamplerDummyImpl::SamplerDummyImpl() {
}

SamplerDummyImpl::SamplerDummyImpl(const SamplerDummyImpl& orig) {
}

SamplerDummyImpl::~SamplerDummyImpl() {
}

double SamplerDummyImpl::random() {
}

double SamplerDummyImpl::sampleUniform(double min, double max) {
}

double SamplerDummyImpl::sampleExponential(double mean) {
}

double SamplerDummyImpl::sampleErlang(double mean, int M) {
}

double SamplerDummyImpl::sampleNormal(double mean, double stddev) {
    return 21;
}

double SamplerDummyImpl::sampleGamma(double mean, double alpha) {
}

double SamplerDummyImpl::sampleBeta(double alpha, double beta, double infLimit, double supLimit) {
}

double SamplerDummyImpl::sampleWeibull(double alpha, double scale) {
}

double SamplerDummyImpl::sampleLogNormal(double mean, double stddev) {
}

double SamplerDummyImpl::sampleTriangular(double min, double mode, double max) {
}

double SamplerDummyImpl::sampleDiscrete(double value, double acumProb, ...) {
}

void SamplerDummyImpl::setRNGparameters(Sampler_if::RNG_Parameters* param) {
    _param = dynamic_cast<MyRNG_Parameters*> (param);
}

Sampler_if::RNG_Parameters* SamplerDummyImpl::getRNGparameters() const {
    return _param;
}
