/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Wrapper.h
 * Author: Telmo "Trooper" <telmo.trooper@gmail.com>
 *
 * Created on October 12, 2019, 9:53 PM
 */

#ifndef WRAPPERS_H
#define WRAPPERS_H

#include "ComponentManagerWrapper.h"
#include "ElementManagerWrapper.h"
#include "ModelWrapper.h"
#include "SimulatorWrapper.h"
#include "TraceManagerWrapper.h"
#include "UtilWrapper.h"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(libgenesys, m) {  
    initComponentManager(m);
    initElementManager(m);
    initModel(m);
    initSimulator(m);
    initTraceManager(m);
    initUtil(m);
}

#endif /* WRAPPERS_H */
