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

    // Getters
	string getName() const{return p_sName;}
	double getZeit() const {return p_dZeit;}
	int getID() const {return p_iID;}

    // Setters
	void setName(string p_sName){this->p_sName = p_sName;}
	void setZeit(double p_dZeit){this->p_dZeit = p_dZeit;}

    // Voids
	virtual void vAusgeben() const;
    virtual void vAusgeben(ostream& ausgabe) const;
    virtual void vSimulieren() = 0;
    virtual void vEinlesen(istream& is);

    // Ueberladen der Operatoren
	bool operator==(const Simulationsobjekt& andere);

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