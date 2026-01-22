#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_

#include "Fahrausnahme.h"

class Weg;
class Fahrzeug;

class Losfahren : public Fahrausnahme
{
public:
	// Konstruktoren
	Losfahren(Fahrzeug &fahrzeug, Weg &weg) : Fahrausnahme(fahrzeug, weg) {}

	// Voids
	void vBearbeiten() override;

protected:
private:
};

#endif /* LOSFAHREN_H_ */