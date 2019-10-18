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
 * File:   UtilWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 14, 2019, 11:33 PM
 */

#ifndef UTIL_WRAPPER_H
#define UTIL_WRAPPER_H

#include "../Util.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initUtil(py::module &m) {
//    py::class_<Util, std::unique_ptr<Util, py::nodelete>>(m, "Util");
    
    py::enum_<Util::TraceLevel>(m, "TraceLevel")
        .value("noTraces", Util::TraceLevel::noTraces)
        .value("errors", Util::TraceLevel::errors)
        .value("report", Util::TraceLevel::report)
        .value("simulation", Util::TraceLevel::simulation)
        .value("transferOnly", Util::TraceLevel::transferOnly)
        .value("blockArrival", Util::TraceLevel::blockArrival)
        .value("blockInternal", Util::TraceLevel::blockInternal)
        .value("mostDetailed", Util::TraceLevel::mostDetailed)
        .export_values();
}

#endif /* UTIL_WRAPPER_H */
