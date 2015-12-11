/*
 * WareUndRechnung.cpp
 *
 *  Created on: 11.12.2015
 *      Author: work
 */

#include "WareUndRechnung.h"

#include <odemx/odemx.h>
using namespace odemx::synchronization;

/*----Implementation von "Ware"----*/
Ware::Ware(int preis, bool istLetzteWare) : preis(preis), letzteWare(istLetzteWare) {}

bool Ware::letzteWareDesKunden() { return letzteWare; }
int Ware::kosten() { return preis; }


/*----Implementation von "Rechnung"----*/
Rechnung::Rechnung(int betrag) { this->betrag = betrag; }

int Rechnung::getBetrag() { return betrag; }


