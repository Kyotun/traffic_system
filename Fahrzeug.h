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

    // Getters
	virtual double getMaxGeschwindigkeit() const{return p_dMaxGeschwindigkeit;}
	double getGesamtstrecke() const {return p_dGesamtstrecke;}
	double getGesamtZeit() const {return p_dGesamtZeit;}
	double getZeit() const {return p_dZeit;}
	double getGlobaleZeit() const {return dGlobaleZeit;}
	virtual double getGesamtVerbrauch() const {return 0.0;}
	virtual double getTankinhalt() const {return 0.0;}
	virtual double getTankvolumen() const {return 0.0;}
	double getAbschnittStrecke() const{return p_dAbschnittStrecke;}
	const unique_ptr<Verhalten>& getVerhalten()const{return p_pVerhalten;}

	// Setters
	void setMaxGeschwindigkeit(double p_dMaxGeschwindigkeit){this->p_dMaxGeschwindigkeit = p_dMaxGeschwindigkeit;}
	void setGesamtstrecke(double p_dGesamtstrecke){this->p_dGesamtstrecke = p_dGesamtstrecke;}
	void setAbschnittStrecke(double dAbschnittStrecke){this->p_dAbschnittStrecke = dAbschnittStrecke;}
	void vResetAbschnittStrecke(){this->p_dAbschnittStrecke = 0;}

    // Doubles
	virtual double dGeschwindigkeit() const{return p_dMaxGeschwindigkeit;}; 
    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()){return 0.0;};

    // Void&Print Funktionen
	virtual void vAusgeben() const override;
    virtual void vAusgeben(ostream& ausgabe)const override;
    static void vKopf();
    virtual void vSimulieren() override;
    void vNeueStrecke(Weg& weg);
    void vNeueStrecke(Weg& weg, double dStartZeitpunkt);
    virtual void vEinlesen(istream& is) override;
	virtual void vZeichnen(const Weg& weg){}

    // Ueberladen der operatoren
	bool operator<(const Fahrzeug& andere) const;
    Fahrzeug& operator=(const Fahrzeug& other);


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