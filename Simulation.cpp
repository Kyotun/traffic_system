#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <sstream>

#include "Fahrrad.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "PKW.h"
#include "Simulation.h"
#include "SimuClient.h"
#include "Tempolimit.h"
#include "Weg.h"

using namespace std;
extern double dGlobaleZeit;

// Wenn die Laenge des Names der Kreuzung nicht drei ist, gibt eine Ausnahme zurueck.
void Simulation::vCheckKreuzungName(string name){
	if(name.length() != 3){
		throw runtime_error("Name der Kreuzung soll wie Kr1 aussehen. Gegeben: " + name);
	}
}

// Waehlt ein Tempolimit aus, nach der gegebenen integer Zahl.
Tempolimit Simulation::convertTempolimit(int iTempolimit){
	switch(iTempolimit){
		case 1:
			return Innerorts;
			break;
		case 2:
			return Landstrasse;
			break;
		case 3:
			return Autobahn;
			break;
		default:
			return Autobahn;
			break;
	}
}

