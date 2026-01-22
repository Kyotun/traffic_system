#include <memory>
#include <string>
#include <list>
#include <iostream>
#include <iomanip>

#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Tempolimit.h"
#include "Weg.h"
#include "vertagt_liste.h"

using namespace std;
using namespace vertagt;
extern double dGlobaleZeit;

// Konstruktor fuer Weg Objekt mit 3 Parametern
Weg::Weg(string p_sName, double p_dLaenge, Tempolimit p_eTempolimit) : // @suppress("Member declaration not found") // @suppress("Class members should be properly initialized")
																	   Simulationsobjekt(p_sName), p_dLaenge(p_dLaenge), p_eTempolimit(p_eTempolimit)
{
}

Weg::Weg(string sName, // @suppress("Class members should be properly initialized")
		 double dLaenge,
		 weak_ptr<Kreuzung> pZielkreuzung,
		 Tempolimit eTempolimit,
		 bool bUeberholverbot) : Simulationsobjekt(sName),
								 p_dLaenge(dLaenge),
								 p_pZielkreuzung(pZielkreuzung),
								 p_eTempolimit(eTempolimit),
								 p_bUeberholverbot(bUeberholverbot)
{
}

// Wird das Tempolimit des Wegs zurueckgegeben
double Weg::getTempolimit() const
{
	cout << fixed << setprecision(2);
	return (double)p_eTempolimit;
}

Tempolimit Weg::gettTempolimit() const
{
	switch ((int)getTempolimit())
	{
	case 50:
		return Innerorts;
	case 100:
		return Landstrasse;
	default:
		return Autobahn;
	}
}

// Ausgeben der Namen der Fahrzeuge, die in der Liste p_pFahrzeuge sind.
void Weg::getFahrzeuge() const
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		const Fahrzeug *fahrzeug = it->get();
		if (it == --p_pFahrzeuge.end())
		{
			cout << fahrzeug->getName() << " ";
		}
		else
		{
			cout << fahrzeug->getName() << ", ";
		}
	}
}

// Gibt den Rueckweg dieses Wegs zurueck.
shared_ptr<Weg> Weg::getRueckweg()
{
	shared_ptr<Weg> sharedPtr = p_pRueckweg.lock();
	if (sharedPtr)
	{
		return sharedPtr;
	}
	else
	{
		throw runtime_error("Rueckweg Objekt wurde schon geloescht.");
	}
}

// Gibt die Zielkreuzung dieses Wegs zurueck.
shared_ptr<Kreuzung> Weg::getKreuzung() const
{
	shared_ptr<Kreuzung> sharedPtr = p_pZielkreuzung.lock();
	if (sharedPtr)
	{
		return sharedPtr;
	}
	else
	{
		throw runtime_error("Kreuzung Objekt wurde schon geloescht.");
	}
}

void Weg::setTempolimiti(int iTempolimit)
{
	switch (iTempolimit)
	{
	case 1:
		this->p_eTempolimit = Innerorts;
		break;
	case 2:
		this->p_eTempolimit = Landstrasse;
		break;
	case 3:
		this->p_eTempolimit = Autobahn;
		break;
	}
}

// Setzt das uebergebene Fahrzeug in der Liste p_pFahrzeuge ein.
void Weg::setFahrzeug(unique_ptr<Fahrzeug> fahrzeug)
{
	p_pFahrzeuge.push_back(std::move(fahrzeug));
	p_pFahrzeuge.vAktualisieren();
}

// Die uebergebene Liste wird nach der aktuelle Fahrzeugliste p_pFahrzeuge hinzugefuegt.
void Weg::setFahrzeugList(list<unique_ptr<Fahrzeug>> fahrzeugList)
{
	for (auto &&fahrzeugPtr : fahrzeugList)
	{
		p_pFahrzeuge.push_back(std::move(fahrzeugPtr));
		p_pFahrzeuge.vAktualisieren();
	}
}

// Wenn das uebergebene Fahrzeg das letzte ist, gibt true zurueck. Wenn nicht false.
bool Weg::bIsLetzteFahrzeug(Fahrzeug &fahrzeug_gesucht)
{
	for (auto rit = p_pFahrzeuge.rbegin(); rit != p_pFahrzeuge.rend(); ++rit)
	{
		if ((*rit).get() == &fahrzeug_gesucht)
		{
			return true;
		}
		if (++rit == p_pFahrzeuge.rend())
		{
			break;
		}
	}
	return false;
}

// Simulieren Methode der Klasse Weg.
void Weg::vSimulieren()
{

	p_pFahrzeuge.vAktualisieren();

	// Simuliere alle vorhandene Fahrzeuge in der Liste p_pFahrzeuge
	// Waehrend des Simuliieren kontrolliere, ob es einen Ausnahme auftritt.
	// Wenn ja, bearbeite diesen Ausnahme und mache weiter.
	// Wenn nein, mach einfach weiter.
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end();)
	{
		try
		{
			cout << *(*it);
			(*it)->vZeichnen(*this);
			(*it)->vSimulieren();
			it++;
		}
		catch (Fahrausnahme *fahrausnahme)
		{
			it++;
			fahrausnahme->vBearbeiten();
		}
	}
	p_pFahrzeuge.vAktualisieren();
}

// Ausgeben der Daten der Wegobjekte
void Weg::vAusgeben() const
{
	Simulationsobjekt::vAusgeben();
	cout << resetiosflags(ios::adjustfield)
		 << setiosflags(ios::left)
		 << setw(10) << ": " << getLaenge()
		 << setw(10) << "( ";
	getFahrzeuge();
	cout << ")";
}

// Ausgeben der Wegobjekte einfach mit cout << (operator<<)
void Weg::vAusgeben(ostream &ausgabe) const
{
	Simulationsobjekt::vAusgeben(ausgabe);
	ausgabe << setw(0) << ": "
			<< setw(15) << getLaenge()
			<< setw(0) << "( "
			<< setw(0);
	getFahrzeuge();
	ausgabe << ")";
}

// Klassenmethode vKopf, fuer tabellaerische Ausgabe wird diese Methode benutzt.
void Weg::vKopf()
{
	cout << endl
		 << resetiosflags(ios::adjustfield)
		 << setiosflags(ios::left)
		 << setw(8) << "ID"
		 << setw(15) << "| Name"
		 << setw(15) << "| Laenge"
		 << setw(15) << "| Fahrzeuge" << endl;

	cout << setw(8 + 15 * 3) << setfill('-') << '-' << setfill(' ') << endl;
}

// Uebergebene Fahrzeug wird als fahrend in der Liste p_pFahrzeuge gesetzt.
void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug)
{
	fahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(std::move(fahrzeug));
	p_pFahrzeuge.vAktualisieren();
}

// Uebergebene Fahrzeug wird als parkend bis zur StartZeitpunkt in der Liste p_pFahrzeuge gesetzt.
void Weg::vAnnahme(unique_ptr<Fahrzeug> fahrzeug, double dStartZeitpunkt)
{
	fahrzeug->vNeueStrecke(*this, dStartZeitpunkt);
	p_pFahrzeuge.push_front(std::move(fahrzeug));
	p_pFahrzeuge.vAktualisieren();
}

// Wenn das uebergebene Fahrzeug in der Fahrzeugliste dieses Wegs ist,
// wird es geloescht und geloeschtes Fahrzeug wird zurueckgegeben.
// Wenn es nicht in der Liste ist, wird nullptr zurueckgegeben.
unique_ptr<Fahrzeug> Weg::pAbgabe(Fahrzeug &fahrzeug_gesucht)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		// ueberpruefen des Iterationselementes mit gewuenschtem Fahrzeug
		if ((*it).get() == &fahrzeug_gesucht)
		{
			// Lokale Variable zur Zwischenspeicherung
			unique_ptr<Fahrzeug> lokal_fahrzeug = std::move(*it);
			// Loeschen des Fahrzeugs aus der Liste
			p_pFahrzeuge.erase(it);
			p_pFahrzeuge.vAktualisieren();
			return lokal_fahrzeug;
		}
	}
	return nullptr;
}