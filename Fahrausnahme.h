#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>

class Weg;
class Fahrzeug;

// Fahrausnahme Klasse erbt von STL Exception.
class Fahrausnahme : public std::exception{
public:
	// Konstruktoren
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);

	// Destruktor
	virtual ~Fahrausnahme() = default;

	// Bearbeitung Methode fuer einige Faelle wie Streckenende, Losfahren etc.
	// Diese Methode wird geerbt von der Unterklasse und diese Klasse(Fahrausnahme) ist eine abstrakte Klasse.
	// Deswegen definieren wir diese Methode als eine rein virtuelle Methode.
	virtual void vBearbeiten()= 0;

protected:
	// Der Weg und das Fahrzeug, deren Informationen benoetigt werden, sollen gespeichert werden.
	// Nach deren Informationen funktionieren die Ausnahmeklassen.
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;
private:
};

#endif /* FAHRAUSNAHME_H_ */