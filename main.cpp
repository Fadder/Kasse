#include <odemx/odemx.h>
#include "Kasse.h"

using namespace odemx;

int main(int argc, char* argv[]){
	Simulation& sim = getDefaultSimulation();
	Kasse kasse(sim);

	kasse.activate();

	for (int i = 1; i < 5; ++i)
		sim.step();

	sim.runUntil(6);
	return 0;
}
