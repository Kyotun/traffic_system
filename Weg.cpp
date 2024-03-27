#include <memory>
#include <string>
#include <list>
#include <iostream>
#include <iomanip>

#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Tempolimit.h"
#include "Weg.h"
#include "vertagt_liste.h"

using namespace std;
using namespace vertagt;
extern double dGlobaleZeit;

// Konstruktor fuer Weg Objekt mit 3 Parametern
Weg::Weg(string p_sName, double p_dLaenge, Tempolimit p_eTempolimit): // @suppress("Member declaration not found") // @suppress("Class members should be properly initialized")
		Simulationsobjekt(p_sName), p_dLaenge(p_dLaenge), p_eTempolimit(p_eTempolimit){}

Weg::Weg(string sName, // @suppress("Class members should be properly initialized")
		double dLaenge,
		weak_ptr<Kreuzung>pZielkreuzung ,
		Tempolimit eTempolimit,
		bool bUeberholverbot) :
	Simulationsobjekt(sName),
	p_dLaenge(dLaenge),
	p_pZielkreuzung(pZielkreuzung),
	p_eTempolimit(eTempolimit),
	p_bUeberholverbot(bUeberholverbot) {
}

// Wird das Tempolimit des Wegs zurueckgegeben
double Weg::getTempolimit() const{
	cout << fixed << setprecision(2);
	return (double)p_eTempolimit;
}

Tempolimit Weg::gettTempolimit() const{
	switch((int)getTempolimit()){
		case 50:
			return Innerorts;
		case 100:
			return Landstrasse;
		default :
			return Autobahn;
		}

}