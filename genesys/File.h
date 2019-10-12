/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.h
 * Author: rlcancian
 *
 * Created on 20 de Fileembro de 2019, 20:07
 */

#ifndef FILE_H
#define FILE_H


#include "ModelElement.h"
#include "ElementManager.h"
#include "ParserChangesInformation.h"
#include "PluginInformation.h"

class File: public ModelElement {
public:
    File(ElementManager* elems);
    File(ElementManager* elems, std::string name);
    File(const File& orig);
    virtual ~File();
public: // static
    static ModelElement* LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields); 
    static PluginInformation* GetPluginInformation();
public:
    virtual std::string show();

protected: // must be overriden by derived classes
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
protected: // could be overriden by derived classes
    virtual bool _check(std::string* errorMessage);
    virtual ParserChangesInformation* _getParserChangesInformation();
private:
    ElementManager* _elems;
};

#endif /* FILE_H */

