#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"

class Weg;
class Fahrzeug;

// Fahren Verhalten erbt von der abstrakte Klasse Verhalten.
// Diese ist ein Verhalten, da Fahrzeuge entweder fahren oder parken koennen.
class Fahren : public Verhalten
{
public:
	// Konstruktoren
	Fahren() : Verhalten() {}
	Fahren(Weg &weg) : Verhalten(weg) {}

	// Fuer das Ausrechnen der aktuelle zuruckgelegte Strecke.
	virtual double dStrecke(Fahrzeug &fahrzeug, double dZeitDifferenz) override;

protected:
private:
};

#endif /* FAHREN_H_ */