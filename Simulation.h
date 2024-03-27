#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>
#include <map>
#include <memory>

#include "Tempolimit.h"
#include "Kreuzung.h"

using namespace std;

class Simulation{
public:

private:
	map<string, shared_ptr<Kreuzung>> kreuzungenMap;
};

#endif /* SIMULATION_H_ */