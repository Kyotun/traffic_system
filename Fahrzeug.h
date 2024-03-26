#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <string>
#include <memory>
#include <iostream>
#include <limits>

#include "Simulationsobjekt.h"
#include "Verhalten.h"

class Weg;

extern double dGlobaleZeit;

class Fahrzeug : public Simulationsobjekt{
public:
	// Konstruktoren
	Fahrzeug() : Simulationsobjekt(){}
	Fahrzeug(string p_sName); // @suppress("Class members should be properly initialized")
	Fahrzeug(string p_sName, double p_dMaxGeschwindigkeit);

	// Destruktor
	virtual ~Fahrzeug() = default;

	// Verbieten von Copy-Konstruktor
	Fahrzeug(const Fahrzeug&) = delete;

protected:
	// Double Variablen
	double p_dMaxGeschwindigkeit = 0.0;
	double p_dGesamtstrecke = 0.0;
	double p_dGesamtZeit = 0.0;

	// Speichern auf dem aktuellen Weg zurückgelegte Strecke
	// Wenn Fahrzeug in einen neuen Weg eintritt, beträgt dieser Wert zu 0.
	double p_dAbschnittStrecke = 0.0;

	// Parkendes oder fahrendes Fahrzeug?
	unique_ptr<Verhalten> p_pVerhalten;

private:

};

#endif /* FAHRZEUG_H_ */