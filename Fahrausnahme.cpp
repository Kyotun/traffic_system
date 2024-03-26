#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"

// Erzeugen ein Ausnahmeobjekt mit einem Fahrzeug und einem Weg.
Fahrausnahme::Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg):p_pFahrzeug(fahrzeug), p_pWeg(weg){}