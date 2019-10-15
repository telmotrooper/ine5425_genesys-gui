/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ComponentManagerWrapper.h
 * Author: Telmo "Trooper"
 *
 * Created on October 14, 2019, 11:08 PM
 */

#ifndef COMPONENT_MANAGER_WRAPPER_H
#define COMPONENT_MANAGER_WRAPPER_H

#include "../ComponentManager.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initComponentManager(py::module &m) {
    py::class_<ComponentManager>(m, "ComponentManager")
    .def(py::init<Model*>())
    .def("insert", &ComponentManager::insert)
    .def("remove", &ComponentManager::remove)
    .def("clear", &ComponentManager::clear)
//    .def("getComponent", &ComponentManager::getComponent)
    .def("getNumberOfComponents", &ComponentManager::getNumberOfComponents)
    .def("begin", &ComponentManager::begin)
    .def("end", &ComponentManager::end);
}

#endif /* COMPONENT_MANAGER_WRAPPER_H */

