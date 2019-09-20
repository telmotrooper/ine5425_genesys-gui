/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatisticsDefaultImpl1.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 1 de Agosto de 2018, 21:03
 */

#include <complex>

#include "StatisticsDefaultImpl1.h"
#include "Traits.h"
#include "Integrator_if.h"
#include "ProbDistrib.h"

StatisticsDefaultImpl1::StatisticsDefaultImpl1() {
    _collector = new Traits<Statistics_if>::CollectorImplementation();
    _collector->setAddValueHandler(SetCollectorAddValueHandler(&StatisticsDefaultImpl1::collectorAddHandler, this));
    _collector->setClearHandler(SetCollectorClearHandler(&StatisticsDefaultImpl1::collectorClearHandler, this));
    //_collector->setAddValueHandler(std::bind(&StatisticsDefaultImpl1::collectorAddHandler, this, std::placeholders::_1));
    this->initStatistics();
}

StatisticsDefaultImpl1::StatisticsDefaultImpl1(Collector_if* collector) {
    _collector = collector;
    _collector->setAddValueHandler(SetCollectorAddValueHandler(&StatisticsDefaultImpl1::collectorAddHandler, this));
    _collector->setClearHandler(SetCollectorClearHandler(&StatisticsDefaultImpl1::collectorClearHandler, this));
    //_collector->setAddValueHandler(std::bind(&StatisticsDefaultImpl1::collectorAddHandler, this, std::placeholders::_1));
    this->initStatistics();
}

StatisticsDefaultImpl1::StatisticsDefaultImpl1(const StatisticsDefaultImpl1& orig) {
}

StatisticsDefaultImpl1::~StatisticsDefaultImpl1() {
}

void StatisticsDefaultImpl1::collectorAddHandler(double newValue) {
    _elems = _collector->numElements();
    if (newValue < _min) {
	_min = newValue;
    }
    if (newValue > _max) {
	_max = newValue;
    }
    _sum += newValue;
    _sumSquare += newValue*newValue;
    _average = _sum / _elems;
    _variance = _sumSquare / _elems - _average*_average;
    //_average = (_average * (elems - 1) + newValue) / elems;  // this approach propagates the numeric error
    //_variance = (_variance * (elems - 1) + pow(newValue - _average, 2)) / elems;  // this approach propagates the numeric error
    _stddeviation = sqrt(_variance);
    _variationCoef = (_stddeviation != 0 ? _stddeviation / _average : 0.0);
    _halfWidth = _criticalTn_1 * (_stddeviation / std::sqrt(_elems));
}

void StatisticsDefaultImpl1::collectorClearHandler() {
    this->initStatistics();
}

void StatisticsDefaultImpl1::initStatistics() {
    _elems = 0;
    _min = 1e+99;
    _max = -1e+99;
    _sum = 0.0;
    _sumSquare = 0.0;
    _average = 0.0;
    _variance = 0.0;
    _stddeviation = 0.0;
    _variationCoef = 0.0;
    _halfWidth = 0.0;
}

unsigned int StatisticsDefaultImpl1::numElements() {
    return this->getCollector()->numElements();
}

double StatisticsDefaultImpl1::min() {
    if (_elems > 0)
	return _min;
    else
	return 0.0;
}

double StatisticsDefaultImpl1::max() {
    if (_elems > 0)
	return _max;
    else
	return 0.0;
}

double StatisticsDefaultImpl1::average() {
    return _average;
}

double StatisticsDefaultImpl1::variance() {
    return _variance;
}

double StatisticsDefaultImpl1::stddeviation() {
    return _stddeviation;
}

double StatisticsDefaultImpl1::variationCoef() {
    return _variationCoef;
}

double StatisticsDefaultImpl1::halfWidthConfidenceInterval() {
    return _halfWidth;
}

void StatisticsDefaultImpl1::setConfidenceLevel(double confidencelevel) {
    _confidenceLevel = confidencelevel;
    //Integrator_if* integrator = new Traits<Integrator_if>::Implementation();
    _criticalTn_1 = 1.96; //integrator->integrate()

}

double StatisticsDefaultImpl1::getConfidenceLevel() {
    return _confidenceLevel;
}

unsigned int StatisticsDefaultImpl1::newSampleSize(double halfWidth) {
    return 0;
}

Collector_if* StatisticsDefaultImpl1::getCollector() {
    return this->_collector;
}

void StatisticsDefaultImpl1::setCollector(Collector_if* collector) {
    this->_collector = collector;
}