#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include "Fahrzeug.h"

using namespace std;

class Fahrrad : public Fahrzeug {
public:
	// Konstruktoren
	Fahrrad() : Fahrzeug(){}
	Fahrrad(string p_sName);
	Fahrrad(string p_sName, double p_dMaxGeschwindigkeit);

    // Doubles
	double dGeschwindigkeit() const override; // Minimal 12km /h , pro 20km %10 Abnahme

private:

};
#endif /* FAHRRAD_H_ */