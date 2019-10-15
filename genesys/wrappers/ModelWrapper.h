/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
        .def("getSimulation", &Model::getSimulation)
        .def("getEvents", &Model::getEvents)
        .def("setTraceManager", &Model::setTraceManager)
        .def("getTraceManager", &Model::getTraceManager);
}

#endif /* MODEL_WRAPPER_H */

