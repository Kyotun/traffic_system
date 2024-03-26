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
    Simulationsobjekt& operator=(const Simulationsobjekt& other);

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

// Ueberladung von '<<' (Ausgabe) Operator.
// Dekleration außerhalb der Klasse. Auf diese Weise kann der Ausgabeoperator die private bzw. protected Bereiche
// nicht erreichen kann.
// Also keine friend Dekleration.
// Aber getters werden benötigt, um die private bzw. protected Bereiche erreichen zu können.
ostream& operator<<(ostream& ausgabe, const Simulationsobjekt& simuobjekt);

// Ueberladung von operator>>(Eingabe Operator)
// Die Attributen koennen einfach durch die einkommende Eingabe eingesetzt werden.
istream& operator>>(istream& is, Simulationsobjekt& simuobjekt);

#endif /* SIMULATIONSOBJEKT_H_ */