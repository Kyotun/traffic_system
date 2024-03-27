#include <string>
#include <iomanip>
#include <iostream>
#include <cmath>

#include "SimuClient.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "Verhalten.h"
#include "Weg.h"

using namespace std;

extern double dGlobaleZeit;

// Konstruktor mit dem Name, erbt von der Klasse Fahrzeug
Fahrrad::Fahrrad(string p_sName): Fahrzeug(p_sName){
}

// Konstruktor mit dem Name und der Geschwindigkeit, erbt von der Klasse Fahrzeug
Fahrrad::Fahrrad(string p_sName, double p_dMaxGeschwindigkeit):
		Fahrzeug(p_sName, p_dMaxGeschwindigkeit){
}