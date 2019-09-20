/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sequence.h
 * Author: rlcancian
 *
 * Created on 03 de Junho de 2019, 15:12
 */

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "ModelElement.h"
#include "ElementManager.h"
#include "PluginInformation.h"
#include "Station.h"

class Sequence : public ModelElement {
public:
    class SequenceStep {
    public:
	Station* _station;
	std::list<std::string>* _assignments;
    };
public:
    Sequence(ElementManager* elems);
    Sequence(ElementManager* elems, std::string name);
    Sequence(const Sequence& orig);
    virtual ~Sequence();
public:
    virtual std::string show();
public: // static 
    static PluginInformation* GetPluginInformation();
    static ModelElement* LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields);
public:
protected:
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
    virtual bool _check(std::string* errorMessage);
private:
    ElementManager* _elems;
private:

};

#endif /* SEQUENCE_H */

