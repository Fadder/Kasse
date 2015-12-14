/*
 * Kassierer.cpp
 *
 *  Created on: 12.12.2015
 *      Author: work
 */

#include <string>
#include <iostream>
#include "Kassierer.h"
#include "Kasse.h"
#include "Person.h"
#include <odemx/base/Process.h>
using namespace odemx::random;
using odemx::base::Process;
using odemx::base::Simulation;
using namespace std;

Kassierer::Kassierer(Simulation& sim) : Person(sim, "Kassierer"), aktuelleWare(0,"Null", 0, false) {
	// TODO Auto-generated constructor stub

}

Kassierer::~Kassierer() {
	// TODO Auto-generated destructor stub
}

int Kassierer::main() {
	Band& band = static_cast<Kasse&>( this->getSimulation() ).band;
	Ablage& ablage = static_cast<Kasse&>( this->getSimulation() ).ablage;
	Kasse& kasse = static_cast<Kasse&>( this->getSimulation() );

	while(true) {

		//Lebenslauf
		//Kassierer wartet auf den naechsten Kunden
		//und kassiert alle Waren des Kunden
		message("wartet auf naechsten Kunden");
		aktuelleWare = band.wareEntnehmen();
		message("faengt an eine Ware aus dem Band zu entnehmen");
		holdFor( this->dauerEinerWarenbewegung() );
		message("hat dem Band eine Ware entnohmen", aktuelleWare);


		kasse.kundenanzahlInkrementieren();//neuer Kunde wird abgefertigt
		kasse.umsatzErhoehen( aktuelleWare.kosten() ); //Umsatz der Kasse um den Preis der Ware erhoehen

		//message("legt diese Ware in die Ablage", aktuelleWare);
		//holdFor( this->dauerEinerWarenbewegung() );
		ablage.wareLegen(aktuelleWare);
		message("hat diese Ware in die Ablage gelegt", aktuelleWare);


		while( !(aktuelleWare.letzteWareDesKunden()) ) {
			aktuelleWare = band.wareEntnehmen();
			message("faengt an eine Ware aus dem Band zu entnehmen");
			holdFor( this->dauerEinerWarenbewegung() );
			message("hat dem Band eine Ware entnohmen", aktuelleWare);


			kasse.umsatzErhoehen( aktuelleWare.kosten() ); //Umsatz der Kasse um den Preis der Ware erhoehen

			//message("legt diese Ware in die Ablage", aktuelleWare);
			//holdFor( this->dauerEinerWarenbewegung() );
			ablage.wareLegen(aktuelleWare);
			message("hat diese Ware in die Ablage gelegt", aktuelleWare);

		}

		message("warte 20 sek. und bedient danach den naechsten Kunden");
		holdFor(20);

		//alle Waren des Kunden sind kassiert, jetzt schickt der Kassierer dem Kunden die Rechnung
	}

	return 0;

}
