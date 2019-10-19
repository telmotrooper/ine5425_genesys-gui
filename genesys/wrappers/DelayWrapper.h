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
 * File:   DelayWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 19, 2019, 7:22 PM
 */

#ifndef DELAYWRAPPER_H
#define DELAYWRAPPER_H

#include "../Delay.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initDelay(py::module &m) {
    py::class_<Delay, ModelComponent>(m, "Delay")
        .def(py::init<Model*>())
        .def(py::init<Delay&>())
        .def("setDelayExpression", &Delay::setDelayExpression)
        .def("getDelayExpression", &Delay::getDelayExpression)
        .def("setDelayTimeUnit", &Delay::setDelayTimeUnit)
        .def("getDelayTimeUnit", &Delay::getDelayTimeUnit)
        .def("show", &Delay::show)
        .def("GetPluginInformation", &Delay::GetPluginInformation)
        .def("LoadInstance", &Delay::LoadInstance);
}

#endif /* DELAYWRAPPER_H */

