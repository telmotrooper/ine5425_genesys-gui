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
 * File:   ComponentManagerWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
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
        .def("getComponent", (ModelComponent* (ComponentManager::*)(Util::identification)) &ComponentManager::getComponent)
        .def("getComponent", (ModelComponent* (ComponentManager::*)(std::string)) &ComponentManager::getComponent)
        .def("getNumberOfComponents", &ComponentManager::getNumberOfComponents)
        .def("begin", &ComponentManager::begin)
        .def("end", &ComponentManager::end);
}

#endif /* COMPONENT_MANAGER_WRAPPER_H */

