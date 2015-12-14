/*
 * Band.h
 *
 *  Created on: Dec 13, 2015
 *      Author: vincent
 */

#ifndef BAND_H_
#define BAND_H_

#include <odemx/odemx.h>
#include "WareUndRechnung.h"

class Band {
private:
	odemx::synchronization::Bin exclusiveNutzung;
	odemx::synchronization::PortTail::Ptr warenUebertragung;
	const int bandkapazitaet = 20;
public:
	Band(odemx::base::Simulation &sim);
	void bandExclusivBenutzen();
	void bandFreigeben();
	void wareAufsBandLegen(Ware* ware);
	std::unique_ptr<Ware> wareEntnehmen();
	virtual ~Band();
};

#endif /* BAND_H_ */
