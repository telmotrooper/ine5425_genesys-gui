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
 * File:   Wrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 12, 2019, 9:53 PM
 */

#ifndef WRAPPERS_H
#define WRAPPERS_H

#include "ModelManagerWrapper.h"
#include "ComponentManagerWrapper.h"
#include "ElementManagerWrapper.h"
#include "ModelWrapper.h"
#include "SimulatorWrapper.h"
#include "TraceManagerWrapper.h"
#include "UtilWrapper.h"
#include "ModelElementWrapper.h"
#include "EntityTypeWrapper.h"
#include "CreateWrapper.h"
#include "SourceModelComponentWrapper.h"
#include "ModelComponentWrapper.h"
#include "DelayWrapper.h"
#include "ConnectionManagerWrapper.h"
#include "SinkModelComponentWrapper.h"
#include "DisposeWrappers.h"
#include "BaseConsoleGenesysApplicationWrapper.h"
#include "ModelSimulationWrapper.h"
#include "ModelInfoWrapper.h"
#include "ResourceWrapper.h"
#include "QueueWrapper.h"
#include "SeizeWrapper.h"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(libgenesys, m) {
    initModelManager(m);
    initComponentManager(m);
    initElementManager(m);
    initModel(m);
    initSimulator(m);
    initTraceManager(m);
    initUtil(m);
    initModelElement(m);
    initEntityType(m); // depends on ModelElement
    initModelComponent(m); // depends on ModelElement
    initSourceModelComponent(m); // depends on ModelComponent
    initCreate(m); // depends on SourceModelComponent
    initDelay(m); // depends on ModelComponent
    initConnectionManager(m);
    initSinkModelComponent(m); // depends on ModelComponent
    initDispose(m); // depends on SinkModelComponent
    initBaseConsoleGenesysApplication(m);
    initModelSimulation(m);
    initModelInfo(m);
    initResource(m);
    initQueue(m);
    initSeize(m);
}

#endif /* WRAPPERS_H */
