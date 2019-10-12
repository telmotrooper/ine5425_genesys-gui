/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Station.h
 * Author: rlcancian
 *
 * Created on 03 de Junho de 2019, 15:12
 */

#ifndef STATION_H
#define STATION_H

#include "ModelElement.h"
#include "ElementManager.h"
#include "Plugin.h"
#include "Entity.h"

class Station: public ModelElement {
public:
    Station(ElementManager* elems);
    Station(ElementManager* elems, std::string name);
    Station(const Station& orig);
    virtual ~Station();
public:
    virtual std::string show();
public: // static 
    static PluginInformation* GetPluginInformation();
    static ModelElement* LoadInstance(ElementManager* elems, std::map<std::string, std::string>* fields);
public:
    void initBetweenReplications();
    void enter(Entity* entity);
    void leave(Entity* entity);
    void setEnterIntoStationComponent(ModelComponent* _enterIntoStationComponent);
    ModelComponent* getEnterIntoStationComponent() const;
protected:
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
    virtual bool _check(std::string* errorMessage);
    virtual void _createInternalElements();
private:
    void _initCStats();
private:
    ElementManager* _elems;
private:
    StatisticsCollector* _cstatNumberInStation;
    StatisticsCollector* _cstatTimeInStation;
    unsigned int _numberInStation=0;
    ModelComponent* _enterIntoStationComponent;
};

#endif /* STATION_H */

