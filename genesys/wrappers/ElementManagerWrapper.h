/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ElementManagerWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 14, 2019, 11:18 PM
 */

#ifndef ELEMENT_MANAGER_WRAPPER_H
#define ELEMENT_MANAGER_WRAPPER_H

#include "../ElementManager.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initElementManager(py::module &m) {
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
}

#endif /* ELEMENT_MANAGER_WRAPPER_H */

