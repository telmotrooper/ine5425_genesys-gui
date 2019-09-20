/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModelInfo.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 7 de Novembro de 2018, 18:13
 */

#include "ModelInfo.h"
#include "Model.h"
#include "Assign.h"

ModelInfo::ModelInfo() {
    _name = "Model " + std::to_string(Util::GenerateNewIdOfType<Model>());
}

ModelInfo::ModelInfo(const ModelInfo& orig) {
}

ModelInfo::~ModelInfo() {

}
std::string ModelInfo::show(){
    return "analystName=\""+this->_analystName+"\""+
	    ",description=\""+this->_description+"\""+
	    ",name=\""+this->_name+"\""+
	    ",numberOfReplications="+std::to_string(this->_numberOfReplications)+
	    ",replicationLength="+std::to_string(this->_replicationLength)+ " "+Util::StrTimeUnit(this->_replicationLengthTimeUnit)+
	    ",terminatingCondition=\""+this->_terminatingCondition+"\""+
	    ",version="+this->_version+
	    ",warmupTime="+std::to_string(this->_warmUpPeriod)+" "+Util::StrTimeUnit(this->_warmUpPeriodTimeUnit);
}

void ModelInfo::setName(std::string _name) {
    this->_name = _name;
}

std::string ModelInfo::getName() const {
    return _name;
}

void ModelInfo::setAnalystName(std::string _analystName) {
    this->_analystName = _analystName;
}

std::string ModelInfo::getAnalystName() const {
    return _analystName;
}

void ModelInfo::setDescription(std::string _description) {
    this->_description = _description;
}

std::string ModelInfo::getDescription() const {
    return _description;
}

void ModelInfo::setProjectTitle(std::string _projectTitle) {
    this->_projectTitle = _projectTitle;
}

std::string ModelInfo::getProjectTitle() const {
    return _projectTitle;
}

void ModelInfo::setVersion(std::string _version) {
    this->_version = _version;
}

std::string ModelInfo::getVersion() const {
    return _version;
}

void ModelInfo::setNumberOfReplications(unsigned int _numberOfReplications) {
    this->_numberOfReplications = _numberOfReplications;
}

unsigned int ModelInfo::getNumberOfReplications() const {
    return _numberOfReplications;
}

void ModelInfo::setReplicationLength(double _replicationLength) {
    this->_replicationLength = _replicationLength;
}

double ModelInfo::getReplicationLength() const {
    return _replicationLength;
}

void ModelInfo::setReplicationLengthTimeUnit(Util::TimeUnit _replicationLengthTimeUnit) {
    this->_replicationLengthTimeUnit = _replicationLengthTimeUnit;
}

Util::TimeUnit ModelInfo::getReplicationLengthTimeUnit() const {
    return _replicationLengthTimeUnit;
}

void ModelInfo::setWarmUpPeriod(double _warmUpPeriod) {
    this->_warmUpPeriod = _warmUpPeriod;
}

double ModelInfo::getWarmUpPeriod() const {
    return _warmUpPeriod;
}

void ModelInfo::setWarmUpPeriodTimeUnit(Util::TimeUnit _warmUpPeriodTimeUnit) {
    this->_warmUpPeriodTimeUnit = _warmUpPeriodTimeUnit;
}

Util::TimeUnit ModelInfo::getWarmUpPeriodTimeUnit() const {
    return _warmUpPeriodTimeUnit;
}

void ModelInfo::setTerminatingCondition(std::string _terminatingCondition) {
    this->_terminatingCondition = _terminatingCondition;
}

std::string ModelInfo::getTerminatingCondition() const {
    return _terminatingCondition;
}


void ModelInfo::loadInstance(std::map<std::string, std::string>* fields) {
    this->_analystName = (*fields->find("analystName")).second;
    this->_description = (*fields->find("description")).second;
    this->_name = (*fields->find("name")).second;
    this->_numberOfReplications = std::stoi((*fields->find("numberOfReplications")).second);
    this->_projectTitle = (*fields->find("projectTitle")).second;
    this->_replicationLength = std::stod((*fields->find("replicationLength")).second);
    this->_replicationLengthTimeUnit = static_cast<Util::TimeUnit>(std::stoi((*fields->find("replicationLengthTimeUnit")).second));
    this->_terminatingCondition = (*fields->find("terminatingCondition")).second;
    this->_version = (*fields->find("version")).second;
    this->_warmUpPeriod = std::stod((*fields->find("warmUpTime")).second);
    this->_warmUpPeriodTimeUnit = static_cast<Util::TimeUnit>(std::stoi((*(fields->find("warmUpTimeTimeUnit"))).second));
}


std::map<std::string, std::string>* ModelInfo::saveInstance() {
    std::map<std::string, std::string>* fields = new std::map<std::string, std::string>();
    fields->emplace("typename", "ModelInfo");
    fields->emplace("analystName", getAnalystName());
    fields->emplace("description", getDescription());
    fields->emplace("name", getName());
    fields->emplace("numberOfReplications", std::to_string(getNumberOfReplications()));
    fields->emplace("projectTitle", getProjectTitle());
    fields->emplace("replicationLength", std::to_string(getReplicationLength()));
    fields->emplace("replicationLengthTimeUnit", std::to_string(static_cast<int> (getReplicationLengthTimeUnit())));
    fields->emplace("terminatingCondition", getTerminatingCondition());
    fields->emplace("version", getVersion());
    fields->emplace("warmUpTime", std::to_string(getWarmUpPeriod()));
    fields->emplace("warmUpTimeTimeUnit", std::to_string(static_cast<int> (getWarmUpPeriodTimeUnit())));
    return fields;
}
