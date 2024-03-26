#include "Fahrzeug.h"
#include "Losfahren.h"
#include "Parken.h"
#include "Weg.h"

using namespace std;

extern double dGlobaleZeit;

// dStrecke Ausrechnen fuer das parkendes Fahrzeug.
// Wartet auf seine Zeit zum Fahren.
// Wenn die Zeit gekommen ist, werft einen Ausnahme "Losfahren"
double Parken::dStrecke(Fahrzeug& aFahrzeug, double dStartZeit){
	if(dGlobaleZeit >= p_dStartZeit){
		throw new Losfahren(aFahrzeug, *p_pWeg);
	}
	return 0.0;
}