/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatisticsDummyImpl.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 23 de Agosto de 2018, 16:52
 */

#include "StatisticsDummyImpl.h"
#include "Traits.h"

StatisticsDummyImpl::StatisticsDummyImpl() {
    _collector = new Traits<Statistics_if>::CollectorImplementation();
    _collector->setAddValueHandler(SetCollectorAddValueHandler(&StatisticsDummyImpl::collectorAddHandler, this));
    _collector->setClearHandler(SetCollectorClearHandler(&StatisticsDummyImpl::collectorClearHandler, this));
    //_collector->setAddValueHandler(std::bind(&StatisticsDummyImpl::collectorAddHandler, this, std::placeholders::_1));
}

StatisticsDummyImpl::StatisticsDummyImpl(const StatisticsDummyImpl& orig) {
}

StatisticsDummyImpl::~StatisticsDummyImpl() {
}

void StatisticsDummyImpl::collectorAddHandler(double newValue) {
}

void StatisticsDummyImpl::collectorClearHandler() {
}

unsigned int StatisticsDummyImpl::numElements() {
}

double StatisticsDummyImpl::min() {
}

double StatisticsDummyImpl::max() {
}

double StatisticsDummyImpl::average() {
}

double StatisticsDummyImpl::variance() {
}

double StatisticsDummyImpl::stddeviation() {
}

double StatisticsDummyImpl::variationCoef() {
}

double StatisticsDummyImpl::halfWidthConfidenceInterval() {
}

unsigned int StatisticsDummyImpl::newSampleSize(double halfWidth) {
}

void StatisticsDummyImpl::setConfidenceLevel(double confidencelevel) {

}

double StatisticsDummyImpl::getConfidenceLevel() {

}

Collector_if* StatisticsDummyImpl::getCollector() {
    return this->_collector;
}

void StatisticsDummyImpl::setCollector(Collector_if* collector) {

}