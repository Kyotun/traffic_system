#include <memory>

#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"

using namespace std;
extern double dGlobaleZeit;

// Wenn fuer das parkende Fahrzeug die Zeit zum Fahren gekommen ist, gibt eine Meldung aufm Bildschrim aus.
// Dann loesche das Objekt von der Liste des Wegs dann nehme ich erneut an. Aber in diesem Fall ist das Fahrzeug
// ein fahrendes Fahrzeug statt parkendes.
void Losfahren::vBearbeiten()
{
	cout << "Das Fahrzeug " << p_pFahrzeug.getName()
		 << " fangt jetzt auf dem Weg " << p_pWeg.getName()
		 << " im Zeitpunkt " << dGlobaleZeit << " zu fahren." << endl;
	unique_ptr<Fahrzeug> lokal_ptr = p_pWeg.pAbgabe(p_pFahrzeug);
	p_pWeg.vAnnahme(std::move(lokal_ptr));
}