/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Leave.h
 * Author: rlcancian
 *
 * Created on 03 de Junho de 2019, 15:14
 */

#ifndef LEAVE_H
#define LEAVE_H

#include "ModelComponent.h"
#include "Station.h"

class Leave: public ModelComponent {
public:
    Leave(Model* model);
    Leave(const Leave& orig);
    virtual ~Leave();
public:
    virtual std::string show();
public:
    static PluginInformation* GetPluginInformation();
    static ModelComponent* LoadInstance(Model* model, std::map<std::string, std::string>* fields);
public:
    void setStation(Station* _station);
    Station* getStation() const;
public:
protected:
    virtual void _execute(Entity* entity);
    virtual void _initBetweenReplications();
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
    virtual bool _check(std::string* errorMessage);
private:
    Station* _station;
};

#endif /* LEAVE_H */

