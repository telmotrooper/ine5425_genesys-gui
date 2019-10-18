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
 * File:   EntityTypeWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 17, 2019, 11:19 PM
 */

#ifndef ENTITY_TYPE_WRAPPER_H
#define ENTITY_TYPE_WRAPPER_H

#include "../EntityType.h"
#include "../ElementManager.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initEntityType(py::module &m) {
    py::class_<EntityType>(m, "EntityType")
        .def(py::init<ElementManager*>())
        .def(py::init<ElementManager*, std::string>())
        .def(py::init<EntityType&>())
        .def("show", &EntityType::show)
        .def("GetPluginInformation", &EntityType::GetPluginInformation)
        .def("LoadInstance", &EntityType::LoadInstance)
        .def("setInitialWaitingCost", &EntityType::setInitialWaitingCost);
//        .def("getElement", &EntityType::getElement)
//        .def("getNumberOfElements", &EntityType::getNumberOfElements)
//        .def("getRankOf", &EntityType::getRankOf)
//        .def("getElementTypenames", &EntityType::getElementTypenames);
}

#endif /* ENTITY_TYPE_WRAPPER_H */
