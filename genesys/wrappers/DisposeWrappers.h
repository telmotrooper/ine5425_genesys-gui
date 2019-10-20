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
 * File:   DisposeWrappers.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Disposed on October 19, 2019, 8:55 PM
 */

#ifndef DISPOSE_WRAPPERS_H
#define DISPOSE_WRAPPERS_H

#include "../Dispose.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initDispose(py::module &m) {
    py::class_<Dispose, SinkModelComponent>(m, "Dispose")
        .def(py::init<Model*>())
        .def(py::init<Dispose&>())
        .def("show", &Dispose::show)
        .def("GetPluginInformation", &Dispose::GetPluginInformation)
        .def("LoadInstance", &Dispose::LoadInstance);
        // There are more methods which haven't been added to the wrapper yet
}

#endif /* DISPOSE_WRAPPERS_H */

