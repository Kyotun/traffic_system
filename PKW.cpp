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

// Gibt den aktuellen Tankinhalt zurueck
double PKW::getTankinhalt() const{
	return p_dTankinhalt;
}

// Ausrechnen der Geschwindigkeit von PKWs
double PKW::dGeschwindigkeit() const{
	double erlaubte_max_geschwindigkeit = 0.0;
	erlaubte_max_geschwindigkeit = getMaxGeschwindigkeit();

	// Wenn dieses Objekt ein Verhalten hat, heisst das, dieses Objekt auf einem Weg sich befindet.
	// Die hochste erlaubte Geschwindigkeit soll rausgenommen werden.(erlaubte_max_geschwindigkeit)
	// Wenn diese Geschwindigkeit riesig gross ist, muss das Fahrzeug mit seiner maxGeschwindigkeit weiterfahren.
	// Wenn es kleiner ist, darf maximal mit dieser Geschwindigkeit gefahren werden.
	if(p_pVerhalten){
		erlaubte_max_geschwindigkeit = p_pVerhalten->getpWeg()->getTempolimit();
	}

	if(erlaubte_max_geschwindigkeit > getMaxGeschwindigkeit()){
		return getMaxGeschwindigkeit();
	}

	return erlaubte_max_geschwindigkeit;
}