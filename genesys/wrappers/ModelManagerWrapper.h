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
 * File:   ModelManagerWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * ModelManagerd on October 19, 2019, 9:17 PM
 */

#ifndef MODEL_MANAGER_WRAPPER_H
#define MODEL_MANAGER_WRAPPER_H

#include "../ModelManager.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initModelManager(py::module &m) {
    py::class_<ModelManager>(m, "ModelManager")
        .def(py::init<Simulator*>())
        .def(py::init<ModelManager&>())
        .def("insert", &ModelManager::insert)
        .def("remove", &ModelManager::remove)
        .def("setCurrent", &ModelManager::setCurrent)
        .def("saveModel", &ModelManager::saveModel)
        .def("loadModel", &ModelManager::loadModel)
        .def("front", &ModelManager::front)
        .def("current", &ModelManager::current,
            py::return_value_policy::reference)
        .def("next", &ModelManager::next)
        .def("end", &ModelManager::end);
}

#endif /* MODEL_MANAGER_WRAPPER_H */

