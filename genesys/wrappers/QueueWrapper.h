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
 * File:   QueueWrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on November 04, 2019, 7:12 PM
 */

#ifndef QUEUE_WRAPPER_H
#define QUEUE_WRAPPER_H

#include "../Queue.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

void initQueue(py::module &m) {
    py::enum_<Queue::OrderRule>(m, "OrderRule")
        .value("FIFO", Queue::OrderRule::FIFO)
        .value("LIFO", Queue::OrderRule::LIFO)
        .value("HIGHESTVALUE", Queue::OrderRule::HIGHESTVALUE)
        .value("SMALLESTVALUE", Queue::OrderRule::SMALLESTVALUE);
      
    py::class_<Queue, ModelElement>(m, "Queue")
        .def(py::init<ElementManager*>())
        .def(py::init<ElementManager*, std::string>())
        .def(py::init<Queue&>())
        .def("show", &Queue::show)
        .def("GetPluginInformation", &Queue::GetPluginInformation,
              py::return_value_policy::reference)
        .def("LoadInstance", &Queue::LoadInstance,
              py::return_value_policy::reference)
        .def("insertElement", &Queue::insertElement)
        .def("removeElement", &Queue::removeElement)
        .def("size", &Queue::size)
        .def("first", &Queue::first,
              py::return_value_policy::reference)
        .def("getAtRank", &Queue::getAtRank,
              py::return_value_policy::reference)
        .def("setAttributeName", &Queue::setAttributeName)
        .def("getAttributeName", &Queue::getAttributeName)
        .def("setOrderRule", &Queue::setOrderRule)
        .def("getOrderRule", &Queue::getOrderRule,
              py::return_value_policy::reference)
        .def("sumAttributesFromWaiting", &Queue::sumAttributesFromWaiting)
        .def("getAttributeFromWaitingRank", &Queue::getAttributeFromWaitingRank)
        .def("initBetweenReplications", &Queue::initBetweenReplications);
}

#endif /* QUEUE_WRAPPER_H */

