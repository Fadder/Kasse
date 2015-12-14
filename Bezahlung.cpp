#include <odemx/odemx.h>
#include "WareUndRechnung.h"
#include "Bezahlung.h"
using namespace std;
using namespace odemx::synchronization;

Bezahlung::Bezahlung(Simulation& sim)
{
	zahlungsUebertragung = PortTailT<Rechnung>::create(sim, "zahlungsUebertragung"
			, PortMode::WAITING_MODE);
}
void Bezahlung::rechnungZeigen(Rechnung rechnung)
{
	zahlungsUebertragung->put(rechnung);
}
void Bezahlung::rechnungBezahlen(Rechnung rechnung)
{
	zahlungsUebertragung->getHead()->get(); //return??
}
