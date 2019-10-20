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
 * File:   ModelSimulationWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 19, 2019, 11:33 PM
 */

#ifndef MODELSIMULATIONWRAPPER_H
#define MODELSIMULATIONWRAPPER_H

#include "../ModelSimulation.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initModelSimulation(py::module &m) {
    py::class_<ModelSimulation>(m, "ModelSimulation")
        .def(py::init<Model*>())
        .def(py::init<ModelSimulation&>())
        .def("startSimulation", &ModelSimulation::startSimulation)
        .def("pauseSimulation", &ModelSimulation::pauseSimulation)
        .def("stepSimulation", &ModelSimulation::stepSimulation)
        .def("stopSimulation", &ModelSimulation::stopSimulation)
        .def("restartSimulation", &ModelSimulation::restartSimulation)
        .def("setPauseOnEvent", &ModelSimulation::setPauseOnEvent)
        .def("isPauseOnEvent", &ModelSimulation::isPauseOnEvent)
        .def("setStepByStep", &ModelSimulation::setStepByStep)
        .def("isStepByStep", &ModelSimulation::isStepByStep)
        .def("setInitializeStatistics", &ModelSimulation::setInitializeStatistics)
        .def("isInitializeStatistics", &ModelSimulation::isInitializeStatistics)
        .def("setInitializeSystem", &ModelSimulation::setInitializeSystem)
        .def("isInitializeSystem", &ModelSimulation::isInitializeSystem)
        .def("setPauseOnReplication", &ModelSimulation::setPauseOnReplication)
        .def("isPauseOnReplication", &ModelSimulation::isPauseOnReplication)
        .def("getSimulatedTime", &ModelSimulation::getSimulatedTime)
        .def("isRunning", &ModelSimulation::isRunning)
        .def("getCurrentReplicationNumber", &ModelSimulation::getCurrentReplicationNumber)
        .def("getCurrentComponent", &ModelSimulation::getCurrentComponent)
        .def("getCurrentEntity", &ModelSimulation::getCurrentEntity)
        .def("getCurrentInputNumber", &ModelSimulation::getCurrentInputNumber)
        .def("getSimulationReporter", &ModelSimulation::getSimulationReporter);
}


#endif /* MODELSIMULATIONWRAPPER_H */

