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
 * File:   ConnectionManagerWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 19, 2019, 7:32 PM
 */

#ifndef CONNECTION_MANAGER_WRAPPER_H
#define CONNECTION_MANAGER_WRAPPER_H

#include "../ConnectionManager.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initConnectionManager(py::module &m) {
    py::class_<ConnectionManager>(m, "ConnectionManager")
        .def(py::init())
        .def(py::init<ConnectionManager&>())
        .def("size", &ConnectionManager::size)
        .def("front", &ConnectionManager::front)
        .def("getAtRank", &ConnectionManager::getAtRank)
//        .def("frontConnection", &ConnectionManager::frontConnection)
//        .def("getConnectionAtRank", &ConnectionManager::getConnectionAtRank)
        .def("insert", &ConnectionManager::insert,
            py::arg("component"), py::arg("inputNumber") = 0)
        .def("getList", &ConnectionManager::getList);
}

#endif /* CONNECTION_MANAGER_WRAPPER_H */

