/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatisticsDataFileDummyImpl.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 22 de Novembro de 2018, 01:24
 */

#include "StatisticsDataFileDummyImpl.h"

#include "Traits.h"

StatisticsDataFileDummyImpl::StatisticsDataFileDummyImpl() {
    _collector = new Traits<Statistics_if>::CollectorImplementation();
}

StatisticsDataFileDummyImpl::StatisticsDataFileDummyImpl(const StatisticsDataFileDummyImpl& orig) {
}

StatisticsDataFileDummyImpl::~StatisticsDataFileDummyImpl() {
}

unsigned int StatisticsDataFileDummyImpl::numElements() {
}

double StatisticsDataFileDummyImpl::min() {
}

double StatisticsDataFileDummyImpl::max() {
}

double StatisticsDataFileDummyImpl::average() {
}

double StatisticsDataFileDummyImpl::mode() {
}

double StatisticsDataFileDummyImpl::mediane() {
}

double StatisticsDataFileDummyImpl::variance() {
}

double StatisticsDataFileDummyImpl::stddeviation() {
}

double StatisticsDataFileDummyImpl::variationCoef() {
}

double StatisticsDataFileDummyImpl::halfWidthConfidenceInterval(double confidencelevel) {
}

unsigned int StatisticsDataFileDummyImpl::newSampleSize(double confidencelevel, double halfWidth) {
}

double StatisticsDataFileDummyImpl::quartil(unsigned short num) {
}

double StatisticsDataFileDummyImpl::decil(unsigned short num) {
}

double StatisticsDataFileDummyImpl::centil(unsigned short num) {
}

void StatisticsDataFileDummyImpl::setHistogramNumClasses(unsigned short num) {
}

unsigned short StatisticsDataFileDummyImpl::histogramNumClasses() {
    return 1;
}

double StatisticsDataFileDummyImpl::histogramClassLowerLimit(unsigned short classNum) {
}

unsigned int StatisticsDataFileDummyImpl::histogramClassFrequency(unsigned short classNum) {
}

Collector_if* StatisticsDataFileDummyImpl::getCollector() {
    return this->_collector;
}

void StatisticsDataFileDummyImpl::setCollector(Collector_if* collector) {

}