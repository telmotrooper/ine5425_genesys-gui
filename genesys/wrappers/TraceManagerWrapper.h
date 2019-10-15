/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TraceManagerWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 14, 2019, 11:22 PM
 */

#ifndef TRACE_MANAGER_WRAPPER_H
#define TRACE_MANAGER_WRAPPER_H

#include "../TraceManager.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initTraceManager(py::module &m) {
    py::class_<TraceManager>(m, "TraceManager")
        .def(py::init<Simulator*>())
//        .def("addTraceHandler", &TraceManager::addTraceHandler);
//        .def("addTraceReportHandler", &TraceManager::addTraceReportHandler)
//        .def("addTraceSimulationHandler", &TraceManager::addTraceSimulationHandler)
//        .def("addTraceErrorHandler", &TraceManager::addTraceErrorHandler)
        .def("trace", &TraceManager::trace)
        .def("traceError", &TraceManager::traceError)
        .def("traceReport", &TraceManager::traceReport)
        .def("traceSimulation", &TraceManager::traceSimulation)
        .def("getErrorMessages", &TraceManager::getErrorMessages)
        .def("setTraceLevel", &TraceManager::setTraceLevel)
        .def("getTraceLevel", &TraceManager::getTraceLevel)
        .def("getSimulator", &TraceManager::getSimulator);
}

#endif /* TRACE_MANAGER_WRAPPER_H */

