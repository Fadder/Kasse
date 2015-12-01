/*
 * Kasse.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: vincent
 */

#include <iostream>
#include "Kasse.h"

Kasse::Kasse(Simulation& sim): Process(sim, "Kasse"){}

Kasse::~Kasse() {}

int Kasse::main(){
	// TODO
	while(true){
		holdFor(1);
		cout << " Warte auf Kunden..." << endl;
	}
	return 0;
}

