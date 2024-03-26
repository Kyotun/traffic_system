#include <iostream>
#include <string>
#include <iomanip>

#include "Simulationsobjekt.h"

using namespace std;

extern double dGlobaleZeit;

// Standard-Konstruktor
Simulationsobjekt::Simulationsobjekt(){
	cout << "Ein Simulationsobjekt wurde mit der ID '" << p_iID
		 << "' erzeugt." << endl;
}

// Standard-Destruktor
Simulationsobjekt::~Simulationsobjekt(){
	cout << "Ein Simulationsobjekt wurde mit dem Name '" << p_sName
		 << "' und mit der ID " << p_iID
		 << " geloescht." << endl;
}

Simulationsobjekt::Simulationsobjekt(string p_sName): p_sName(p_sName){
	cout << "Ein Simulationsobjekt wurde mit dem Name '" << p_sName
			 << "' und mit der ID " << p_iID
			 << " erzeugt." << endl;
}

// Ausgeben von Objekten mit Punktoperator und die Methode vAusgeben.
void Simulationsobjekt::vAusgeben() const{
	cout << resetiosflags(ios::adjustfield)
		 << setiosflags(ios::left)
		 << setprecision(2) << fixed
		 << setw(8) << getID()
		 << setw(15) << getName();
}

// Ausgeben von Objekten einfach mit cout<< (opreator<<)
void Simulationsobjekt::vAusgeben(ostream& ausgabe) const{
	ausgabe << resetiosflags(ios::adjustfield)
			 << setiosflags(ios::left)
			 << setprecision(2) << fixed
			 << setw(8) << getID()
		     << setw(15) << getName();
}

void Simulationsobjekt::vEinlesen(istream& is){
	if(is.fail()){
		throw runtime_error("Fehler beim Einlesen der Eingabe Stream.");
	}
	is >> p_sName;
}

// Ueberladen des Gleichheitoperators
bool Simulationsobjekt::operator==(const Simulationsobjekt& andere){
	if(this->p_iID == andere.p_iID){
		return true;
	}
	return false;

}

// Ueberladen des Zuweisungsoperators
Simulationsobjekt& Simulationsobjekt::operator=(const Simulationsobjekt& other) {
	//Kontrolliere ob das Objekt selbst aufruft.
	if (this == &other) {
		return *this;
	}

	this->p_sName = other.getName();
	this->p_dZeit = other.getZeit();

	return *this;
}

// Ueberladen des Ausgabeoperators
// Dank dieses Ueberladen, darf die Fahrzeuge einfach mit cout<<(operator <<) ausgegeben werden.
ostream& operator<<(ostream& ausgabe,const Simulationsobjekt& simuobjekt) {
	simuobjekt.vAusgeben(ausgabe);
	return ausgabe;
}

// Ueberladen des Eingabe Operators
istream& operator>>(istream& is, Simulationsobjekt& simuobjekt){
	simuobjekt.vEinlesen(is);
    return is;
}
