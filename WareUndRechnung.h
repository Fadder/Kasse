#ifndef WAREUNDRECHNUNG_H_
#define WAREUNDRECHNUNG_H_

#include <odemx/odemx.h>
using namespace odemx::synchronization;

class Ware : public PortData {
	int preis;
	bool letzteWare = false;

public:
	Ware(int preis, bool istLetzteWare = false);
	virtual ~Ware() {}

	bool letzteWareDesKunden();
	int kosten(); //gibt den Preis der Ware zurueck
};

class Rechnung : public PortData {
	int betrag;
public:
	Rechnung(int betrag);
	virtual ~Rechnung() {}

	int getBetrag();
};

#endif /* WAREUNDRECHNUNG_H_ */
