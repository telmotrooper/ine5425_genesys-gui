/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wrapper.h
 * Author: Telmo "Trooper"
 *
 * Created on October 12, 2019, 9:53 PM
 */

#ifndef WRAPPERS_H
#define WRAPPERS_H

#include "Simulator.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(libgenesys, m) {
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

#endif /* WRAPPERS_H */
