/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FitterDefaultImpl1.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 20 de Maio de 2019, 20:48
 */

#include "FitterDefaultImpl1.h"

FitterDefaultImpl1::FitterDefaultImpl1() {
}

FitterDefaultImpl1::FitterDefaultImpl1(const FitterDefaultImpl1& orig) {
}

FitterDefaultImpl1::~FitterDefaultImpl1() {
}

bool FitterDefaultImpl1::isNormalDistributed(double confidencelevel) {
    return true;
}

void FitterDefaultImpl1::fitUniform(double *sqrerror, double *min, double *max) {

}

void FitterDefaultImpl1::fitTriangular(double *sqrerror, double *min, double *mo, double *max) {

}

void FitterDefaultImpl1::fitNormal(double *sqrerror, double *avg, double *stddev) {

}

void FitterDefaultImpl1::fitExpo(double *sqrerror, double *avg1) {
}

void FitterDefaultImpl1::fitErlang(double *sqrerror, double *avg, double *m) {

}

void FitterDefaultImpl1::fitBeta(double *sqrerror, double *alpha, double *beta, double *infLimit, double *supLimit) {

}

void FitterDefaultImpl1::fitWeibull(double *sqrerror, double *alpha, double *scale) {

}

void FitterDefaultImpl1::fitAll(double *sqrerror, std::string *name) {

}

void FitterDefaultImpl1::setDataFilename(std::string dataFilename) {

}

std::string FitterDefaultImpl1::getDataFilename() {
    return ""; //todo
}
