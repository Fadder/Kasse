#ifndef BEZAHLUNG_H_
#define BEZAHLUNG_H_

#include <odemx/odemx.h>
#include "WareUndRechnung.h"
using namespace std;
using namespace odemx::synchronization;

class Bezahlung
{
	shared_ptr<PortTailT<Rechnung>> zahlungsUebertragung;
public:
	Bezahlung(Simulation& sim);
	~Bezahlung(){}
	void rechnungZeigen(Rechnung rechnung);
	void rechnungBezahlen(Rechnung rechnung);
};


#endif /* BEZAHLUNG_H_ */
