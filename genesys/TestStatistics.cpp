/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TestStatistics.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 30 de Agosto de 2018, 19:28
 */

#include "TestStatistics.h"
#include <fstream>
#include <iostream>

#include "Traits.h"

TestStatistics::TestStatistics() {
}

int TestStatistics::main(int argc, char** argv) {
    Statistics_if* stat = new Traits<Statistics_if>::Implementation();
    std::ifstream datafile;
    datafile.open("datafileLarge.dat");
    //double value;
    //while (datafile >> value) {
    //    stat->getCollector()->addValue(value);
    //}
    stat->getCollector()->addValue(1001);
    stat->getCollector()->addValue(1002);
    stat->getCollector()->addValue(1007);
    std::cout << "Elems\t" << "Average\t" << "StdDev\t" << "CoefVar\t" << "Min\t" << "Max\t" << std::endl;
    std::cout << stat->numElements() << "\t"
	    << stat->average() << "\t"
	    << stat->stddeviation() << "\t"
	    << stat->variationCoef() << "\t"
	    << stat->min() << "\t"
	    << stat->max() << "\t"
	    << std::endl;
    //datafile.close();
    return 0;
}

