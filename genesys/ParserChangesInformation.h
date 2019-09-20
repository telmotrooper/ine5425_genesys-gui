/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParserChangesInformation.h
 * Author: rlcancian
 *
 * Created on 11 de Setembro de 2019, 20:42
 */

#ifndef PARSERCHANGESINFORMATION_H
#define PARSERCHANGESINFORMATION_H

#include <string>
#include <list>

class ParserChangesInformation {
public:
    typedef std::string token;
    typedef std::string typeobj;
    typedef std::string lexinclude;
    typedef std::pair<std::string,std::string> production;
    typedef std::pair<std::string,std::string> lexicalelement;
public:
    ParserChangesInformation();
    ParserChangesInformation(const ParserChangesInformation& orig);
    virtual ~ParserChangesInformation();

public: // gets and sets
    std::list<ParserChangesInformation::lexicalelement*>* getLexicalElementToRemove() const;
    std::list<ParserChangesInformation::lexicalelement*>* getLexicalElementToAdd() const;
    std::list<ParserChangesInformation::lexinclude*>* getLexIncludeToRemove() const;
    std::list<ParserChangesInformation::lexinclude*>* getLexIncludeToAdd() const;
    std::list<ParserChangesInformation::production*>* getProductionToRemove() const;
    std::list<ParserChangesInformation::production*>* getProductionToAdd() const;
    std::list<ParserChangesInformation::typeobj*>* getTypeobjToRemove() const;
    std::list<ParserChangesInformation::typeobj*>* getTypeobjToAdd() const;
    std::list<ParserChangesInformation::token*>* getTokensToRemove() const;
    std::list<ParserChangesInformation::token*>* getTokensToAdd() const;
private:
    std::list<token*>* _tokensToAdd = new std::list<token*>();
    std::list<token*>* _tokensToRemove = new std::list<token*>();
    std::list<typeobj*>* _typeobjToAdd = new std::list<typeobj*>();
    std::list<typeobj*>* _typeobjToRemove = new std::list<typeobj*>();
    std::list<production*>* _productionToAdd = new std::list<production*>();
    std::list<production*>* _productionToRemove = new std::list<production*>();
    std::list<lexinclude*>* _lexIncludeToAdd = new std::list<lexinclude*>();
    std::list<lexinclude*>* _lexIncludeToRemove = new std::list<lexinclude*>();
    std::list<lexicalelement*>* _lexicalElementToAdd = new std::list<lexicalelement*>();
    std::list<lexicalelement*>* _lexicalElementToRemove = new std::list<lexicalelement*>();
    
};

#endif /* PARSERCHANGESINFORMATION_H */

