/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "TestInputAnalyserTools.h"
#include "Simulator.h"
#include "Sampler_if.h"
#include "ProbDistrib.h"
#include "Traits.h"

void testStudentSoftwareDevelopments() {
    Simulator* simulator = new Simulator();
    Sampler_if* mmc = simulator->getToolManager()->getSampler(); // Sampler is the new MMC
    CollectorDatafile_if* collector = (new Traits<Collector_if>::Implementation());
    collector->setDataFilename("./datafile.txt");
    // just to show how to change MMC parameters
    Traits<Sampler_if>::Parameters* parameters = (Traits<Sampler_if>::Parameters*) mmc->getRNGparameters();
    parameters->module = 2147483648;
    parameters->multiplier = 1103515245;
    parameters->seed = 1234;
    mmc->setRNGparameters(parameters);

    // generate a datafile with a thousand values that should be normal distributed == NORM(5000,350)
    double value;
    for (unsigned int i = 0; i < 1e3; i++) {
	value = mmc->sampleNormal(5000, 350);
	value = mmc->sampleBeta(2, 4, 1000, 2000);
	value = mmc->sampleErlang(1000, 10);
	value = mmc->sampleGamma(1000, 2);
	value = mmc->sampleTriangular(1000, 1900, 2000);
	value = mmc->sampleWeibull(1000, 1);
	collector->addValue(value);
    }

    // generate statistics about that datafile 
    Statistics_if* statistics = new Traits<Statistics_if>::Implementation();
    statistics->setCollector(collector); //setDataFilename(collector->getDataFilename());
    double statVal;
    statVal = statistics->numElements();
    statVal = statistics->average();
    statVal = statistics->stddeviation();
    statVal = statistics->halfWidthConfidenceInterval();
    /*
	    statVal = statistics->quartil(2);
	    statVal = statistics->mediane();
	    unsigned int numclasses = statistics->histogramNumClasses();
	    for (unsigned int i = 0; i < numclasses; i++) {
		    statVal = statistics->histogramClassFrequency(i);
		    statVal = statistics->histogramClassLowerLimit(i);
	    }
     */
    // fit datafile to different probability distributions
    Fitter_if* fitter = simulator->getToolManager()->getFitter();
    fitter->setDataFilename(collector->getDataFilename());
    double sqrerror, p1, p2, p3; //, p4;
    std::string distribName;
    bool res;
    res = fitter->isNormalDistributed(0.95);
    fitter->fitUniform(&sqrerror, &p1, &p2);
    fitter->fitTriangular(&sqrerror, &p1, &p2, &p3);
    fitter->fitNormal(&sqrerror, &p1, &p2);
    fitter->fitAll(&sqrerror, &distribName);

    // get some values from the PDF (Probability Density Functions)
    value = ProbDistrib::uniform(0.25, 0.0, 1.0);
    value = ProbDistrib::uniform(0.5, 0.0, 1.0); // should return the same value than above
    value = ProbDistrib::uniform(0.75, 0.0, 1.0); // should return the same value than above
    value = ProbDistrib::normal(10.0, 50.0, 20.0);
    value = ProbDistrib::normal(30.0, 50.0, 20.0); // should return a greater value than above
    value = ProbDistrib::normal(50.0, 50.0, 20.0); // should return a greater value than above

    // calculate some integrals just for fun
    Integrator_if* integrator = new Traits<Integrator_if>::Implementation();
    value = integrator->integrate(0.0, 0.4, &ProbDistrib::uniform, 0.0, 0.1); // should return 0.4
    value = integrator->integrate(0.0, 100, &ProbDistrib::normal, 100, 10); // should return 0.5

    // Test some hypothesis about the datafile
    HypothesisTester_if* tester = new Traits<HypothesisTester_if>::Implementation();
    tester->setDataFilename(collector->getDataFilename());
    res = tester->testAverage(0.95, 5500, HypothesisTester_if::GREATER_THAN);
    res = tester->testAverage(0.95, 4500, HypothesisTester_if::LESS_THAN);
    res = tester->testAverage(0.95, 5100, HypothesisTester_if::DIFFERENT);
    res = tester->testVariance(0.95, 350 * 350, HypothesisTester_if::LESS_THAN);

}

TestInputAnalyserTools::TestInputAnalyserTools() {

}

int TestInputAnalyserTools::main(int argc, char** argv) {
    testStudentSoftwareDevelopments();
    return 0;
}