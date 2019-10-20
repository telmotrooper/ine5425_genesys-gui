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
 * File:   BaseConsoleGenesysApplicationWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 19, 2019, 10:36 PM
 */

#ifndef BASE_CONSOLE_GENESYS_APPLICATION_WRAPPER_H
#define BASE_CONSOLE_GENESYS_APPLICATION_WRAPPER_H

#include "../BaseConsoleGenesysApplication.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

class PyGenesysApplication: public BaseConsoleGenesysApplication {
public:
    PyGenesysApplication() {};
public:
    int main(int argc, char** argv) {
        return 0;
    };
};


void initBaseConsoleGenesysApplication(py::module &m) {    
    py::class_<BaseConsoleGenesysApplication>(m, "BaseConsoleGenesysApplication");
    
    py::class_<PyGenesysApplication, BaseConsoleGenesysApplication>(m, "PyGenesysApplication")
       .def(py::init())
       .def("setDefaultTraceHandlers", &PyGenesysApplication::setDefaultTraceHandlers)
       .def("insertFakePluginsByHand", &PyGenesysApplication::insertFakePluginsByHand);
}

#endif /* BASE_CONSOLE_GENESYS_APPLICATION_WRAPPER_H */

