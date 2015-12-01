/*
 * Kasse.h
 *
 *  Created on: Dec 1, 2015
 *      Author: vincent
 */

#ifndef KASSE_H_
#define KASSE_H_

#include <odemx/odemx.h>
#include <queue>
#include "Kunde.h"
#include "Ware.h"

using namespace odemx;
using namespace std;

class Kasse : public Process {

private:
  queue<Kunde> schlange;
  queue<Ware> band;
  queue<Ware> ablage;

public:
  Kasse(Simulation& sim);
  virtual ~Kasse();

protected:
  int main();
};

#endif /* KASSE_H_ */
