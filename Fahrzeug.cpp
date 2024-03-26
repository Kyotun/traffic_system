#include <string>
#include <iomanip>
#include <iostream>
#include <memory>
#include "Fahrzeug.h"
#include "Simulationsobjekt.h"
#include "Weg.h"

using namespace std;

extern double dGlobaleZeit;

// Fahrzeug-Objekt mit dem Name
Fahrzeug::Fahrzeug(string p_sName): Simulationsobjekt(p_sName){
}

// Fahrzeug-Objekt Konstruktor mit dem Name und der Geschwindigkeit
Fahrzeug::Fahrzeug(string p_sName, double p_dMaxGeschwindigkeit): Simulationsobjekt(p_sName),
		p_dMaxGeschwindigkeit((p_dMaxGeschwindigkeit > 0) ? p_dMaxGeschwindigkeit : 0){
}
