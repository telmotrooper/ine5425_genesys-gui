/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
