/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectionManager.cpp
 * Author: rlcancian
 * 
 * Created on 1 de Julho de 2019, 18:39
 */

#include "ConnectionManager.h"

ConnectionManager::ConnectionManager() {
}

ConnectionManager::ConnectionManager(const ConnectionManager& orig) {
}

ConnectionManager::~ConnectionManager() {
}

unsigned int ConnectionManager::size() {
    return _nextConnections->size();
}

ModelComponent* ConnectionManager::front() {
    return _nextConnections->front()->first;
}

ModelComponent* ConnectionManager::getAtRank(unsigned int rank) {
    return _nextConnections->getAtRank(rank)->first;
}

Connection* ConnectionManager::frontConnection() {
    return _nextConnections->front();
}

Connection* ConnectionManager::getConnectionAtRank(unsigned int rank) {
    return _nextConnections->getAtRank(rank);
}

void ConnectionManager::insert(ModelComponent* component, unsigned int inputNumber) {
    _nextConnections->insert(new Connection(component, inputNumber));
}

std::list<Connection*>* ConnectionManager::getList() const {
    return _nextConnections->getList();
}
