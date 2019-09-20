/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModelElement.h
 * Author: rafael.luiz.cancian
 *
 * Created on 21 de Junho de 2018, 19:40
 */

#ifndef MODELELEMENT_H
#define MODELELEMENT_H

#include <string>
#include <list>
#include <vector>
#include "Util.h"

#include "ParserChangesInformation.h"

/*!
 * This class is the basis for any element of the model (such as Queue, Resource, Variable, etc.) and also for any component of the model. 
 * It has the infrastructure to read and write on file and to verify symbols.
 */
class ModelElement {
public:
    ModelElement(std::string elementTypename);
    ModelElement(const ModelElement& orig);
    virtual ~ModelElement();

public: // get & set
    Util::identitifcation getId() const;
    void setName(std::string _name);
    std::string getName() const;
    std::string getTypename() const;
public: // static
    static ModelElement* LoadInstance(std::map<std::string, std::string>* fields); // TODO: return ModelComponent* ?
    static std::map<std::string, std::string>* SaveInstance(ModelElement* element);
    static bool Check(ModelElement* element, std::string* errorMessage);
public:
    virtual std::string show();
    bool generateReportInformation() const;
    
protected: // must be overriden by derived classes
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
protected: // could be overriden by derived classes
    virtual bool _check(std::string* errorMessage);
    virtual ParserChangesInformation* _getParserChangesInformation();
protected:
    Util::identitifcation _id;
    std::string _name;
    std::string _typename;
};

#endif /* MODELELEMENT_H */

