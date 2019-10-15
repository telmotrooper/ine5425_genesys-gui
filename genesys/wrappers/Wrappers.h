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

#include "ComponentManagerWrapper.h"
#include "../ElementManager.h"
#include "../Model.h"
#include "../Simulator.h"
#include "../TraceManager.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(libgenesys, m) {  
    initComponentManager(m);
    
    py::class_<ElementManager>(m, "ElementManager")
        .def(py::init<Model*>())
        .def("insert", &ElementManager::insert)
        .def("remove", &ElementManager::remove)
//        .def("check", &ElementManager::check)
        .def("clear", &ElementManager::clear)
//        .def("getElement", &ElementManager::getElement)
//        .def("getNumberOfElements", &ElementManager::getNumberOfElements)
        .def("getRankOf", &ElementManager::getRankOf)
        .def("getElementTypenames", &ElementManager::getElementTypenames);
    
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

#endif /* WRAPPERS_H */
