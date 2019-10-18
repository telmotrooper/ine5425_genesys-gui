/*
 * Copyright (C) 2019 Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

