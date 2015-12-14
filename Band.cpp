/*
 * Band.cpp
 *
 *  Created on: Dec 13, 2015
 *      Author: vincent
 */

#include "Band.h"
#include <iostream>

using namespace odemx::synchronization;

Band::Band(odemx::base::Simulation& sim)
: exclusiveNutzung(sim, "exclusiveNutzung", 1)
, warenUebertragung(PortTail::create(sim, "warenUebertragung"))
{}

void
Band::bandExclusivBenutzen(){
	exclusiveNutzung.take(1);
	std::cout << "Band wird exclusiv benutzt" << std::endl;
}

void
Band::bandFreigeben(){
	exclusiveNutzung.give(1);
	std::cout << "Band wird freigegeben" << std::endl;
}

void
Band::wareAufsBandLegen(Ware* ware){
	warenUebertragung->put(ware);
	std::cout << "Ware wird aufs Band gelegt" << std::endl;
}

std::unique_ptr<Ware>
Band::wareEntnehmen(){
	PortTail::HeadPtr hptr = warenUebertragung->getHead();
	std::unique_ptr<Ware> uptr = std::unique_ptr<Ware>(static_cast<Ware*>(*hptr->get()));
	std::cout << "Ware wird vom Band genommen" << std::endl;
	return uptr;
}

Band::~Band() {}

