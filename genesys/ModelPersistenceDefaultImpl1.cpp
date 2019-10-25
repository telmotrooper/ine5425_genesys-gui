/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModelPersistenceDefaultImpl1.cpp
 * Author: rafael.luiz.cancian
 * 
 * Created on 20 de Maio de 2019, 20:41
 */

#include "ModelPersistenceDefaultImpl1.h"
#include <fstream>
#include <ctime>
#include <regex>
#include <cassert>
#include "ModelComponent.h"
#include "Simulator.h"

ModelPersistenceDefaultImpl1::ModelPersistenceDefaultImpl1(Model* model) {
    _model = model;
}

std::map<std::string, std::string>* ModelPersistenceDefaultImpl1::_getSimulatorInfoFieldsToSave() {
    std::map<std::string, std::string>* fields = new std::map<std::string, std::string>();
    fields->emplace("typename", "SimulatorInfo");
    fields->emplace("name", _model->getParentSimulator()->getName());
    fields->emplace("version", _model->getParentSimulator()->getVersion());
    return fields;
}

bool ModelPersistenceDefaultImpl1::save(std::string filename) {
    _model->getTraceManager()->trace(Util::TraceLevel::blockArrival, "Saving file \"" + filename + "\"");
    Util::IncIndent();
    std::list<std::string> *simulInfosToSave, *modelInfosToSave, *modelElementsToSave, *modelComponentsToSave;
    {
	//bool res = true;
	std::map<std::string, std::string>* fields;
	fields = _getSimulatorInfoFieldsToSave();
	simulInfosToSave = _adjustFieldsToSave(fields);
	// save model own infos
	fields = _model->getInfos()->saveInstance();
	modelInfosToSave = _adjustFieldsToSave(fields);
	// save infras
	modelElementsToSave = new std::list<std::string>();
	std::list<std::string>* infraTypenames = _model->getElementManager()->getElementTypenames();
	for (std::list<std::string>::iterator itTypenames = infraTypenames->begin(); itTypenames != infraTypenames->end(); itTypenames++) {
	    if ((*itTypenames) != Util::TypeOf<StatisticsCollector>() && (*itTypenames) != Util::TypeOf<Counter>()) { // STATISTICSCOLLECTR and COUNTERs do NOT need to be saved
		List<ModelElement*>* infras = _model->getElementManager()->getElements((*itTypenames));
		_model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, "Writing elements of type \"" + (*itTypenames) + "\":");
		Util::IncIndent();
		{
		    for (std::list<ModelElement*>::iterator it = infras->getList()->begin(); it != infras->getList()->end(); it++) {
			_model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, "Writing " + (*itTypenames) + " \"" + (*it)->getName() + "\"");
			fields = (*it)->SaveInstance((*it));
			Util::IncIndent();
			modelElementsToSave->merge(*_adjustFieldsToSave(fields));
			Util::DecIndent();
		    }
		}
		Util::DecIndent();
	    }
	}
	// save components
	_model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, "Writing components\":");
	//List<ModelComponent*>* components = this->_model->getComponents();
	modelComponentsToSave = new std::list<std::string>();
	Util::IncIndent();
	{
	    for (std::list<ModelComponent*>::iterator it = _model->getComponentManager()->begin(); it != _model->getComponentManager()->end(); it++) {
		fields = (*it)->SaveInstance((*it));
		Util::IncIndent();
		modelComponentsToSave->merge(*_adjustFieldsToSave(fields));
		Util::DecIndent();
	    }
	}
	Util::DecIndent();
	// SAVE FILE
	_model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, "Saving file");
	Util::IncIndent();
	{
	    // open file
	    std::ofstream savefile;
	    savefile.open(filename, std::ofstream::out);
	    savefile << "# Genesys simulation model " << std::endl;
	    time_t now = time(0);
	    char* dt = ctime(&now);
	    savefile << "# Last saved on " << dt;
	    savefile << "# simulator infos" << std::endl;
	    _saveContent(simulInfosToSave, &savefile);
	    savefile << "# model infos" << std::endl;
	    _saveContent(modelInfosToSave, &savefile);
	    savefile << "# model elements" << std::endl;
	    _saveContent(modelElementsToSave, &savefile);
	    savefile << "# model components" << std::endl;
	    _saveContent(modelComponentsToSave, &savefile);
	    savefile.close();
	}
	Util::DecIndent();
    }
    Util::DecIndent();
    return true; // todo: check if save really saved successfully
}

void ModelPersistenceDefaultImpl1::_saveContent(std::list<std::string>* content, std::ofstream* file) {
    for (std::list<std::string>::iterator it = content->begin(); it != content->end(); it++) {
	*file << (*it) << std::endl << std::endl;
    }
}

bool ModelPersistenceDefaultImpl1::_loadFields(std::string line) {
    //std::regex regex{R"([=]+)"}; // split on space R"([\s]+)" TODO: HOW SEPARATOR WITH MORE THAN ONE CHAR
    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, line);
    bool res = true;
    std::regex regex{R"([;]+)"}; // split on "; ".TODO: How change it by the attribute _linefieldseparator ??
    std::sregex_token_iterator tit{line.begin(), line.end(), regex, -1};
    std::list<std::string> lstfields{tit,{}};
    // for each field, separate key and value and form a map
    try {
	std::map<std::string, std::string>* fields = new std::map<std::string, std::string>();
	regex = {R"([=]+)"};
	std::vector<std::string> veckeyval; //{it,{}};
	for (std::list<std::string>::iterator it = lstfields.begin(); it != lstfields.end(); it++) {
	    //std::cout << (*it) << std::endl;
	    tit = {(*it).begin(), (*it).end(), regex, -1};
	    veckeyval = {tit,{}};
	    trim((veckeyval[0]));
	    if (veckeyval[0] != "") {
		if (veckeyval.size() > 1) {
		    trim((veckeyval[1]));
		    fields->emplace(veckeyval[0], veckeyval[1]);
		} else {
		    fields->emplace(veckeyval[0], "");
		}
	    }
	}
	// now the map<str,str> is ready. Look for the right class to load it
	Util::IncIndent();
	{
	    std::string thistypename = (*fields->find("typename")).second;
	    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, "loading " + thistypename + "");
	    if (thistypename == "SimulatorInfo") {
		this->_loadSimulatorInfoFields(fields);
	    } else if (thistypename == "ModelInfo") {
		_model->getInfos()->loadInstance(fields);
	    } else {
		// this should be a ModelComponent or ModelElement. 
		//std::string thistypename = (*fields->find("typename")).second;
		ModelElement* newTemUselessElement = ModelElement::LoadInstance(fields);
		if (newTemUselessElement != nullptr) {
		    newTemUselessElement->~ModelElement();
		    Plugin* plugin = this->_model->getParentSimulator()->getPluginManager()->find(thistypename);
		    if (plugin != nullptr) {
			res = plugin->loadAndInsertNew(_model, fields);
			// save fields for components, in order to allow to connect components after all of them have been loaded
			if (res && plugin->getPluginInfo()->isComponent()) {
			    _componentFields->insert(_componentFields->end(), fields);
			}
		    } else {
			_model->getTraceManager()->trace(Util::TraceLevel::errors, "Error loading file: Could not identity typename \"" + thistypename + "\"");
			res = false;
		    }
		} else {
		    _model->getTraceManager()->trace(Util::TraceLevel::errors, "Error loading file: Could not identity typename \"" + thistypename + "\"");
		    res = false;
		}

	    }
	}
	Util::DecIndent();
    } catch (...) {

    }
    return res;
}

void ModelPersistenceDefaultImpl1::_loadSimulatorInfoFields(std::map<std::string, std::string>* fields) {
}

bool ModelPersistenceDefaultImpl1::load(std::string filename) {
    //std::list<Plugin*> plugins = this->_model->getParent()->getPlugins();
    //plugins->front()->
    //return false;
    bool res = true;
    _model->getTraceManager()->trace(Util::TraceLevel::blockArrival, "Loading file \"" + filename + "\"");
    Util::IncIndent();
    _componentFields->clear();
    {
	std::ifstream modelFile;
	std::string inputLine;
	try {
	    modelFile.open(filename);
	    while (getline(modelFile, inputLine) && res) {
		//trim(&inputLine);
		if (inputLine.substr(0, 1) != "#" && !inputLine.empty()) {
		    //Util::IncIndent();
		    res &= _loadFields(inputLine);
		    //Util::DecIndent();
		}
	    }
	    modelFile.close();
	} catch (...) {
	    _model->getTraceManager()->trace(Util::TraceLevel::errors, "Error loading file \"" + filename + "\"");
	}
    }
    if (res) {
	// connect loaded components
	ComponentManager* cm = _model->getComponentManager();
	_model->getTraceManager()->trace(Util::TraceLevel::blockArrival, "Connecting loaded components");
	Util::IncIndent();
	{
	    for (std::list<std::map<std::string, std::string>*>::iterator it = _componentFields->begin(); it != _componentFields->end(); it++) {
		std::map<std::string, std::string>* fields = (*it);
		// find the component
		ModelComponent* thisComponent = nullptr;
		Util::identification thisId = std::stoi((*fields->find("id")).second);
		for (std::list<ModelComponent*>::iterator itcomp = cm->begin(); itcomp != cm->end(); itcomp++) {
		    if ((*itcomp)->getId() == thisId) {
			thisComponent = (*itcomp);
			break; // end inner for loop
		    }
		}
		assert(thisComponent != nullptr);

		// find the next components connected with this one
		unsigned short nextSize = std::stoi((*fields->find("nextSize")).second);
		for (unsigned short i = 0; i < nextSize; i++) {
		    Util::identification nextId = std::stoi((*fields->find("nextId" + std::to_string(i))).second);
		    unsigned short nextInputNumber = 0;
		    if (fields->find("nextInputNumber" + std::to_string(i)) != fields->end())
			nextInputNumber = std::stoi((*fields->find("nextInputNumber" + std::to_string(i))).second);

		    for (std::list<ModelComponent*>::iterator itcomp = cm->begin(); itcomp != cm->end(); itcomp++) {// connect the components 
			if ((*itcomp)->getId() == nextId) { // connect the components 
			    ModelComponent* nextComponent = (*itcomp);
			    thisComponent->getNextComponents()->insert(nextComponent, nextInputNumber);
			    _model->getTraceManager()->trace(Util::TraceLevel::blockInternal, thisComponent->getName() + " -> " + nextComponent->getName());
			    break;
			}
		    }
		}

	    }
	}
	Util::DecIndent();
    }
    Util::DecIndent();
    return res;
}

std::list<std::string>* ModelPersistenceDefaultImpl1::_adjustFieldsToSave(std::map<std::string, std::string>* fields) {
    std::list<std::string>* newList = new std::list<std::string>();
    std::string newStr;
    for (std::map<std::string, std::string>::iterator it = fields->begin(); it != fields->end(); it++) {
	newStr += (*it).first + "=" + (*it).second + this->_linefieldseparator;
    }
    _model->getTraceManager()->trace(Util::TraceLevel::mostDetailed, newStr);
    newList->push_back(newStr);
    return newList;
}

bool ModelPersistenceDefaultImpl1::isSaved() {
    return _isSaved;
}
