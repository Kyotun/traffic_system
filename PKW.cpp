#include <string>
#include <iostream>
#include <iomanip>

#include "Fahrzeug.h"
#include "PKW.h"
#include "SimuClient.h"
#include "Tempolimit.h"
#include "Verhalten.h"
#include "Weg.h"


using namespace std;
extern double dGlobaleZeit;

// Konstruktor mit dem Name, erbt von Fahrzeug
PKW::PKW(string p_sName): Fahrzeug(p_sName){}

// Konstruktor mit dem Name und  der Geschwindigkeit, erbt von Fahrzeug
PKW::PKW(string p_sName, double p_dMaxGeschwindigkeit): Fahrzeug(p_sName, p_dMaxGeschwindigkeit){}

// Konstruktor mit dem Verbrauch und Tankvolumen
PKW::PKW(double p_dVerbrauch, double p_dTankvolumen):
		p_dVerbrauch(p_dVerbrauch), p_dTankvolumen(p_dTankvolumen){
	cout << "Ein PKW wurde mit dem Verbrauch '" << p_dVerbrauch
		 <<"' und der Tankvolumen '" << p_dTankvolumen << "' erzeugt" << endl;
}

// Konstruktor mit dem Name, der Geschwindigkeit, dem Verbrauch und dem Tankvolumen.
// Der erbt den Name und die Geschwindigkeit von der Fahrzeugklasse
PKW::PKW(string p_sName, double p_dMaxGeschwindigkeit,
				double p_dVerbrauch, double p_dTankvolumen):
					Fahrzeug(p_sName, p_dMaxGeschwindigkeit),
					p_dVerbrauch(p_dVerbrauch),
					p_dTankvolumen(p_dTankvolumen){}

// Rechne den Gesamtverbrauch und gibt es zurueck.
double PKW::getGesamtVerbrauch() const{
	// Gesamtstrecke in km erste Klammer
	// Zweite Klammer = Gesamtverbrauch in 1 km
	return (p_dGesamtstrecke)*(p_dVerbrauch/100);
}