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

// Uebergebener Weg fuehrt zu dieser(this) Kreuzung und hat nur einen Rueckweg.
// Dieser Rueckweg ist in der Liste von dieser Kreuzung.
// Wenn es nur einen Weg gibt, der zu dieser Kreuzung fuehrt, wuerde dieser Weg ausgewaehlt muessen.
shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg& weg){
	if(p_pWege.empty()){
		throw runtime_error("Diese Kreuzung " + getName() + " enthaelt keinen Weg.");
	}

	shared_ptr<Weg> rueckWeg = weg.getRueckweg();
	if (!rueckWeg) {
		throw runtime_error("Es gibt keinen Rueckweg fuer uebergebenen Weg.");
	}

	// Kontrolliere, ob es nur einen Weg zu dieser Kreuzung gibt.
	// Wenn ja, gibt den Rueckweg zuerueck.
	if(p_pWege.size() == 1){
		return rueckWeg;
	}

	// Wenn nein, nimmt alle Wege ausser diesen Rueckweg
	// und stelle diese in einer Liste, die nur den Rueckweg nicht enthaelt.
	list<shared_ptr<Weg>> filteredWege;
	for (const auto& wegPtr : p_pWege) {
		if (wegPtr != rueckWeg) {
			filteredWege.push_back(wegPtr);
		}
	}

	// Erzeuge einen zufaelligen Index zwischen 0 und groesse von filteredWege list.
	// Dann waehle einen Index zufaellig.
	// Gibt diesen zufaellig gewaehlten Index(Weg) zurueck.
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, filteredWege.size() - 1);
	int randomIndex = dis(gen);
	auto it = filteredWege.begin();
	std::advance(it, randomIndex);
	return *it;
}