#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include <string>
#include <iostream>

using namespace std;

class Simulationsobjekt{
public:
    // Konstruktoren
    Simulationsobjekt();
    Simulationsobjekt(string p_sName);

    // Verbieten von Copy-Konstruktor
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	// Destruktor
	virtual ~Simulationsobjekt();

protected:
	// Strings
	string p_sName = "";

	// Ints
	const int p_iID = ++p_iMaxID;

	// Doubles
	double p_dZeit = 0.0;

private:
	// Inline = To be able to initialize
	// const != cause we want to increment ID value. Cannot assign the const to a const.
	static inline int p_iMaxID = 0;

};

#endif /* SIMULATIONSOBJEKT_H_ */