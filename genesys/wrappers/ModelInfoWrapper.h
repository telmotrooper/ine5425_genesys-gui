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
 * File:   ModelInfoWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on November 04, 2019, 05:27 PM
 */

#ifndef MODEL_INFO_WRAPPER_H
#define MODEL_INFO_WRAPPER_H

#include "../ModelInfo.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initModelInfo(py::module &m) {
    py::class_<ModelInfo>(m, "ModelInfo")
        .def(py::init())
        .def(py::init<ModelInfo&>())
        .def("show", &ModelInfo::show)
        .def("setName", &ModelInfo::setName)
        .def("getName", &ModelInfo::getName)
        .def("setAnalystName", &ModelInfo::setAnalystName)
        .def("getAnalystName", &ModelInfo::getAnalystName)
        .def("setDescription", &ModelInfo::setDescription)
        .def("getDescription", &ModelInfo::getDescription)
        .def("setProjectTitle", &ModelInfo::setProjectTitle)
        .def("getProjectTitle", &ModelInfo::getProjectTitle)
        .def("setVersion", &ModelInfo::setVersion)
        .def("getVersion", &ModelInfo::getVersion)
        .def("setNumberOfReplications", &ModelInfo::setNumberOfReplications)
        .def("getNumberOfReplications", &ModelInfo::getNumberOfReplications)
        .def("setReplicationLength", &ModelInfo::setReplicationLength)
        .def("getReplicationLengthTimeUnit", &ModelInfo::getReplicationLengthTimeUnit,
            py::return_value_policy::reference)
        .def("setReplicationLengthTimeUnit", &ModelInfo::setReplicationLengthTimeUnit)    
        .def("setWarmUpPeriod", &ModelInfo::setWarmUpPeriod)
        .def("getWarmUpPeriod", &ModelInfo::getWarmUpPeriod)
        .def("setWarmUpPeriodTimeUnit", &ModelInfo::setWarmUpPeriodTimeUnit)
        .def("getWarmUpPeriodTimeUnit", &ModelInfo::getWarmUpPeriodTimeUnit,
            py::return_value_policy::reference)
        .def("setTerminatingCondition", &ModelInfo::setTerminatingCondition)
        .def("getTerminatingCondition", &ModelInfo::getTerminatingCondition)
        .def("loadInstance", &ModelInfo::loadInstance);
        // .def("saveInstance", &ModelInfo::saveInstance);
}

#endif /* MODEL_INFO_WRAPPER_H */
