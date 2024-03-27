#include <string>
#include <iomanip>
#include <iostream>
#include <memory>

#include "Fahren.h"
#include "Fahrzeug.h"
#include "Parken.h"
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

// Simulation-Funktion. Wenn die von einem Objekt aufgerufen wird, wird das Objekt eine Zeittakt(Zeitdiffernez) simuliert.
void Fahrzeug::vSimulieren(){
	// Zeitdifferenz ist der Differenz zwischen t(t) und t(t+1)
	if(p_dZeit == dGlobaleZeit){
		cout << "Farhzeug '" << p_sName << "' wurde vorher schon einmal simuliert." << endl;
		return;
	}else{
		double dZeitdifferenz = dGlobaleZeit - p_dZeit;

		// Aktuell gefahrende Strecke
		// wenn es ein Verhalten gibt, soll die Geschwindigkeit nach diesem Verhalten ausrechnet werden.
		if(p_pVerhalten){
			// TeilStrecke wird nach der Geschwindigkeit, des Zeitdifferenz und des Ueberholverbot ausgerechnet.
			// Dann werden die Abschnitt- und Gesamtstrecke inkrementiert.
			// Falls der Weg ein Ueberholverbot besitzt, soll die Schranke auch beruecksichtigt(bei der dStrecke Funktion) werden.
			// Letztes wird die Schranke als aktuelle Schranke gesetzt.
			double dTeilStrecke = p_pVerhalten->dStrecke(*this, dZeitdifferenz);
			Weg* pWeg = p_pVerhalten->getpWeg();
			p_dAbschnittStrecke += dTeilStrecke;
			p_dGesamtstrecke += dTeilStrecke;
			pWeg->setSchranke(p_dAbschnittStrecke);
		}else{
			double dTeilStrecke = dGeschwindigkeit()*dZeitdifferenz;
			p_dAbschnittStrecke += dTeilStrecke;
			p_dGesamtstrecke += dTeilStrecke;
		}

		p_dGesamtZeit += dZeitdifferenz;
		p_dZeit = dGlobaleZeit; // Die Letzte Zeit, in der das Fahrzeug sich bewegt hat.

	}
}

// Wenn ein Fahrzeug von einem Weg akzeptiert wurde, soll es auch diesen Weg in sich selbst anerkannt machen.
// Diese Method fuer die fahrende Fahrzeuge
void Fahrzeug::vNeueStrecke(Weg& weg){
	if(p_pVerhalten){
		p_pVerhalten.reset();
	}
	p_pVerhalten = make_unique<Fahren>(weg);
	this->vResetAbschnittStrecke();
	cout << "Fahrzeug " << p_sName << " ist in den Weg " << weg.getName() << " zum Fahren angekommen." << endl;
}

// Wenn ein Fahrzeug von einem Weg akzeptiert wurde, soll es auch diesen Weg in sich selbst anerkannt machen.
// Diese Method fuer die parkende Fahrzeuge.
// Parkende Fahrzeuge warten bis die Globalezeit gleich Startzeitpunkt ist.
void Fahrzeug::vNeueStrecke(Weg& weg, double dStartZeitpunkt){
	if(p_pVerhalten){
		p_pVerhalten.reset();
	}
	p_pVerhalten = make_unique<Parken>(weg, dStartZeitpunkt);
	this->vResetAbschnittStrecke();
	cout << "Fahrzeug " << p_sName << " ist in den Weg " << weg.getName() << " zum Parken angekommen." << endl;
}

void Fahrzeug::vEinlesen(istream& is){
	Simulationsobjekt::vEinlesen(is);
	is >> p_dMaxGeschwindigkeit;
}

// Ueberladen des '<' (kleiner als) operators
// Wenn das Vergleichobjekt groesser ist, ist diese Bedingung richtig.
bool Fahrzeug::operator<(const Fahrzeug& andere)const{
	if(this->getGesamtstrecke() < andere.getGesamtstrecke()){
		return true;
	} else{
		return false;
	}
}

// ueberladen des Operators '='
// Ausser ID Attribute, wird alles kopiert und uebertragen.
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {
	// Kontrolliere ob das Objekt selbst aufruft.
	Simulationsobjekt::operator =(other);
	this->p_dMaxGeschwindigkeit = other.getMaxGeschwindigkeit();
	this->p_dGesamtstrecke = other.getGesamtstrecke();
	this->p_dZeit = other.getZeit();
	this->p_dGesamtZeit = other.getGesamtZeit();

	return *this;
}

void Fahrrad::vEinlesen(istream& is){
	Fahrzeug::vEinlesen(is);
}