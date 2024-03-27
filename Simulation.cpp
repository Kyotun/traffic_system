#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <sstream>

#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Simulation.h"
#include "SimuClient.h"
#include "Tempolimit.h"
#include "Weg.h"

using namespace std;
extern double dGlobaleZeit;

shared_ptr<Kreuzung> Simulation::getKreuzung(const string& name) {
	vCheckKreuzung(name);
    auto it = kreuzungenMap.find(name);
    return it->second;
}

// Kontrolliere, ob der gegebene Name nicht im Map ist.
void Simulation::vCheckKreuzung(const string& name){
	if(kreuzungenMap.find(name) == kreuzungenMap.end()){
		throw runtime_error("Es gibt keine Kreuzung unter diesen Name: " + name);
	}
}

// Kontrolliere, ob der gegebene Name sich im Map schon befindet.
void Simulation::vCheckDoppelKreuzung(const string& name){
	if(kreuzungenMap.find(name) != kreuzungenMap.end()){
		throw runtime_error("Es gibt bereits eine andere Kreuzunge unter der Name: " + name);
	}
}

void Simulation::vAddKreuzung(const string& name, shared_ptr<Kreuzung> kreuzung) {
	vCheckDoppelKreuzung(name);
	kreuzungenMap[name] = kreuzung;
}

// Aktualisiert die gegebene Kreuzung.
// Zuerst loescht die gegebene Kreuzung, dann addiert wieder in die Map.
void Simulation::vAktualisiereKreuzung(const string& name, shared_ptr<Kreuzung> kreuzung){
	vCheckKreuzung(name);
	kreuzungenMap.erase(name);
	vAddKreuzung(name, kreuzung);

}

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

