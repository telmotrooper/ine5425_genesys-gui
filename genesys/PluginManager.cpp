/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PluginManager.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 30 de Maio de 2019, 17:49
 */

#include "PluginManager.h"
#include "Simulator.h"
#include "Traits.h"

PluginManager::PluginManager(Simulator* simulator) {
    _simulator = simulator;
    this->_pluginConnector = new Traits<PluginConnector_if>::Implementation();
}

PluginManager::PluginManager(const PluginManager& orig) {
}

PluginManager::~PluginManager() {
}

//bool PluginManager::check(Plugin* plugin){
//    return true;
//}

bool PluginManager::_insert(Plugin* plugin) {
    PluginInformation *plugInfo = plugin->getPluginInfo();
    if (plugin->isIsValidPlugin() && plugInfo != nullptr) {
	std::string msg = "Inserting ";
	if (plugInfo->isComponent())
	    msg += "component";
	else
	    msg += "element";
	msg += " plugin \"" + plugin->getPluginInfo()->getPluginTypename() + "\"";
	_simulator->getTraceManager()->trace(Util::TraceLevel::blockInternal, msg);
	// insert all dependencies before to insert this plugin
	bool allDependenciesInserted = true;
	if (plugInfo->getDynamicLibFilenameDependencies()->size() > 0) {
	    Util::IncIndent();
	    {
		_simulator->getTraceManager()->trace(Util::TraceLevel::blockInternal, "Inserting dependencies...");
		for (std::list<std::string>::iterator it = plugInfo->getDynamicLibFilenameDependencies()->begin(); it != plugInfo->getDynamicLibFilenameDependencies()->end(); it++) {
		    allDependenciesInserted &= (this->insert((*it)) != nullptr);
		}
	    }
	    Util::DecIndent();
	}
	if (!allDependenciesInserted) {
	    _simulator->getTraceManager()->trace(Util::TraceLevel::blockInternal, "Plugin dependencies could not be inserted; therefore, plugin will not be inserted");
	    return false;
	}
	if (this->find(plugInfo->getPluginTypename()) != nullptr) { // plugin alread exists
	    _simulator->getTraceManager()->trace(Util::TraceLevel::blockInternal, "Plugin alread exists and was not inserted again");
	    return false;
	}
	_plugins->insert(plugin);
	this->_simulator->getTraceManager()->trace(Util::TraceLevel::mostDetailed, "Plugin successfully inserted");
	return true;
    } else {
	this->_simulator->getTraceManager()->trace(Util::TraceLevel::blockInternal, "Invalid plugin");
	plugin->~Plugin(); // destroy the invalid plugin
	return false;
    }
}

bool PluginManager::check(std::string dynamicLibraryFilename) {
    Plugin* plugin;
    try {
	plugin = _pluginConnector->check(dynamicLibraryFilename);
    } catch (...) {

	return false;
    }
    return (plugin != nullptr);
}

Plugin* PluginManager::insert(std::string dynamicLibraryFilename) {
    Plugin* plugin;
    try {
	plugin = _pluginConnector->connect(dynamicLibraryFilename);
	if (plugin != nullptr)
	    _insert(plugin);
	else {
	    _simulator->getTraceManager()->trace(Util::TraceLevel::errors, "Plugin from file \""+dynamicLibraryFilename+"\" could not be connected.");
	}
    } catch (...) {

	return nullptr;
    }
    return plugin;
}

bool PluginManager::remove(std::string dynamicLibraryFilename) {

    Plugin* pi = this->find(dynamicLibraryFilename);
    remove(pi);
}

bool PluginManager::remove(Plugin* plugin) {
    if (plugin != nullptr) {
	_plugins->remove(plugin);
	try {
	    _pluginConnector->disconnect(plugin);
	} catch (...) {

	    return false;
	}
	return true;
    }
    return false;
}

Plugin* PluginManager::find(std::string pluginTypeName) {
    for (std::list<Plugin*>::iterator it = this->_plugins->getList()->begin(); it != _plugins->getList()->end(); it++) {
	if ((*it)->getPluginInfo()->getPluginTypename() == pluginTypeName) {

	    return (*it);
	}
    }
    return nullptr;
}

Plugin* PluginManager::front() {

    return this->_plugins->front();
}

Plugin* PluginManager::next() {

    return _plugins->next();
}

Plugin* PluginManager::last() {
    return this->_plugins->last();
}