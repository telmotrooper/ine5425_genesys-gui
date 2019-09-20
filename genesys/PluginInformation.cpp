/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PluginInformation.cpp
 * Author: rlcancian
 * 
 * Created on 9 de Setembro de 2019, 20:02
 */

#include "PluginInformation.h"


    PluginInformation::PluginInformation(std::string pluginTypename, StaticLoaderComponentInstance componentloader) {
	this->_componentloader = componentloader;
	this->_elementloader = nullptr;
	this->_isComponent = true;
	this->_pluginTypename = pluginTypename;
    }

    PluginInformation::PluginInformation(std::string pluginTypename, StaticLoaderElementInstance elementloader) {
	this->_componentloader = nullptr;
	this->_elementloader = elementloader;
	this->_isComponent = false;
	this->_pluginTypename = pluginTypename;
    }

    StaticLoaderElementInstance PluginInformation::getElementloader() const {
        return _elementloader;
    }

    StaticLoaderComponentInstance PluginInformation::getComponentloader() const {
        return _componentloader;
    }

    bool PluginInformation::isGenerateReport() const {
        return _generateReport;
    }

    bool PluginInformation::isComponent() const {
        return _isComponent;
    }

    bool PluginInformation::isSendTransfer() const {
        return _sendTransfer;
    }

    bool PluginInformation::isReceiveTransfer() const {
        return _receiveTransfer;
    }

    bool PluginInformation::isSink() const {
        return _isSink;
    }

    bool PluginInformation::isSource() const {
        return _isSource;
    }

    std::string PluginInformation::getObservation() const {
        return _observation;
    }

    std::string PluginInformation::getVersion() const {
        return _version;
    }

    std::string PluginInformation::getDate() const {
        return _date;
    }

    std::string PluginInformation::getAuthor() const {
        return _author;
    }

    std::string PluginInformation::getPluginTypename() const {
        return _pluginTypename;
    }
    
    void PluginInformation::insertDynamicLibFileDependence(std::string filename) {
	_dynamicLibFilenameDependencies->insert(_dynamicLibFilenameDependencies->end(), filename);
    }

    void PluginInformation::setDynamicLibFilenameDependencies(std::list<std::string>* dynamicLibFilenameDependencies) {
        this->_dynamicLibFilenameDependencies = dynamicLibFilenameDependencies;
    }

    std::list<std::string>* PluginInformation::getDynamicLibFilenameDependencies() const {
        return _dynamicLibFilenameDependencies;
    }

    void PluginInformation::setGenerateReport(bool generateReport) {
        this->_generateReport = generateReport;
    }

    void PluginInformation::setSendTransfer(bool sendTransfer) {
        this->_sendTransfer = sendTransfer;
    }

    void PluginInformation::setReceiveTransfer(bool receiveTransfer) {
        this->_receiveTransfer = receiveTransfer;
    }

    void PluginInformation::setSink(bool Sink) {
        _isSink = Sink;
    }

    void PluginInformation::setSource(bool Source) {
        _isSource = Source;
    }

    void PluginInformation::setObservation(std::string observation) {
        this->_observation = observation;
    }

    void PluginInformation::setVersion(std::string version) {
        this->_version = version;
    }

    void PluginInformation::setDate(std::string date) {
        this->_date = date;
    }

    void PluginInformation::setAuthor(std::string author) {
        this->_author = author;
    }


