/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParserChangesInformation.cpp
 * Author: rlcancian
 * 
 * Created on 11 de Setembro de 2019, 20:42
 */

#include "ParserChangesInformation.h"

ParserChangesInformation::ParserChangesInformation() {
}

ParserChangesInformation::ParserChangesInformation(const ParserChangesInformation& orig) {
}

ParserChangesInformation::~ParserChangesInformation() {
}

std::list<ParserChangesInformation::ParserChangesInformation::lexicalelement*>* ParserChangesInformation::getLexicalElementToRemove() const {
    return _lexicalElementToRemove;
}

std::list<ParserChangesInformation::lexicalelement*>* ParserChangesInformation::getLexicalElementToAdd() const {
    return _lexicalElementToAdd;
}

std::list<ParserChangesInformation::lexinclude*>* ParserChangesInformation::getLexIncludeToRemove() const {
    return _lexIncludeToRemove;
}

std::list<ParserChangesInformation::lexinclude*>* ParserChangesInformation::getLexIncludeToAdd() const {
    return _lexIncludeToAdd;
}

std::list<ParserChangesInformation::production*>* ParserChangesInformation::getProductionToRemove() const {
    return _productionToRemove;
}

std::list<ParserChangesInformation::production*>* ParserChangesInformation::getProductionToAdd() const {
    return _productionToAdd;
}

std::list<ParserChangesInformation::typeobj*>* ParserChangesInformation::getTypeobjToRemove() const {
    return _typeobjToRemove;
}

std::list<ParserChangesInformation::typeobj*>* ParserChangesInformation::getTypeobjToAdd() const {
    return _typeobjToAdd;
}

std::list<ParserChangesInformation::token*>* ParserChangesInformation::getTokensToRemove() const {
    return _tokensToRemove;
}

std::list<ParserChangesInformation::token*>* ParserChangesInformation::getTokensToAdd() const {
    return _tokensToAdd;
}

