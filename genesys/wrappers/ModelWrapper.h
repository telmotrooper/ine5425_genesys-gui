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
 * File:   ModelWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 14, 2019, 11:20 PM
 */

#ifndef MODEL_WRAPPER_H
#define MODEL_WRAPPER_H

#include "../Model.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initModel(py::module &m) {
    py::class_<Model>(m, "Model")
        .def(py::init<Simulator*>())
        .def("saveModel", &Model::saveModel)
        .def("loadModel", &Model::loadModel)
        .def("checkModel", &Model::checkModel)
        .def("clear", &Model::clear)
        .def("show", &Model::show)
        .def("removeEntity", &Model::removeEntity)
//        .def("sendEntityToComponent", &Model::sendEntityToComponent)
//        .def("parseExpression", &Model::parseExpression)
        .def("checkExpression", &Model::checkExpression)
        .def("getId", &Model::getId)
        .def("getControls", &Model::getControls)
        .def("getResponses", &Model::getResponses)
        .def("getOnEventManager", &Model::getOnEventManager)
        .def("getElementManager", &Model::getElementManager)
        .def("getComponentManager", &Model::getComponentManager)
        .def("getInfos", &Model::getInfos)
        .def("getParentSimulator", &Model::getParentSimulator)
        .def("getSimulation", &Model::getSimulation,
            py::return_value_policy::reference)
        .def("getEvents", &Model::getEvents)
        .def("setTraceManager", &Model::setTraceManager)
        .def("getTraceManager", &Model::getTraceManager,
            py::return_value_policy::reference);
}

#endif /* MODEL_WRAPPER_H */

