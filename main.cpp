#include <sstream>
#include <iostream>
#include <memory>
#include <iomanip>
#include <vector>
#include <cmath>
#include <list>
#include <random>
#include <limits>
#include <fstream>
#include <exception>
#include <stdexcept>

#include "Fahrausnahme.h"
#include "Fahren.h"
#include "Fahrrad.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Losfahren.h"
#include "Parken.h"
#include "PKW.h"
#include "SimuClient.h"
#include "Simulation.h"
#include "Simulationsobjekt.h"
#include "Streckenende.h"
#include "Tempolimit.h"
#include "Verhalten.h"
#include "vertagt_aktion.h"
#include "vertagt_liste.h"
#include "Weg.h"

using namespace std;
double dGlobaleZeit = 0.0;

void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();

int main(){
	// vAufgabe_1();
    // vAufgabe_1a();
    // vAufgabe_2();
	return 0;
}

void vAufgabe_1(){
	// Statisches Erzeugen eines Elements
	Fahrzeug fahrrad1("fahrrad1", 25.33);

	// Dynamisch erzeugtes Element
	Fahrzeug* fahrrad2 = new Fahrzeug("fahrrad2(p)", 30.9);

	// Loeschen des dynamisch erzeugteten Elements
	delete fahrrad2;

	// Erzeugen der Smart Pointern
	unique_ptr<Fahrzeug> fahrzeug1 = make_unique<Fahrzeug>("fahrzeug1(up)", 33.3);
	unique_ptr<Fahrzeug> fahrzeug2 = make_unique<Fahrzeug>("fahrzeug2(up)", 29.7);
	shared_ptr<Fahrzeug> fahrzeug3 = make_shared<Fahrzeug>("fahrzeug3(sp)", 22.5);
	shared_ptr<Fahrzeug> fahrzeug4 = make_shared<Fahrzeug>("fahrzeug4(sp)", 19.1);
	cout << "\nVor dem Erzeugen des neues Objekts(Shared-Ptr) durch die Zuweisung, Count von fahrzeug4: " << fahrzeug4.use_count() << endl;

	// Speichern des Objekts, das vom fahrzeug4 shared ptr gezeigt wird, im Shared-Ptr fahrzeug_s
	shared_ptr<Fahrzeug> fahrzeug_s = fahrzeug4;
	cout << "Nach dem Erzeugen des neues Objekts(Shared-Ptr) durch die Zuweisung, Count von fahrzeug4: " << fahrzeug_s.use_count() << endl << endl;

	// Error: Unique-Ptr darf nicht zugewiesen werden.
	// unique_ptr<Fahrzeug> fahrzeug_u = fahrzeug2;

	cout << "Vor dem Speichern der Unique-Ptrs in der Unique-Vector:" << endl;
	cout << *fahrzeug1 << endl; // das Objekt
	cout << *fahrzeug2 << endl;
	cout << "Fahrzeug1: " << fahrzeug1 << endl;  // Adresse vom Objekt
	cout << "Fahrzeug2: " << fahrzeug2 << endl;
	cout << "Fahrzeug1&: " << &fahrzeug1 << endl; // Adresse vom Pointer
	cout << "Fahrzeug2&: " << &fahrzeug2 << endl << endl;


	// In einer Unique-Vektor duerfen nur die Objekte, die von Unique-Pointers gezeigt werden, gespeichert werden.
	// Da andernsfall wuerde das Objekt durch zwei Unique-Ptrs gleichzeigit angezeigt werden.
	vector<unique_ptr<Fahrzeug>> vectorFahrzeuge;
	vectorFahrzeuge.push_back(std::move(fahrzeug1));
	vectorFahrzeuge.push_back(std::move(fahrzeug2));


	// Kompilier weist diese Unique-Ptrs nach dem Speichern kein Speichernpplatz mehr zu.
	// Aber Sie existieren noch. Nur zeigen ihre Zeigern auf eine leere.
	cout << "Nach dem Speichern der Unique-Ptrs in der Unique-Vector:" << endl;
	cout << "Fahrzeug1: " << fahrzeug1 << endl;
	cout << "Fahrzeug2: " << fahrzeug2 << endl << endl;


	// cout << *fahrzeug1 << endl; -> Nach dieser Zeile duerfen die andere Code nicht gezeigt werden.
	cout << "Objekte aus der Unique-Vector: " << endl;
	cout << *vectorFahrzeuge[0] << endl; // -> Fahrzeug1 Objekt.
	cout << *vectorFahrzeuge[1] << endl << endl; // -> Fahrzeug2 Objekt.


    //	Diese Zeilen wuerden error ausgeben.
    //	vectorFahrzeuge.push_back(fahrzeug1);
    //	vectorFahrzeuge.push_back(fahrzeug3);
    //	vectorFahrzeuge.push_back(fahrzeug4);
    //	vectorFahrzeuge.push_back(fahrzeug_s);


	// Loesche den Intahl des Vektors. Die Objekte werden durch der Destruktor geloescht.
	vectorFahrzeuge.clear();


	// Count von fahrzeug3 wird sich erhoehen, weil ohne move Funktion die Ptrs Ihren Besitz aufm Objekt nicht verlieren.
	// Deswegen gewinnt dieses Objekt noch einen Pointer.
	// Mit "Count" wird gemeint, von wie viele Pointers dieses Objekt gezeigt wird.

	// Mit move Funktion verliert der Zeiger seinen Besitz aufm Objekt.
	// Der Besitzsrecht wird aufm neuen Zeiger uebertragen, der eigentlich eine Vektor ist.
	// Shared-Ptr Fahrzeug4 zeigt nun auf die Leere.
	cout << "\nVor dem Speichern des Objekts, Count von fahrzeug3: " << fahrzeug3.use_count() << endl;
	cout << "Vor dem Speichern des Objekts mit move(), Count von fahrzeug4: " << fahrzeug4.use_count() << endl;

	vector<shared_ptr<Fahrzeug>> vectorSharedFahrzeuge;
	vectorSharedFahrzeuge.push_back(fahrzeug3);
	vectorSharedFahrzeuge.push_back(std::move(fahrzeug4));

	cout << "Nach dem Speichern des Objekts, Count von fahrzeug3: " << fahrzeug3.use_count() << endl;
	cout << "Nach dem Speichern des Objekts, Count von fahrzeug4: " << fahrzeug4.use_count() << endl << endl;


	// Hier kann man eine Unique-Ptr in einer Shared-Vector speichern. Da die Shared-Typ flexibler als Unique-Typ ist.
	// Bei Unique-Ptr & Unique-Vector war das Gegenteil.
	cout << endl << "Erzeugen einer Unique-Ptr." << endl;
	unique_ptr<Fahrzeug> fahrzeug5 = make_unique<Fahrzeug>("fahrzeug5(up)", 35.7);
	vectorSharedFahrzeuge.push_back(std::move(fahrzeug5));
	cout << "Unique-Ptr wird in Shared-Vektor verschoben." << endl << endl;
	vectorSharedFahrzeuge.clear();
}

void vAufgabe_1a(){

	double dStunden = 0.0;
	// Lese die gewuenschte Simulationzeit ein.(Benutzerfreundlciher)
	cout << "Bitte geben Sie die Simulationzeit in Stunden ein: ";
	cin >> dStunden;
	double dMaxGeschwindigkeit = 0.0;
	string sName;


	// Lass Benutzer Eigenschaften der 3 Objekte eingeben.
	// Erzeuge die Objekte(im Smart-Pointer Format) nach den gegebenen Eigenschaften.
	cout << "Geben Sie bitte den Namen und MaxGeschwindigkeit des erstes Fahrzeuges:" << endl;
	cin >> sName >> dMaxGeschwindigkeit;
	unique_ptr<Fahrzeug> fahrzeug1 = make_unique<Fahrzeug>(sName,dMaxGeschwindigkeit);

	cout << "Geben Sie bitte den Namen und MaxGeschwindigkeit des zweites Fahrzeuges" << endl;
	cin >> sName >> dMaxGeschwindigkeit;
	unique_ptr<Fahrzeug> fahrzeug2 = make_unique<Fahrzeug>(sName,dMaxGeschwindigkeit);

	cout << "Geben Sie bitte den Namen und MaxGeschwindigkeit des drittes Fahrzeuges" << endl;
	cin >> sName >> dMaxGeschwindigkeit;
	unique_ptr<Fahrzeug> fahrzeug3 = make_unique<Fahrzeug>(sName,dMaxGeschwindigkeit);

	// Speichere diese Objekte, die von der Smart-Pointern gezeigt werden, in einer Unique Vektor
	// Da die Unique Pointers in einer Unique-Vektor gespeichert werden duerfen.
	vector<unique_ptr<Fahrzeug>>fahrzeuge;
	fahrzeuge.push_back(std::move(fahrzeug1));
	fahrzeuge.push_back(std::move(fahrzeug2));
	fahrzeuge.push_back(std::move(fahrzeug3));

	double dEpsilon = 0.0;
	// Einlesen der Zeittakt vom Benutzer.
	cout << endl << "Bitte geben Sie eine Period fuer die Simulation(lieber als Bruchteile von Studen): ";
	cin >> dEpsilon;

	// Simuliere diese Objekte und gibt die Eigenschaften dieser Objekte in jeder Zeittakt aufm Bildschirm aus.
	Fahrzeug::vKopf();
	for(dGlobaleZeit = dEpsilon; dGlobaleZeit < dStunden; dGlobaleZeit += dEpsilon){
		for(const auto& fahrzeug: fahrzeuge){
			cout << *fahrzeug << endl;
			fahrzeug->vSimulieren();
		}
	}
}

void vAufgabe_2(){
	int iPkwAnzahl, iFahrradAnzahl;

	string sName;
	double dGeschwindigkeit = 0.0;
	double dVerbrauch = 0.0;
	string sTankVolumen;

	vector<unique_ptr<Fahrzeug>> fahrzeuge;

	// Fragt nach dem Benutzer, wie viele Anzahl der Objekte er erzeugen will.
	// Einlesen der Anzahlen von PKWs und Fahrraeder
	cout << "Wie viele PKWs moechten Sie erstellen?" << endl;
	cin >> iPkwAnzahl;

	cout << "Wie viele Fahrraeder moechten Sie erstellen?" << endl;
	cin >> iFahrradAnzahl;

	// Erzeuge die Objekte mit der eingelesenen Eigenschaften und nach gegebenen Typen.
	cout << "Bitte geben Sie jetzt die Eigenschaften der PKWs vom Ersten bis Letzem ein.\n";
	for(int i = 0; i < iPkwAnzahl; i++){
		cout << "1) Name: ";
		cin >> sName;

		cout << "2) Maximale Geschwindigkeit: ";
		cin >> dGeschwindigkeit;

		cout << "3) Verbrauch: ";
		cin >> dVerbrauch;

		// Mann muss vorsicht sein, wenn die Stringeingaben eingelesen werden.
		// Das Verhalten des cin Operators ist anders fuer Strings.
		// Hier soll getline Methode benutzt werden.
		getline(cin, sTankVolumen);
		cout << "4) Tankvolumen(optinal, default 55 liter angenommen.): ";
		getline(cin, sTankVolumen);

		// Kontrolliere ob der Benutzer optionalen Eingabe eingegeben hat.
		// Wenn ja, erzeuge das PKW mit 3 Parametern.
		// Wenn nein, formt den Eingabe von string um den double Wert um und dann erzeuge das PKW.
		// Letztes gibt das Objekt in die Vektor ein.
		if(sTankVolumen == ""){
			unique_ptr<PKW> pkw = make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch);
			fahrzeuge.push_back(std::move(pkw));
		} else{
			unique_ptr<PKW> pkw = make_unique<PKW>(sName, dGeschwindigkeit, dVerbrauch, stod(sTankVolumen));
			fahrzeuge.push_back(std::move(pkw));
		}
	}

	// Erzeuge die Objekte mit der eingelesene Eigenschaften nach gegebenen Typen.
	cout << "Bitte geben Sie nun die Eigenschaften der Fahrraeder vom Ersten bis Letzem ein.\n";
	for(int j = 0; j < iFahrradAnzahl; j++){
		cout << "1) Name: ";
		cin >> sName;

		cout << "2) Maximale Geschwindigkeit: ";
		cin >> dGeschwindigkeit;

		// Erzeuge das Fahrrad Objekt.
		// Dann gibt das Objekt in die Vektor ein.
		unique_ptr<Fahrrad> fahrrad = make_unique<Fahrrad>(sName, dGeschwindigkeit);
		fahrzeuge.push_back(std::move(fahrrad));
	}

	// In jeder x.x Stunden werden die Taenke der PKWs aufgefuellt.
	double dTankZeit = 0.0;
	cout << endl << "Bitte geben Sie eine Period fuer Tanken der PKWs: ";
	cin >> dTankZeit;

	// Wie lange eine Simulationsschritt dauert? -> dEpsilon
	double dEpsilon = 0.0; // Zeittakt.
	cout << endl << "Bitte geben Sie eine Period fuer die Simulation(lieber als Bruchteile von Studen): ";
	cin >> dEpsilon;

	// Gibt die Eigenschaften der Objekte aufm Bildschrim formatiert aus.
	Fahrzeug::vKopf();
	for(dGlobaleZeit = dEpsilon; dGlobaleZeit < 5; dGlobaleZeit += dEpsilon){
		for(const auto& fahrzeug : fahrzeuge){
			cout << *fahrzeug;
			fahrzeug->vSimulieren();
			if(fmod(dGlobaleZeit,dTankZeit) < dEpsilon){
				fahrzeug->dTanken(fahrzeug->getTankvolumen());
			}
		}
	}
}