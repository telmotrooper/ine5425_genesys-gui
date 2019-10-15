/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimulatorWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 14, 2019, 11:21 PM
 */

#ifndef SIMULATOR_WRAPPER_H
#define SIMULATOR_WRAPPER_H

#include "../Simulator.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initSimulator(py::module &m) {
    py::class_<Simulator>(m, "Simulator")
        .def(py::init())
        .def("getVersion", &Simulator::getVersion)
        .def("getName", &Simulator::getName)
        .def("getLicenceManager", &Simulator::getLicenceManager) 
        .def("getPluginManager", &Simulator::getPluginManager) 
        .def("getModelManager", &Simulator::getModelManager) 
        .def("getToolManager", &Simulator::getToolManager) 
        .def("getTraceManager", &Simulator::getTraceManager) 
        .def("getParserManager", &Simulator::getParserManager);
}

#endif /* SIMULATOR_WRAPPER_H */

