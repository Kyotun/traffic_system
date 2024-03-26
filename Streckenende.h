#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_

#include "Fahrausnahme.h"

class Weg;
class Fahrzeug;

class Streckenende : public Fahrausnahme{
public:
	// Konstruktoren
	Streckenende(Fahrzeug& fahrzeug, Weg& weg): Fahrausnahme(fahrzeug, weg){}

	// Voids
	virtual void vBearbeiten() override;

protected:
private:
};

#endif /* STRECKENENDE_H_ */