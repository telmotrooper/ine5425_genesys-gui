/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Group.h
 * Author: rlcancian
 *
 * Created on 12 de Junho de 2019, 19:00
 */

#ifndef GROUP_H
#define GROUP_H

#include "ModelElement.h"
#include "Entity.h"
#include <map>
#include <list>

class Group : public ModelElement {
public:
    Group(ElementManager* elems);
    Group(ElementManager* elems, std::string name);
    Group(const Group& orig);
    virtual ~Group();
public:
    virtual std::string show();
public:
    static PluginInformation* GetPluginInformation();
    static ModelElement* LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields);
public:
    void insertElement(Entity* element);
    void removeElement(Entity* element);
    unsigned int size();
    Entity* first();
public:
    void initBetweenReplications();
protected:
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
    //virtual std::list<std::map<std::string,std::string>*>* _saveInstance(std::string type);
    virtual bool _check(std::string* errorMessage);
private:
    void _initCStats();
private:
    ElementManager* _elements;
private: //1::n
    List<Entity*>* _list = new List<Entity*>();
private: //1::1
    StatisticsCollector* _cstatNumberInGroup;
};

#endif /* GROUP_H */

