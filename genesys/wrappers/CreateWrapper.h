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
 * File:   CreateWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 19, 2019, 6:30 PM
 */

#ifndef CREATE_WRAPPER_H
#define CREATE_WRAPPER_H

#include "../ModelElement.h"
#include "../Create.h"
#include "../ElementManager.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initCreate(py::module &m) {
    py::class_<ModelComponent, ModelElement>(m, "ModelComponent");
    py::class_<SourceModelComponent, ModelComponent>(m, "SourceModelComponent");
    py::class_<Create, SourceModelComponent>(m, "Create")
        .def(py::init<Model*>())
        .def(py::init<Create&>())
        .def("show", &Create::show)
        .def("GetPluginInformation", &Create::GetPluginInformation)
        .def("LoadInstance", &Create::LoadInstance);
        // There are more methods which haven't been added to the wrapper yet
}

#endif /* CREATE_WRAPPER_H */

