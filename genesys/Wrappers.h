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

#include <pybind11/pybind11.h>
namespace py = pybind11;

#include "Simulator.h"

PYBIND11_MODULE(libgenesys, m) {
    py::class_<Simulator>(m, "Simulator")
        .def(py::init())
        .def("getName", &Simulator::getName);
}

#endif /* WRAPPERS_H */
