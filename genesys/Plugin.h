/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Plugin.h
 * Author: rafael.luiz.cancian
 *
 * Created on 21 de Junho de 2018, 12:58
 */

#ifndef PLUGIN_H
#define PLUGIN_H

#include "Util.h"
#include <string>
#include <functional>
#include <list>

#include "PluginInformation.h"

/*!
 * A Plugin represents a dynamically linked component class (ModelComponent) or element class (ModelElement); It gives access to a ModelComponent so it can be used by the model. Classes like Create, Delay, and Dispose are examples of PlugIns.  It corresponds directly to the  "Expansible" part (the capitalized 'E') of the GenESyS acronymous
PlugIns are NOT implemented yet
 */
class Plugin {
public:
    Plugin(std::string filename_so_dll);
    Plugin(StaticGetPluginInformation getInformation); // temporary. Just while compiled together
    Plugin(const Plugin& orig);
    virtual ~Plugin();
public:
    bool isIsValidPlugin() const;
    PluginInformation* getPluginInfo() const;
public:
    ModelElement* loadNew(Model* model, std::map<std::string, std::string>* fields);
    bool loadAndInsertNew(Model* model, std::map<std::string, std::string>* fields);
private:
    ModelComponent* _loadNewComponent(Model* model, std::map<std::string, std::string>* fields);
    ModelElement* _loadNewElement(ElementManager* model, std::map<std::string, std::string>* fields);
private: // read only
    bool _isValidPlugin;
    PluginInformation* _pluginInfo;
private:
    StaticGetPluginInformation _StatMethodGetInformation;
};

#endif /* PLUGIN_H */

