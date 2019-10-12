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
    Util::identification getId() const;
    void setName(std::string _name);
    std::string getName() const;
    std::string getTypename() const;
public: // static
    static ModelElement* LoadInstance(std::map<std::string, std::string>* fields); // TODO: return ModelComponent* ?
    static std::map<std::string, std::string>* SaveInstance(ModelElement* element);
    static bool Check(ModelElement* element, std::string* errorMessage);
    static void CreateInternalElements(ModelElement* element);

public:
    virtual std::string show();
    
protected: // must be overriden by derived classes
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
protected: // could be overriden by derived classes
    virtual bool _check(std::string* errorMessage);
    virtual ParserChangesInformation* _getParserChangesInformation();
    virtual void _createInternalElements(); ///< This method is necessary only for those components that instantiate internal elements that must exist before simulation starts and even before model checking. That's the case of components that have internal StatisticsCollectors, since others components may refer to them as expressions (as in "TVAG(ThisCSTAT)") and therefore the element must exist when checking such expression    
protected:
    Util::identification _id;
    std::string _name;
    std::string _typename;
};

#endif /* MODELELEMENT_H */

