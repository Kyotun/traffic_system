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
void vAufgabe_3();
void vAufgabe_AB1();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();
void vAufgabe_6b();
void vAufgabe_7();
void vAufgabe_8();
void vAufgabe_9();
void vAufgabe_9a();

int main(){
	// vAufgabe_1();
    // vAufgabe_1a();
    // vAufgabe_2();
    // vAufgabe_3();
    // vAufgabe_AB1();
    // vAufgabe_4();
    // vAufgabe_5();
    // vAufgabe_6();
    // vAufgabe_6a();
    // vAufgabe_6b();
    // vAufgabe_7();
    // vAufgabe_8();
    // vAufgabe_9();
    // vAufgabe_9a();
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

void vAufgabe_3(){
	// Unterschied zwischen ptr Objekt(fahrrad1, fahrrad2, fahrzeug2) und nicht ptr Objekt(pkw1, pkw2) zu beachten.
	// Es ist nicht gut, traditionaller Pointer zu nutzen. Lieber kann man smart Pointers benutzen.

	// Erzeuge einige Fahrzeuge/PKWs und Fahrraeder Objekte.
	unique_ptr<Fahrzeug> fahrzeug1 = make_unique<Fahrzeug>("fahrzeug1", 200.3);
	Fahrrad* fahrrad1 = new Fahrrad("fahrrad1", 25.3);
	Fahrrad* fahrrad2 = new Fahrrad("fahrrad2", 22.9);
	PKW pkw1("pkw1", 159.3, 8.3, 44.9);
	PKW pkw2("pkw2", 100.5, 8, 32.5);
	Fahrzeug* fahrzeug2 = new Fahrzeug("fahrzeug2", 88.3);

	// Gibt die Eigenschaften dieser Objekte aufm Bildschrim aus.
	Fahrzeug::vKopf();
	cout << *fahrzeug1 << endl << endl;
	cout << *fahrrad1 << endl;
	cout << *fahrrad2 << endl;
	cout << pkw1 << endl;
	cout << pkw2 << endl;
	cout << *fahrzeug2 << endl << endl;

	// Set die Gesamtstrecke von zwei PKWs, um das Verhealtnis des ueberladenden operator< beobachten zu koennen.
	pkw1.setGesamtstrecke(100);
	pkw2.setGesamtstrecke(200);

	// Gibt die Eigenschaften dieser Objekte aufm Bildschrim aus.
	Fahrzeug::vKopf();
	cout << *fahrzeug1 << endl << endl;
	cout << *fahrrad1 << endl;
	cout << *fahrrad2 << endl;
	cout << pkw1 << endl;
	cout << pkw2 << endl;
	cout << *fahrzeug2 << endl << endl;

	// Beachte der operator<
	if(pkw1 < pkw2){
		cout << "\nGesamtstrecke von pkw1: " << pkw1.getGesamtstrecke() << endl;
		cout << "GesamStstrecke von pkw2: " << pkw2.getGesamtstrecke() << endl;
		cout << "Bedingung war pkw1 < pkw2. Die Bedingung wurde erfuellt und diese Zeile ist im If-Block\n" << endl;
	}

	// Beachte der operator=
	// Da pkw1 und pkw1 Objekte sind, koennen die alle Eigenschaften außer ID uebertragen werden.
	cout << "Operation: pkw1=pkw2" << endl << endl;
	pkw1 = pkw2;

	cout << "Adresse von pkw1: " << &pkw1 << endl;
	cout << "Adresse von pkw2: " << &pkw2 << endl;


	// Gibt die Eigenschaften dieser Objekte aufm Bildschrim aus.
	Fahrzeug::vKopf();
	cout << *fahrzeug1 << endl << endl;
	cout << *fahrrad1 << endl;
	cout << *fahrrad2 << endl;
	cout << pkw1 << endl;
	cout << pkw2 << endl;
	cout << *fahrzeug2 << endl << endl;

	// Da die Fahrraeder Pointers sind, kann die uebertragung der IDs nicht vermieden werden.
	cout << "Operation: fahrrad1=fahrrad2\n" << endl;
	fahrrad1 = fahrrad2;

	cout << fahrrad1 << endl;
	cout << fahrrad2 << endl;

	// Gibt die Eigenschaften dieser Objekte aufm Bildschrim aus.
	Fahrzeug::vKopf();
	cout << *fahrzeug1 << endl << endl;
	cout << *fahrrad1 << endl;
	cout << *fahrrad2 << endl;
	cout << pkw1 << endl;
	cout << pkw2 << endl;
	cout << *fahrzeug2 << endl << endl;

	// Loeschen der dynamischen Objekte(Pointers, um von der undefinierten Verhealtnissen vermeiden zu koennen.)
	delete fahrrad1;
	delete fahrrad2;
	delete fahrzeug2;
}

void vAufgabe_AB1() {

   int l = 0; // Laufindex fuer gezielte AUsgabe
   vector<int> ausgabe{15};
   double dTakt = 0.3;

   std::vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
   vecFahrzeuge.push_back(make_unique <PKW>("Audi", 229, 9.6));
   vecFahrzeuge.push_back(make_unique <Fahrrad>("BMX", 24.7));
   for (dGlobaleZeit = 0; dGlobaleZeit < 5; dGlobaleZeit += dTakt)
   {
       auto itL = find(ausgabe.begin(), ausgabe.end(), l);
       if (itL != ausgabe.end()) {
           std::cout << std::endl << l <<  " Globalezeit = " << dGlobaleZeit << std::endl;
           Fahrzeug::vKopf();
       }

       for (int i = 0; i < (int) vecFahrzeuge.size(); i++)
       {
           vecFahrzeuge[i]->vSimulieren();
           if (fabs(dGlobaleZeit - 3.0) < dTakt/2)
           {
               vecFahrzeuge[i]->dTanken();
           }
           if (itL != ausgabe.end()) {
               std::cout << *vecFahrzeuge[i] << endl;
           }
       }
       l++;
   }
   char c;
   std::cin >> c;
}

void vAufgabe_4(){

	// Statisches erzeugen eines Wegs "Innerorts"
	Weg weg1("weg1", 105.99, Tempolimit::Innerorts);

	// Dynamisches erzeugen(mit Smart-Ptr) eines wegs "Autobahn"
	unique_ptr<Weg> weg_ptr = make_unique<Weg>("weg_ptr", 287.34, Autobahn);

	// Dynamisches erzeugen eines Fahrzeugs.
	unique_ptr<Fahrzeug> fahrzeug1 = make_unique<Fahrzeug>("BMW");
	unique_ptr<Fahrzeug> fahrzeug2 = make_unique<Fahrzeug>("Audi");
	unique_ptr<Fahrzeug> fahrzeug3 = make_unique<Fahrzeug>("BMX");


	// Weg sollte leer sein.
	cout << "\nVor dem Annahme:";
	Weg::vKopf();
	cout << weg1 << endl;
	cout << *weg_ptr << endl << endl;

	// Nach diesen Zeilen soll Weg fahrzeug1 enthalten.
	cout << "Nach dem Annahme von fahrzeug1 im weg1:" << endl;
	weg1.vAnnahme(std::move(fahrzeug1));
	weg1.vAnnahme(std::move(fahrzeug2));
	weg1.vAnnahme(std::move(fahrzeug3));
	Weg::vKopf();
	cout << weg1 << endl;
	cout << *weg_ptr << endl << endl;
}

void vAufgabe_5(){

	// Dynamisches Erzeugen verschiedenen Elementen
	unique_ptr<Weg> weg_ptr1 = make_unique<Weg>("WEG", 255.55, Innerorts);

	unique_ptr<Fahrzeug> fahrzeug = make_unique<PKW>("PKW1", 123.35, 13.37);
	unique_ptr<Fahrzeug> fahrzeug2 = make_unique<PKW>("PKW2", 155.37, 15.55, 62.37);
	unique_ptr<Fahrzeug> fahrzeug3 = make_unique<Fahrrad>("Fahrrad", 27.89);
	unique_ptr<Fahrzeug> fahrzeug4 = make_unique<PKW>("PKW3", 121.3, 12.33, 34.37);

	// Weg akzeptiert die Fahrzeuge.
	cout << endl;
	weg_ptr1->vAnnahme(std::move(fahrzeug));
	weg_ptr1->vAnnahme(std::move(fahrzeug2));
	weg_ptr1->vAnnahme(std::move(fahrzeug3));
	weg_ptr1->vAnnahme(std::move(fahrzeug4),2);



	// In jeder x.x Stunden werden die Taenke der PKWs aufgefuellt.
	double dTankZeit = 0.0;
	cout << endl << "Bitte geben Sie eine Period fuer Tanken der PKWs: ";
	cin >> dTankZeit;

	// Wie lange eine Simulationsschritt dauert? -> dEpsilon
	double dEpsilon = 0.0; // Zeittakt.
	cout << endl << "Bitte geben Sie eine Period fuer die Simulation(lieber als Bruchteile von Studen): ";
	cin >> dEpsilon;

	// Gibt die Eigenschaften der Objekte aufm Bildschrim formatiert aus.
	// In jeder Zeittakt, gibt die Informationen der Fahrzeugen vor dem Simulieren aus.
	// Dann simuliere alle Fahrzeuge.
	Fahrzeug::vKopf();
	for(dGlobaleZeit = dEpsilon; dGlobaleZeit < 5; dGlobaleZeit += dEpsilon){
		for(const auto& fahrzeug : *weg_ptr1->getFahrzeugList()){
			if(fmod(dGlobaleZeit,dTankZeit) < dEpsilon){
				fahrzeug->dTanken(fahrzeug->getTankvolumen());
			}
		}
		weg_ptr1->vSimulieren();
	}
}

// Mit grafische Ausgabe, neue Aufgabe6
void vAufgabe_6(){

	//Dynamisches Erzeugen der Elementen
	unique_ptr<Weg> autobahn = make_unique<Weg>("Autobahn", 500.0);
	unique_ptr<Weg> innerort = make_unique<Weg>("Innerort", 500.0, Innerorts);

	unique_ptr<PKW> pkw1 = make_unique<PKW>("PKW1_AB", 123.35, 13.37);
	unique_ptr<PKW> pkw2 = make_unique<PKW>("PKW2_AB", 155.37, 15.55, 62.37);
	unique_ptr<PKW> pkw3 = make_unique<PKW>("PKW3_IN", 133.39, 12.22);
	unique_ptr<PKW> pkw4 = make_unique<PKW>("PKW4_IN", 188.32, 16.37);

	unique_ptr<Fahrrad> fahrrad1 = make_unique<Fahrrad>("Fahrrad1_AB", 30.33);
	unique_ptr<Fahrrad> fahrrad2 = make_unique<Fahrrad>("Fahrrad2_IN", 25.35);

	// Intialisierung der Grafik auf dem SimuServer
	bInitialisiereGrafik(800, 500);

	// Setzen der Koordinaten fuer die Straße, gerade Linie
	int koordinaten[4] = { 700, 250, 100, 250 };

	// Zeichnen der Straße
	bZeichneStrasse(autobahn->getName(), innerort->getName(), autobahn->getLaenge(), 2, koordinaten);


	//Annehmen der Fahrzeuge in die Wege.
	cout << endl;
	// Zum beobachten des Ueberholverbot, die kleinste Geschwindigkeit soll als erstes angenommen werden.
	// Auf dem Autobahn kann man Ueberholverbot beobachten.
	autobahn->vAnnahme(std::move(fahrrad1));
	autobahn->vAnnahme(std::move(pkw1));
	autobahn->vAnnahme(std::move(pkw2),2);

	// Hier kann man nur zwischen pk4 und fahrrad2 das Ueberholverbot beobachten.
	innerort->vAnnahme(std::move(pkw3));
	innerort->vAnnahme(std::move(pkw4),1.5);
	innerort->vAnnahme(std::move(fahrrad2));



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
	for(dGlobaleZeit = dEpsilon; dGlobaleZeit < 4; dGlobaleZeit += dEpsilon){

		// Kontrolliere die Fahrzeuge fuer Tanken, die aufm Autobahn fahren.
		for(const auto& fahrzeug : *autobahn->getFahrzeugList()){
			//Kontrolliere ob die TankZeit gekommen ist.
			if(fmod(dGlobaleZeit,dTankZeit) < dEpsilon){
				fahrzeug->dTanken(fahrzeug->getTankvolumen());
			}
		}

		// Kontrolliere die Fahrzeuge fuer Tanken, die aufm Innerorts fahren.
		for(const auto& fahrzeug : *innerort->getFahrzeugList()){
			//Kontrolliere ob die TankZeit gekommen ist.
			if(fmod(dGlobaleZeit,dTankZeit) < dEpsilon){
				fahrzeug->dTanken(fahrzeug->getTankvolumen());
			}
		}

		// Als erstes werden die Fahrzeuge ausgegeben, die aufm Autobahn fahren.
		autobahn->vSimulieren();
		cout << endl;
		innerort->vSimulieren();
		cout << endl;
		vSleep(500);
	}
	vBeendeGrafik();
}

void vAufgabe_6a(){

	// Wir moechten namespace vertagt benutzen, da alle Angaben unter diesem Name definiert wurden.
	using namespace vertagt;

	// Erstellen eine Liste vom Typ VListe
	VListe<int> VListe;

	// Zur Erstellung einer zufaelligen Zahl
	static std::mt19937 device(0);
	std::uniform_int_distribution<int> dist(1, 10);

	// Zahlen in die Liste eingeben.
	cout << "Zahlen werden in die Liste eingetragen.:\n\n";
	for(int i = 1; i < 10; i++){
		VListe.push_back(dist(device));
	}

	// Zahlen ausgeben
	cout << "Liste vor dem Aktualisieren:\n";
	for(auto it = VListe.begin(); it != VListe.end(); it++) {
		std::cout << (*it) << " ";
	}

	// Liste soll aktualisiert wernde, sonst konnten die Zahlen in die Liste nicht rein.
	cout << "\nListe wurde aktualisiert.\n\n";
	VListe.vAktualisieren();

	// Ausgeben nach dem Aktualisieren, soll sich gaeendert worden sein.
	cout << "Liste nach dem aktualiseren:\n";
	for(auto it = VListe.begin(); it != VListe.end(); it++) {
		std::cout << (*it) << " ";
	}

	// Loeschen der Elementen grosser als 5 sind.
	for(auto it = VListe.begin(); it != VListe.end(); it++) {
		if((*it) > 5) {
			VListe.erase(it);
		}
	}

	cout << "\n\nElemente grßer als 5 wurden gelscht aber nicht aktualisiert..\n";
	cout << "Liste:\n";
	// Ausgabe sollte die gleiche sein, da vAktualisieren noch nicht durchgefuehrt wurde
	for(auto it = VListe.begin(); it != VListe.end(); it++) {
		std::cout << (*it) << " ";
	}

	VListe.vAktualisieren();

	cout << "\n\nListe wurde aktualisiert. Liste:\n";
	// Ausgeben nach dem Aktualisieren, soll sich gaeendert worden sein.
	for(auto it = VListe.begin(); it != VListe.end(); it++) {
		cout << (*it) << " ";
	}

	// Eingeben in die Liste zwei mehr zufaellige Zahlen
	VListe.push_back(dist(device));
	VListe.push_front(dist(device));

	cout << "\n\nEine Zahl vorne und eine Zahl hinter werden hinzugefuegt.\n";
	cout << "Vor dem aktualiseren:\n";
	for(auto it = VListe.begin(); it != VListe.end(); it++) {
		cout << (*it) << " ";
	}

	// Liste soll aktualisiert werden.
	VListe.vAktualisieren();

	cout << "\n\nNach dem aktualisieren. Liste:\n";
	// Ausgabe sollte sich geaendert haben
	for(auto it = VListe.begin(); it != VListe.end(); it++) {
		std::cout << (*it) << " ";
	}
}

// Ohne grafische Ausgabe, altaere Aufgabe6
//void vAufgabe_6b(){
//
//	// Dynamisches Erzeugen aller Objekte.
//	unique_ptr<Weg> autobahn = make_unique<Weg>("Autobahn", 250);
//	unique_ptr<Weg> innerort = make_unique<Weg>("Innerort", 250, Innerorts);
//
//	unique_ptr<Fahrzeug> fahrzeug = make_unique<PKW>("PKW1", 123.35, 13.37);
//	unique_ptr<Fahrzeug> fahrzeug2 = make_unique<PKW>("PKW2", 155.37, 15.55, 62.37);
//	unique_ptr<Fahrzeug> fahrzeug3 = make_unique<PKW>("PKW3", 133.39, 12.22);
//	unique_ptr<Fahrzeug> fahrzeug4 = make_unique<PKW>("PKW4", 188.32, 16.37);
//
//	unique_ptr<Fahrzeug> fahrzeug5 = make_unique<Fahrrad>("Fahrrad1", 30.33);
//	unique_ptr<Fahrzeug> fahrzeug6 = make_unique<Fahrrad>("Fahrrad2", 25.35);
//
//
//	// Wege akzeptieren die Fahrzeuge.
//	cout << endl;
//	autobahn->vAnnahme(std::move(fahrzeug));
//	autobahn->vAnnahme(std::move(fahrzeug2),2);
//	autobahn->vAnnahme(std::move(fahrzeug5));
//
//	innerort->vAnnahme(std::move(fahrzeug3));
//	innerort->vAnnahme(std::move(fahrzeug4),3);
//	innerort->vAnnahme(std::move(fahrzeug6));
//
//
//
//	// In jeder x.x Stunden werden die Taenke der PKWs aufgefuellt.
//	double dTankZeit = 0.0;
//	cout << endl << "Bitte geben Sie eine Period fuer Tanken der PKWs: ";
//	cin >> dTankZeit;
//
//	// Wie lange eine Simulationsschritt dauert? -> dEpsilon
//	double dEpsilon = 0.0; // Zeittakt.
//	cout << endl << "Bitte geben Sie eine Period fuer die Simulation(lieber als Bruchteile von Studen): ";
//	cin >> dEpsilon;
//
//	// Gibt die Eigenschaften der Objekte aufm Bildschrim formatiert aus.
//	Fahrzeug::vKopf();
//	for(dGlobaleZeit = dEpsilon; dGlobaleZeit < 5; dGlobaleZeit += dEpsilon){
//		for(const auto& fahrzeug : *autobahn->getFahrzeugList()){
//			// Kontrolliere ob die TankZeit gekommen ist.
//			if(fmod(dGlobaleZeit,dTankZeit) < dEpsilon){
//				fahrzeug->dTanken(fahrzeug->getTankvolumen());
//			}
//		}
//		// Simuliere den Weg.
//		autobahn->vSimulieren();
//	}
//	dGlobaleZeit = 0;
//
//	// Gibt die Eigenschaften der Objekte aufm Bildschrim formatiert aus.
//	cout << "\n\nAutobahn wurde Simuliert. Nun wird der Innerort simuliert." << endl;
//	Fahrzeug::vKopf();
//	for(dGlobaleZeit = dEpsilon; dGlobaleZeit < 5; dGlobaleZeit += dEpsilon){
//		for(const auto& fahrzeug : *innerort->getFahrzeugList()){
//			// Kontrolliere ob die TankZeit gekommen ist.
//			if(fmod(dGlobaleZeit,dTankZeit) < dEpsilon){
//				fahrzeug->dTanken(fahrzeug->getTankvolumen());
//			}
//		}
//		// Simuliere den Weg.
//		innerort->vSimulieren();
//	}
//}

void vAufgabe_7(){
	double dStunden = 0.0;
	// Lese die gewuenschte Simulationzeit ein.(Benutzerfreundlciher)
	cout << "Bitte geben Sie die Simulationzeit in Stunden ein: ";
	cin >> dStunden;

	double dEpsilon = 0.0;
	// Einlesen der Zeittakt vom Benutzer.
	cout << endl << "Bitte geben Sie eine Period fuer die Simulation(lieber als Bruchteile von Studen): ";
	cin >> dEpsilon;

	// Erzeuge Kreuzungen und deren Strasse
	shared_ptr<Kreuzung> Kr1 = make_shared<Kreuzung>("Kr1");
	shared_ptr<Kreuzung> Kr2 = make_shared<Kreuzung>("Kr2", 1000);
	shared_ptr<Kreuzung> Kr3 = make_shared<Kreuzung>("Kr3", 0);
	shared_ptr<Kreuzung> Kr4 = make_shared<Kreuzung>("Kr4", 0);

	// Verbinde die Kreuzungen mit den Wegen
	Kreuzung::vVerbinde("W12", "W21", 40, Kr1, Kr2, Innerorts, false);
	Kreuzung::vVerbinde("W23a", "W32a", 115, Kr2, Kr3, Autobahn, true);
	Kreuzung::vVerbinde("W23b", "W32b", 40, Kr2, Kr3, Innerorts, false);
	Kreuzung::vVerbinde("W24", "W42", 55, Kr2, Kr4, Innerorts, false);
	Kreuzung::vVerbinde("W34", "W43", 85, Kr3, Kr4, Autobahn, true);
	Kreuzung::vVerbinde("W44a", "W44b", 130, Kr4, Kr4, Landstrasse, true);

	// Erzeuge Fahrzeuge
	unique_ptr<PKW> pkw1 = make_unique<PKW>("pkw1", 47.83, 11.27);
	unique_ptr<PKW> pkw2 = make_unique<PKW>("pkw2", 35.24, 15.88, 67.73);
	unique_ptr<Fahrrad> fahrrad1 = make_unique<Fahrrad>("fahrrad1", 21.34);
	unique_ptr<Fahrrad> fahrrad2 = make_unique<Fahrrad>("fahrrad2", 27.25);

	// KR1 nimmt alle Fahrzeuge an
	Kr1->vAnnahme(std::move(pkw1),1);
	Kr1->vAnnahme(std::move(pkw2),0.75);
	Kr1->vAnnahme(std::move(fahrrad1),0.25);
	Kr1->vAnnahme(std::move(fahrrad2),0.5);

	// Erzeuge eine Liste/Vektor dann zieht alle Kreuzungen in diese Liste um.
	vector<shared_ptr<Kreuzung>>kreuzungen;
	kreuzungen.push_back(Kr1);
	kreuzungen.push_back(Kr2);
	kreuzungen.push_back(Kr3);
	kreuzungen.push_back(Kr4);

	// Initsialisiere Grafik
	bInitialisiereGrafik(1000, 1000);


	// Zeichne Kreuzungen
	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	// Zeichne Strassen
	// Strasse 1
	int kS1[] = {680, 40, 680, 300};
	bZeichneStrasse("W12", "W21", 40, 2, kS1);

	// Strasse 2
	int kS2[] = {680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570};
	bZeichneStrasse("W23a", "W32a", 115, 6, kS2);

	// Strasse 3
	int kS3[] = {680, 300, 680, 570};
	bZeichneStrasse("W23b", "W32b", 40, 2, kS3);

	// Strasse 4
	int kS4[] = {680, 300, 320, 300};
	bZeichneStrasse("W24", "W42", 55, 2, kS4);

	// Strasse 5
	int kS5[] = {680, 570, 500, 570, 350, 510, 320, 420, 320, 300};
	bZeichneStrasse("W34", "W43", 85, 5, kS5);

	// Strasse 6
	int kS6[] = {320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300};
	bZeichneStrasse("W44a", "W44b", 130, 7, kS6);

	// Simuliere alle Kreuzungen in dieser Liste in einer For-loop bis ende der gegebenen Zeit.
	Fahrzeug::vKopf();
	for(dGlobaleZeit = dEpsilon; dGlobaleZeit < dStunden; dGlobaleZeit += dEpsilon){
		vSetzeZeit(dGlobaleZeit);
		for(const auto& kreuzung : kreuzungen){
			kreuzung->vSimulieren();
		}
		vSleep(500);
	}
	vBeendeGrafik();
}

// Lese die Daten der Objekte aus Einer Datei
// Gibt eine Ausnahme aus, wenn es einen Fehler gibt.(Z.B: Eroeffnung einer Datei)
// Wenn es keinen Fehler gibt, gibt die Daten der Objekten aus.
void vAufgabe_8(){

	ifstream inputFile("VO.dat");

	try{

		if(!inputFile.is_open()){
			throw runtime_error("Fehler bei der Eroerffnung der Datei.");
		}

		PKW porsche;
		Fahrrad rennrad;
		Kreuzung kr1;

		inputFile >> porsche >> rennrad >> kr1;

		Fahrzeug::vKopf();
		cout << porsche;
		cout << rennrad;
		cout << kr1 << endl;

		inputFile.close();

	} catch(const runtime_error& e){
		cerr << "Aufgefangene Exception: " << e.what() << endl;
	} catch(...){
		cerr << "Unbekannter Fehler." << endl;
	}
}

void vAufgabe_9(){
	double dStunden = 0.0;
	// Lese die gewuenschte Simulationzeit ein.(Benutzerfreundlciher)
	cout << "Bitte geben Sie die Simulationzeit in Stunden ein: ";
	cin >> dStunden;

	double dEpsilon = 0.0;
	// Einlesen der Zeittakt vom Benutzer.
	cout << "Bitte geben Sie eine Period fuer die Simulation(lieber als Bruchteile von Studen): ";
	cin >> dEpsilon;

	// Simulator wird die Dateieingabe einlesen und die Variablen fuer die Objekte einsetzen.
	// Nachdem der die Variable eingesetzt hat, wird der die Kreuzungen fuer der innerhalb gegebenen Zeit simulieren.
	// Achtung! -> Bei dieser Aufgabe gibt es keine grafische Ausgabe.
	Simulation simulator;
	ifstream inputFile("Simu6.dat");
	if (!inputFile.is_open()) {
		throw runtime_error("InputFile konnte nicht geoeffnet werden.");
	}
	simulator.vEinlesen(inputFile);
	inputFile.close();
	simulator.vSimulieren(dStunden, dEpsilon);
}

void vAufgabe_9a(){
	double dStunden = 0.0;
	// Lese die gewuenschte Simulationzeit ein.(Benutzerfreundlciher)
	cout << "Bitte geben Sie die Simulationzeit in Stunden ein: ";
	cin >> dStunden;

	double dEpsilon = 0.0;
	// Einlesen der Zeittakt vom Benutzer.
	cout << "Bitte geben Sie eine Period fuer die Simulation(lieber als Bruchteile von Studen): ";
	cin >> dEpsilon;

	// Simulator wird die Dateieingabe einlesen und die Variablen fuer die Objekte einsetzen.
	// Nachdem der die Variable eingesetzt hat, wird der die Kreuzungen fuer der innerhalb gegebenen Zeit simulieren.
	// Achtung! -> Bei dieser Aufgabe gibt es grafische Ausgabe.
	Simulation simulator;
	ifstream inputFile("SimuDisplay.dat");
	if (!inputFile.is_open()) {
		throw runtime_error("InputFile konnte nicht geoeffnet werden.");
	}
	simulator.vEinlesen(inputFile, true);
	inputFile.close();
	simulator.vSimulieren(dStunden, dEpsilon);
}