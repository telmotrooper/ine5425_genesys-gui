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
 * File:   ReleaseWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on November 04, 2019, 8:43 PM
 */

#ifndef RELEASE_WRAPPER_H
#define RELEASE_WRAPPER_H

#include "../Release.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initRelease(py::module &m) {
    py::class_<Release, ModelComponent>(m, "Release")
        .def(py::init<Model*>())
        .def(py::init<Release&>())
        .def("show", &Release::show)
        .def("GetPluginInformation", &Release::GetPluginInformation,
            py::return_value_policy::reference)
        .def("LoadInstance", &Release::LoadInstance,
            py::return_value_policy::reference)
        .def("setResource", &Release::setResource);
}

#endif /* RELEASE_WRAPPER_H */

