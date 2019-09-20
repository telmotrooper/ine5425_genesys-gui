/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Match.h
 * Author: rlcancian
 *
 * Created on 03 de Junho de 2019, 15:14
 */

#ifndef MATCH_H
#define MATCH_H

#include "ModelComponent.h"

/*!
 This component ...
 */
class Match : public ModelComponent {
public: // constructors
    Match(Model* model);
    Match(const Match& orig);
    virtual ~Match();
public:  // virtual
    virtual std::string show();
public:  // static
    static PluginInformation* GetPluginInformation();
    static ModelComponent* LoadInstance(Model* model, std::map<std::string, std::string>* fields);
protected:  // virtual
    virtual void _execute(Entity* entity);
    virtual void _initBetweenReplications();
    virtual bool _loadInstance(std::map<std::string, std::string>* fields);
    virtual std::map<std::string, std::string>* _saveInstance();
    virtual bool _check(std::string* errorMessage);
private: // methods
private: // attributes 1:1
private: // attributes 1:n
};


#endif /* MATCH_H */

