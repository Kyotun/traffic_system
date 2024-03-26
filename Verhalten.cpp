#include "Fahrzeug.h"
#include "Verhalten.h"

using namespace std;

extern double dGlobaleZeit;

// Gibt die gefahrende Strecke vom uebergebenen Fahrzeug innerhalb des gegebenen Zeitintervalls zurueck.
double Verhalten::dStrecke(Fahrzeug& fahrzeug, double dZeitIntervall){
	return fahrzeug.dGeschwindigkeit()*dZeitIntervall;
}