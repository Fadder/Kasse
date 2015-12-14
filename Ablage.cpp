#include "Ablage.h"

#include <odemx/odemx.h>
#include "WareUndRechnung.h"
using namespace std;
using namespace odemx::synchronization;

Ablage::Ablage(Simulation& sim)
{
	ablageKapazitaet = 10000; //default
	warenUebertragung = PortTailT<Ware>::create(sim, "warenUebertragung", PortMode::WAITING_MODE,
			ablageKapazitaet);
	exklusiveNutzung = new Bin(sim, "exklusiveNutzung", 1);
}

Ware Ablage::wareEntnehmen()
{
	return(*warenUebertragung->getHead()->get());
}

void Ablage::wareLegen(Ware zuLegen)
{
	warenUebertragung->put(zuLegen);
}

void Ablage::kundeMoechteBenutzen()
{
	if(exklusiveNutzung->getTokenNumber())
	{
		exklusiveNutzung->take(1); //und return(true)??
	}
}

void Ablage::furNaechstenKundenFreigeben()
{
	exklusiveNutzung->give(1);
}

void Ablage::ablageKapazitaetSetzenAuf(int anzWaren)
{
	ablageKapazitaet = anzWaren;
}
