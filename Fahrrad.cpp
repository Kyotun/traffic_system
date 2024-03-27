#include <string>
#include <iomanip>
#include <iostream>
#include <cmath>

#include "SimuClient.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "Verhalten.h"
#include "Weg.h"

using namespace std;

extern double dGlobaleZeit;

// Konstruktor mit dem Name, erbt von der Klasse Fahrzeug
Fahrrad::Fahrrad(string p_sName): Fahrzeug(p_sName){
}

// Konstruktor mit dem Name und der Geschwindigkeit, erbt von der Klasse Fahrzeug
Fahrrad::Fahrrad(string p_sName, double p_dMaxGeschwindigkeit):
		Fahrzeug(p_sName, p_dMaxGeschwindigkeit){
}

// Geschwindigkeitfunktion, die die aktuelle Geschwindigkeit der Fahrräder aktualisiert.
// Wenn es schon kleiner gleich 12 ist, bleibt es 12.
// Wenn nicht, soll die aktuelle Geschwinidkgiet mit 0.9 in jeder Zeittakt multipliziert werden,
// um die aktuelle Geschwindigkeit aktualisieren zu können
double Fahrrad::dGeschwindigkeit() const{

	double erlaubte_max_geschwindigkeit = 0.0;
	double d_aktuelleGeschwindigkeit = 0.0;
	int iAnzahlAbschnitt = (int)p_dGesamtstrecke/20;

	d_aktuelleGeschwindigkeit = p_dMaxGeschwindigkeit * pow(0.9, iAnzahlAbschnitt);

	// Wenn es ein Verhalten gibt, soll dessen Weg anerkannt gemacht werden und der Geschwindigkeitgrenze dieses Wegs
	// Soll auch geachtet werden.
	if(p_pVerhalten){
		erlaubte_max_geschwindigkeit = p_pVerhalten->getpWeg()->getTempolimit();

		// Wenn es einen Weg gibt, dessen Tempolimit geachtet werden soll, muss man kontrollieren, ob die Geschwindigkeit
		// in dem erlaubenden Grenze liegt. Wenn nicht soll die Geschwindigkeit nach diesem Grenze reguliert werden.
		if(erlaubte_max_geschwindigkeit < p_dMaxGeschwindigkeit){
			d_aktuelleGeschwindigkeit = erlaubte_max_geschwindigkeit * pow(0.9, iAnzahlAbschnitt);
		}
	}

	// Fahrraeder duerfen mindestens mit 12km/h fahren.
	if(d_aktuelleGeschwindigkeit <= 12.0){
		d_aktuelleGeschwindigkeit = 12.0;
	}

	return d_aktuelleGeschwindigkeit;
}

// Ausgabefunktion der Klasse Fahrrad, erbt von Fahrzeug und werden einige Fahrradspezifische Eigenschaften addiert.
// Diese Funktion ist eine Objektmethode. Der Punktoperator soll verwendet werden.
void Fahrrad::vAusgeben() const{
	Fahrzeug::vAusgeben();
	cout << setw(20) << "-"
	   	 << setw(15) << "-"
		 << setw(10) << getZeit()
		 << setw(15) << getGlobaleZeit() << endl;
}

// Ausgabefunktion der Klasse Fahrrad, erbt von Fahrzeug und werden einige Fahrradspezifische Eigenschaften addiert.
// Mit dieser Methode kann das Objekt direkt mit cout<< ausgegeben werden.
void Fahrrad::vAusgeben(std::ostream& ausgabe) const{
	Fahrzeug::vAusgeben(ausgabe);
	ausgabe << setw(20) << "-"
			<< setw(15) << "-"
			<< setw(10) << getZeit()
			<< setw(15) << getGlobaleZeit() << endl;
}
