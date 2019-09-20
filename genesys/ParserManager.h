/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ParserManager.h
 * Author: rlcancian
 *
 * Created on 11 de Setembro de 2019, 20:34
 */

#ifndef PARSERMANAGER_H
#define PARSERMANAGER_H

#include "ParserChangesInformation.h"

class ParserManager {
public:
    
    struct NewParser {
	std::string bisonFilename;
	std::string flexFilename;
	std::string compiledParserFilename;	
    };
    struct GenerateNewParserResult {
	bool result;
	std::string bisonMessages;
	std::string lexMessages;
	std::string compilationMessages;
	NewParser newParser;
    };
public:
    ParserManager();
    ParserManager(const ParserManager& orig);
    virtual ~ParserManager();
public:
    ParserManager::GenerateNewParserResult generateNewParser(ParserChangesInformation* changes);
    bool connectNewParser(ParserManager::NewParser newParser);
private:
};

#endif /* PARSERMANAGER_H */

