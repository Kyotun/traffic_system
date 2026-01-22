#ifndef PARKEN_H_
#define PARKEN_H_

#include "Verhalten.h"

class Fahrzeug;
class Weg;

using namespace std;

class Parken : public Verhalten
{
public:
	// Konstruktoren
	Parken() : Verhalten() {}
	Parken(Weg &weg, double dStartZeit) : Verhalten(weg), p_dStartZeit(dStartZeit) {}

	// Doubles
	double dStrecke(Fahrzeug &aFahrzeug, double dStartZeit) override;

protected:
private:
	double p_dStartZeit = 0.0;
};

#endif /* PARKEN_H_ */