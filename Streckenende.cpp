#include <iostream>
#include <memory>
#include <string>

#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Streckenende.h"
#include "Weg.h"

extern double dGlobaleZeit;

// Wenn ein Fahrzeug am Ende eines Wegs gefahren ist, wird diese Methode von der Methode des Wegs vSimulieren aufgerufen.
// Durch try-catch Block.
void Streckenende::vBearbeiten(){
	// Print den Hinweis, dass das Fahrzeug am Ende des Wegs gekommen ist.
	cout << "\nDas Fahrzeug " << p_pFahrzeug.getName()
		 << " ist jetzt am Ende des Wegs " << p_pWeg.getName()
		 << " im Zeitpunkt " << dGlobaleZeit <<"." << endl;

	// Loescht das Fahrzeug von der Liste des Wegs
	unique_ptr<Fahrzeug> lokalFahrzeug = p_pWeg.pAbgabe(p_pFahrzeug);

	// Neur Weg, neue AbschnittStrecke
	lokalFahrzeug->setAbschnittStrecke(0.0);

	// Kreuzung,zu der das Fahrzeug aus dem Weg gefahren ist.
	shared_ptr<Kreuzung> lokalKreuzung = p_pWeg.getKreuzung();

	// Nimmt einen zufaelligen Weg, der von der Kreuzung anfangt.
	shared_ptr<Weg> lokalZufaelligerWeg = lokalKreuzung->pZufaelligerWeg(p_pWeg);

	// Tanken vom neu in der Kreuzung gefahrenden Fahrzeug.
	lokalKreuzung->vTanken(*lokalFahrzeug);

	// Umziehen vom Fahrzeug in den neuen Weg.
	lokalZufaelligerWeg->vAnnahme(std::move(lokalFahrzeug));

	// Gibt die Informationen aus.
	cout << "Das Fahrzeug " << p_pFahrzeug.getName()
		 << " hat auf dem Weg " << p_pWeg.getName()
		 << " das Streckenede erreicht." << std::endl;

	cout << "ZEIT     " << ": " << dGlobaleZeit << endl;
	cout << "KREUZUNG " << ": " << lokalKreuzung->getName() << ", Tankvolumen erhaeltlich(Liter): " << lokalKreuzung->getTankstelle() << endl;
	cout << "WECHSEL  " << ": " << p_pWeg.getName() << " -> " << lokalZufaelligerWeg->getName() << endl;
	cout << "FAHRZEUG " << ": " << p_pFahrzeug.getName() << endl;
}