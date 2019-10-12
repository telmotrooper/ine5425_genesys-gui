/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PluginConnectorDummyImpl1.cpp
 * Author: rlcancian
 * 
 * Created on 9 de Setembro de 2019, 19:24
 */

#include "PluginConnectorDummyImpl1.h"

// Model Components
#include "Create.h"
#include "Delay.h"
#include "Dispose.h"
#include "Seize.h"
#include "Release.h"
#include "Assign.h"
#include "Record.h"
#include "Decide.h"
#include "Dummy.h"
#include "Route.h"
#include "Enter.h"
#include "Leave.h"
#include "Write.h"

// Model elements
#include "EntityType.h"
#include "Attribute.h"
#include "Variable.h"
#include "ProbDistrib.h"
#include "EntityGroup.h"
#include "Station.h"
#include "Formula.h"
#include "ODE.h"

#include "Util.h"

PluginConnectorDummyImpl1::PluginConnectorDummyImpl1() {
}

PluginConnectorDummyImpl1::PluginConnectorDummyImpl1(const PluginConnectorDummyImpl1& orig) {
}

PluginConnectorDummyImpl1::~PluginConnectorDummyImpl1() {
}

Plugin* PluginConnectorDummyImpl1::check(const std::string dynamicLibraryFilename) {
    return nullptr; /**@ TODO:To implement */
}

Plugin* PluginConnectorDummyImpl1::connect(const std::string dynamicLibraryFilename) {
    std::string fn = getFileName(dynamicLibraryFilename);
    StaticGetPluginInformation GetInfo = nullptr;
    Plugin* pluginResult = nullptr;
    // model elements
    if (fn == "attribute.so")
	GetInfo = &Attribute::GetPluginInformation;
    else if (fn == "counter.so")
	GetInfo = &Counter::GetPluginInformation;
    else if (fn == "entitytype.so")
	GetInfo = &EntityType::GetPluginInformation;
    else if (fn == "queue.so")
	GetInfo = &Queue::GetPluginInformation;
    else if (fn == "resource.so")
	GetInfo = &Resource::GetPluginInformation;
    else if (fn == "statisticscollector.so")
	GetInfo = &StatisticsCollector::GetPluginInformation;
    else if (fn == "variable.so")
	GetInfo = &Variable::GetPluginInformation;
    else if (fn == "entitygroup.so")
	GetInfo = &EntityGroup::GetPluginInformation;
    else if (fn == "station.so")
	GetInfo = &Station::GetPluginInformation;
    else if (fn == "formula.so")
	GetInfo = &Formula::GetPluginInformation;
    else if (fn == "ode.so")
	GetInfo = &ODE::GetPluginInformation;
    else if (fn == "assign.so")
	// model components
	GetInfo = &Assign::GetPluginInformation;
    else if (fn == "create.so")
	GetInfo = &Create::GetPluginInformation;
    else if (fn == "write.so")
	GetInfo = &Write::GetPluginInformation;
    else if (fn == "decide.so")
	GetInfo = &Decide::GetPluginInformation;
    else if (fn == "delay.so")
	GetInfo = &Delay::GetPluginInformation;
    else if (fn == "dispose.so")
	GetInfo = &Dispose::GetPluginInformation;
    else if (fn == "dummy.so")
	GetInfo = &Dummy::GetPluginInformation;
    else if (fn == "record.so")
	GetInfo = &Record::GetPluginInformation;
    else if (fn == "release.so")
	GetInfo = &Release::GetPluginInformation;
    else if (fn == "seize.so")
	GetInfo = &Seize::GetPluginInformation;
    else if (fn == "route.so")
	GetInfo = &Route::GetPluginInformation;
    else if (fn == "enter.so")
	GetInfo = &Enter::GetPluginInformation;
    else if (fn == "leave.so")
	GetInfo = &Leave::GetPluginInformation;
    //else if (fn=="")

    if (GetInfo != nullptr) {
	pluginResult = new Plugin(GetInfo);
    }
    return pluginResult;
}

bool PluginConnectorDummyImpl1::disconnect(const std::string dynamicLibraryFilename) {
    return true;
}

bool PluginConnectorDummyImpl1::disconnect(Plugin* plugin) {
    return true;
}
