/*
 * Kunde.cpp
 *
 *  Created on: 12.12.2015
 *      Author: work
 */

#include "Band.h"
#include <string>
#include <iostream>
#include "Kunde.h"
#include "Kasse.h"
#include "Person.h"
#include "Ablage.h"
#include "WareUndRechnung.h"
#include <odemx/odemx.h>
using namespace odemx::random;
using odemx::base::Process;
using odemx::base::Simulation;
using namespace std;

Kunde::Kunde(Simulation& sim) : Person(sim, "Kunde"), anzahlDerWaren(sim, "Warenanzahl", 3, 1),
								kostenProProdukt(sim, "Produktkosten", 0.2), warenAnzahlPois(sim, "Warenanzahl", 3)
{
	this->einkaufskorbFuellen();
}

Kunde::~Kunde() {
	// TODO Auto-generated destructor stub
}

//berechnet die Warenanzahl, die ein Kunde haben soll
//dabei wird die Zufallszahl gerundet:
//Nachkommastelle <= 0.5 ----> wird abgerundet
//Nachkommastelle > 0.5 ----> wird aufgerundet
//negative Zahlen und Null werden ignoriert
int Kunde::zufaelligeWarenAnzahl() {
	int ret;

	while(true) {
		double i = anzahlDerWaren.sample();

		if(i <= 0) { continue; } //negative Zahl bzw. Null --> wird ignoriert

		ret = (int)i; //fuer die Differenzbildung, um die Nachkommastelle zu bekommen

		double j;
		j = i - ret; //Nachkommastelle


		if(j <= 0.5) {
			return ret;
		}
		else {
			return ++ret;
		}
	}
}

int Kunde::zufaelligeWarenAnzahlPoisson() {
	int ret;

	while(true) {
		ret = warenAnzahlPois.sample();
		if(ret > 0) {
			break;
		}
	}
	return ret;
}

double Kunde::zufaelligerPreisEinerWare() {
	double ret;

	while(true) {
		ret = kostenProProdukt.sample();
		if(ret > 0) {
			break;
		}
	}
	return ret;
}

void Kunde::einkaufskorbFuellen() {
	int warenanzahl = zufaelligeWarenAnzahlPoisson();
	einkaufskorb.reserve(warenanzahl);
	//cout << "Warenanzahl: " << warenanzahl << endl;

	int id = 0;
	for(int i=1; i < warenanzahl; i++) {
		id = i;
		einkaufskorb.push_back( Ware{zufaelligerPreisEinerWare(), this->getLabel(), id } );
	}
	id++;
	einkaufskorb.push_back( Ware{zufaelligerPreisEinerWare(), this->getLabel(), id,  true} ); // letzte Ware des Kunden
}

int Kunde::main() {
	Band& band = static_cast<Kasse&>( this->getSimulation() ).band;
	Ablage& ablage = static_cast<Kasse&>( this->getSimulation() ).ablage;


	//Lebenslauf------------------------------
	//Kunde versucht das Band exklusiv zu benutzen, indem er einen Token nimmt und
	//somit die restlichen Kunden warten muessen, bis er diesen Token zurueck gibt
	message("hat sich an das Band angestellt");
	band.bandExclusivBenutzen();
	message("ist an der Reihe seine Waren auf das Band zu legen");

	//legt seine Waren auf das Band
	for(unsigned int i = 0; i < einkaufskorb.size(); i++) {
			message("faengt an eine Ware auf das Band zu legen");

			//holdFor ist vor "band.wareAufsBandLegen(einkaufskorb[i])", weil sonst die Ware schon vor der
			//eigentlichen Warenbewegung auf dem Band waere
			holdFor( this->dauerEinerWarenbewegung() );
			//band.wareAufsBandLegen(einkaufskorb[i]);
			band.wareAufsBandLegen( &(einkaufskorb[i]) );

			message("Ware wurde auf das Band gelegt", einkaufskorb[i]);

	}

	//alle Waren sind auf das Band gelegt, deswegen verlaesst der Kunde das Band
	band.bandFreigeben();
	message("hat alle seine Waren auf das Band gelegt und verlaesst das Band");


	//der Kunde moechte jetzt die Ablage benutzten
	message("steht vor der Ablage");
	ablage.kundeMoechteBenutzen();
	message("befindet sich in dem Ablagebereich");

	//der Kunde wartet auf seine Waren und legt diese in seinen Einkaufswagen
	Ware wareAusDerAblage(0,"Null", 0, false);
	do {
		wareAusDerAblage = ablage.wareEntnehmen();
		message("faengt an eine Ware aus der Ablage zu entnehmen");
		holdFor( this->dauerEinerWarenbewegung() );
		message("hat eine Ware aus der Ablage entnohmen", wareAusDerAblage);


	} while ( !(wareAusDerAblage.letzteWareDesKunden()) );

	//Alle Waren wurden in den Einkaufswagen gelegt
	//Jetzt wartet der Kunde auf die Rechnung
	message("wartet auf die Rechnung");



	//Kunde hat bezahlt und verlaesst jetzt die Ablage
	ablage.furNaechstenKundenFreigeben();

	return 0;
}

