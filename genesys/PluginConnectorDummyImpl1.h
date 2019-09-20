/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PluginConnectorDummyImpl1.h
 * Author: rlcancian
 *
 * Created on 9 de Setembro de 2019, 19:24
 */

#ifndef PLUGINCONNECTORDUMMYIMPL1_H
#define PLUGINCONNECTORDUMMYIMPL1_H

#include "PluginConnector_if.h"

class PluginConnectorDummyImpl1 : public PluginConnector_if {
public:
    PluginConnectorDummyImpl1();
    PluginConnectorDummyImpl1(const PluginConnectorDummyImpl1& orig);
    virtual ~PluginConnectorDummyImpl1();
public:
    virtual Plugin* check(const std::string dynamicLibraryFilename);
    virtual Plugin* connect(const std::string dynamicLibraryFilename);
    virtual bool disconnect(const std::string dynamicLibraryFilename);
    virtual bool disconnect(Plugin* plugin);
private:

};

#endif /* PLUGINCONNECTORDUMMYIMPL1_H */

