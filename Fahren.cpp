#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

// Ausrechnen der aktuelle zuruckgelegten Strecke des fahrenden Fahrzeuges
double Fahren::dStrecke(Fahrzeug& fahrzeug, double dZeitDifferenz){
	double dTeilStrecke = fahrzeug.dGeschwindigkeit()*dZeitDifferenz;
	double dLaenge = p_pWeg->getLaenge();
	double dAbschnittStrecke = fahrzeug.getAbschnittStrecke();

	// Wenn es ein Ueberholverbot gibt, soll die Schranke beobachtet werden.
	// Falls die Schranke schon gesetzt ist, darf dieses Fahrzeug maximal bis zu dieser Schranke weiterfahren.
	// Wenn die Schranke nicht ueberschritten wird, faehrt das Fahrzeug bis, wo es fahren kann.
	// Wenn aber die Schranke ueberschritten wird, wird die TeilStrecke nach dieser Situation berechnet.
	if(p_pWeg->getUeberholverbot()){
		double dSchranke = p_pWeg->getSchranke();
		if(dAbschnittStrecke < dSchranke){
			double dNeuAbschnittStrecke = dTeilStrecke + dAbschnittStrecke;
			if(dNeuAbschnittStrecke > dSchranke){
				dTeilStrecke = dSchranke - dAbschnittStrecke;
			}
		}
	}

	// Kontrolliere, was wuerde passieren, wenn der letzte Teil auch gefahren wuerde?
	// Wenn der noch gefahren werden kann, return einfach die TeilStrecke
	// Wenn nicht, gibt eine Meldung durch die Ausnahmeklasse Streckenende aus,
	// waehrend das Fahrzeug am Ende des Wegs gestellt wird.
	if(dLaenge-dAbschnittStrecke < dTeilStrecke){
		fahrzeug.setAbschnittStrecke(dLaenge);
		throw new Streckenende(fahrzeug, *p_pWeg);
	}
	return dTeilStrecke;

}