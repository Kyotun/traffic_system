#include <string>
#include <iomanip>
#include <iostream>
#include <memory>
#include "Fahrzeug.h"
#include "Simulationsobjekt.h"
#include "Weg.h"

using namespace std;

extern double dGlobaleZeit;

// Fahrzeug-Objekt mit dem Name
Fahrzeug::Fahrzeug(string p_sName): Simulationsobjekt(p_sName){
}

// Fahrzeug-Objekt Konstruktor mit dem Name und der Geschwindigkeit
Fahrzeug::Fahrzeug(string p_sName, double p_dMaxGeschwindigkeit): Simulationsobjekt(p_sName),
		p_dMaxGeschwindigkeit((p_dMaxGeschwindigkeit > 0) ? p_dMaxGeschwindigkeit : 0){
}

// Ausgabe Funktion, die zum Ausgeben von der Eigenschaften der Objekten dient.
// Es ist eine Objektmethode.
void Fahrzeug::vAusgeben() const{

	Simulationsobjekt::vAusgeben();
	cout << resetiosflags(ios::left)
		 << setiosflags(ios::right)
		 << setw(20) << getMaxGeschwindigkeit()
		 << setw(20) << getGesamtstrecke()
		 << setw(20) << getAbschnittStrecke()
		 << setw(20) << dGeschwindigkeit();
}

// Ausgabe Funktion, die zum Ausgeben von der Eigenschaften der Objekten dient.
// Es reicht nur das Objekt zu cout zu geben.
void Fahrzeug::vAusgeben(ostream& ausgabe) const {

	Simulationsobjekt::vAusgeben(ausgabe);
	ausgabe << resetiosflags(ios::left)
			<< setiosflags(ios::right)
			<< setw(20) << getMaxGeschwindigkeit()
			<< setw(20) << getGesamtstrecke()
			<< setw(20) << getAbschnittStrecke()
			<< setw(20) << dGeschwindigkeit();
}

// Kopf Funktion wird vor der Funktion Ausgeben aufgerufen,
// damit ist die Ausgaben(Eigenschaften der Objekten) besser und deutlich zu sehen.
void Fahrzeug::vKopf(){
	cout << endl << resetiosflags(ios::adjustfield)
		 << setiosflags(ios::left)
		 << setw(8) << "ID"
		 << setw(15) << "Name"
		 << resetiosflags(ios::adjustfield)
		 << setiosflags(ios::right)
		 << setw(20) << "MaxGeschwindigkeit"
		 << setw(20) << "Gesamtstrecke"
		 << setw(20) << "Abschnittstrecke"
		 << setw(20) << "Geschwindigkeit"
		 << setw(20) << "Gesamtverbrauch"
		 << setw(15) << "Tankinhalt"
		 << setw(10) << "Zeit"
		 << setw(15) << "GlobaleZeit" << endl;

	cout << setw(8+10+15*3+20*5) << setfill('-') << '-' << setfill(' ') << endl;

}
