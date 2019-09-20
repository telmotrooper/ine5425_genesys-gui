/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SamplerDefaultImpl1.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 2 de Agosto de 2018, 01:10
 */

#include <cmath>
#include <complex>

#include "SamplerDefaultImpl1.h"

SamplerDefaultImpl1::SamplerDefaultImpl1() {
    reset();
}

void SamplerDefaultImpl1::reset() {
    _seed = static_cast<DefaultImpl1RNG_Parameters*> (_param)->seed;
    //_normalflag = true;
}

SamplerDefaultImpl1::SamplerDefaultImpl1(const SamplerDefaultImpl1& orig) {
}

SamplerDefaultImpl1::~SamplerDefaultImpl1() {
}

double SamplerDefaultImpl1::random() {
    double module = (double) static_cast<DefaultImpl1RNG_Parameters*> (_param)->module;
    _seed *= static_cast<DefaultImpl1RNG_Parameters*> (_param)->multiplier;
    _seed -= std::trunc((double) _seed / module) * module;
    return (double) _seed / (double) static_cast<DefaultImpl1RNG_Parameters*> (_param)->module;
}

double SamplerDefaultImpl1::sampleUniform(double min, double max) {
    return min + (max - min) * random();
}

double SamplerDefaultImpl1::sampleExponential(double mean) {
    return mean * (-std::log(random()));
}

double SamplerDefaultImpl1::sampleErlang(double mean, int M) {
}

double SamplerDefaultImpl1::sampleNormal(double mean, double stddev) {
    double z = std::sqrt(-2 * std::log(random())) * std::cos(2 * M_PI * random());
    return mean + stddev*z;
}

double SamplerDefaultImpl1::sampleGamma(double mean, double alpha) {
}

double SamplerDefaultImpl1::sampleBeta(double alpha, double beta, double infLimit, double supLimit) {
}

double SamplerDefaultImpl1::sampleWeibull(double alpha, double scale) {
}

double SamplerDefaultImpl1::sampleLogNormal(double mean, double stddev) {
}

double SamplerDefaultImpl1::sampleTriangular(double min, double mode, double max) {
}

double SamplerDefaultImpl1::sampleDiscrete(double value, double acumProb, ...) {
}

void SamplerDefaultImpl1::setRNGparameters(Sampler_if::RNG_Parameters* param) {
    _param = param; // there is a better solution for this...
}

Sampler_if::RNG_Parameters* SamplerDefaultImpl1::getRNGparameters() const {
    return _param;
}
