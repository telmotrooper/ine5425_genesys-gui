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
 * File:   SinkModelComponentWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 19, 2019, 8:15 PM
 */

#ifndef SINK_MODEL_COMPONENT_WRAPPER_H
#define SINK_MODEL_COMPONENT_WRAPPER_H

#include "../SinkModelComponent.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initSinkModelComponent(py::module &m) {
    py::class_<SinkModelComponent, ModelComponent>(m, "SinkModelComponent");
}


#endif /* SINK_MODEL_COMPONENT_WRAPPER_H */

