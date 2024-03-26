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
