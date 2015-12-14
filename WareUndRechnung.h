#ifndef WAREUNDRECHNUNG_H_
#define WAREUNDRECHNUNG_H_

#include <string>
#include <odemx/odemx.h>
using namespace odemx::synchronization;

class Ware : public PortData {
	double preis;
	bool letzteWare = false;
public:
	std::string besitzer;
	int id;


	Ware(double preis, std::string besitzer, int id , bool istLetzteWare = false);
	virtual ~Ware() {}

	bool letzteWareDesKunden();
	double kosten(); //gibt den Preis der Ware zurueck
};

class Rechnung : public PortData {
	double betrag;
public:
	Rechnung(double betrag);
	virtual ~Rechnung() {}

	double getBetrag();
};

#endif /* WAREUNDRECHNUNG_H_ */
