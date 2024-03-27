#include <list>
#include <random>

#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Weg.h"


using namespace std;

Kreuzung::Kreuzung(string sName, double dTankstelle):
		Simulationsobjekt(sName),
		p_dTankstelle(dTankstelle){
}
