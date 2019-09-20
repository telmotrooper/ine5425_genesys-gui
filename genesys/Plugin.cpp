/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Plugin.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 21 de Junho de 2018, 12:58
 */

#include "Plugin.h"
#include "Model.h"
#include "SourceModelComponent.h"
#include "SinkModelComponent.h"
#include "Assign.h"
#include <assert.h>

Plugin::Plugin(StaticGetPluginInformation getInformation) {
    this->_StatMethodGetInformation = getInformation;
    try {
	PluginInformation* infos = _StatMethodGetInformation();
	this->_pluginInfo = infos;
	this->_isValidPlugin = true;
    } catch (...) {
	this->_isValidPlugin = false;
    }
}

PluginInformation* Plugin::getPluginInfo() const {
    return _pluginInfo;
}

bool Plugin::isIsValidPlugin() const {
    return _isValidPlugin;
}

//Plugin::Plugin(std::string pluginTypename, bool source, bool drain) {
//    //_fullfilename = fullfilename;
//    _source = source;
//    _drain = drain;
//}

Plugin::Plugin(const Plugin& orig) {
}

Plugin::~Plugin() {
}

ModelElement* Plugin::loadNew(Model* model, std::map<std::string, std::string>* fields) {
    if (this->_pluginInfo->isComponent()) {
	return _loadNewComponent(model, fields);
    } else {
	return _loadNewElement(model->getElementManager(), fields);
    }
}

bool Plugin::loadAndInsertNew(Model* model, std::map<std::string, std::string>* fields) {
    if (this->_pluginInfo->isComponent()) {
	ModelComponent* newComp = _loadNewComponent(model, fields);
	return model->getComponentManager()->insert(newComp);
    } else {
	ModelElement* newElem = _loadNewElement(model->getElementManager(), fields);
	return model->getElementManager()->insert(this->_pluginInfo->getPluginTypename(), newElem);
    }
}

ModelComponent* Plugin::_loadNewComponent(Model* model, std::map<std::string, std::string>* fields) {
    //return this->_pluginInfo->loader(model, fields);
    StaticLoaderComponentInstance loader = this->_pluginInfo->getComponentloader();
    ModelComponent* newElementOrComponent = loader(model, fields);
    return newElementOrComponent;
}

ModelElement* Plugin::_loadNewElement(ElementManager* elems, std::map<std::string, std::string>* fields) {
    StaticLoaderElementInstance loader = this->_pluginInfo->getElementloader();
    ModelElement* newElementOrComponent = loader(elems, fields);
    return newElementOrComponent;
}
