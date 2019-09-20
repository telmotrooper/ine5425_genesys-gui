/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PluginConnector_if.h
 * Author: rlcancian
 *
 * Created on 9 de Setembro de 2019, 19:17
 */

#ifndef PLUGINCONNECTOR_IF_H
#define PLUGINCONNECTOR_IF_H

#include<string>
#include "Plugin.h"

class PluginConnector_if {
public:
    virtual Plugin* check(const std::string dynamicLibraryFilename) = 0;
    virtual Plugin* connect(const std::string dynamicLibraryFilename) = 0;
    virtual bool disconnect(const std::string dynamicLibraryFilename) = 0;
    virtual bool disconnect(Plugin* plugin) = 0;
};

#endif /* PLUGINCONNECTOR_IF_H */

