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
 * File:   ModelElementWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 18, 2019, 12:03 AM
 */

#ifndef MODEL_ELEMENT_WRAPPER_H
#define MODEL_ELEMENT_WRAPPER_H

#include "../ModelElement.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initModelElement(py::module &m) {
    py::class_<ModelElement>(m, "ModelElement")
        .def(py::init<std::string>())
        .def(py::init<ModelElement&>())
        .def("getId", &ModelElement::getId)
        .def("setName", &ModelElement::setName)
        .def("getName", &ModelElement::getName)
        .def("getTypename", &ModelElement::getTypename)
        .def("LoadInstance", &ModelElement::LoadInstance)
        .def("SaveInstance", &ModelElement::SaveInstance)
        .def("Check", &ModelElement::Check)
        .def("show", &ModelElement::show);
}

#endif /* MODEL_ELEMENT_WRAPPER_H */

