/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rafael.luiz.cancian
 *
 * Created on 21 de Junho de 2018, 12:47
 */

#include <iostream>
#include <thread>
#include "Traits.h"

/*
 * This is the MAIN application of GenESyS. It just calls the Application specificied on the configuration file.
 */
int main(int argc, char** argv) {
    // do not change it. Set you own application in Traits file => Traits<GenesysApplication_if>::Application
    GenesysApplication_if *app = new Traits<GenesysApplication_if>::Application();
    int res = app->main(argc, argv);
    // that's all folks!!
    std::cout << "Quiting application." << std::endl;
    for (unsigned int i=0; i<1e6;i++)
	std::this_thread::yield(); // Give the IDE a try to output previous traces
    return res;
}

