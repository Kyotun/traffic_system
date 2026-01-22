#include <list>
#include <random>

#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Weg.h"

using namespace std;

Kreuzung::Kreuzung(string sName, double dTankstelle) : Simulationsobjekt(sName),
													   p_dTankstelle(dTankstelle)
{
}

// Uebergebener Weg fuehrt zu dieser(this) Kreuzung und hat nur einen Rueckweg.
// Dieser Rueckweg ist in der Liste von dieser Kreuzung.
// Wenn es nur einen Weg gibt, der zu dieser Kreuzung fuehrt, wuerde dieser Weg ausgewaehlt muessen.
shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg &weg)
{
	if (p_pWege.empty())
	{
		throw runtime_error("Diese Kreuzung " + getName() + " enthaelt keinen Weg.");
	}

	shared_ptr<Weg> rueckWeg = weg.getRueckweg();
	if (!rueckWeg)
	{
		throw runtime_error("Es gibt keinen Rueckweg fuer uebergebenen Weg.");
	}

	// Kontrolliere, ob es nur einen Weg zu dieser Kreuzung gibt.
	// Wenn ja, gibt den Rueckweg zuerueck.
	if (p_pWege.size() == 1)
	{
		return rueckWeg;
	}

	// Wenn nein, nimmt alle Wege ausser diesen Rueckweg
	// und stelle diese in einer Liste, die nur den Rueckweg nicht enthaelt.
	list<shared_ptr<Weg>> filteredWege;
	for (const auto &wegPtr : p_pWege)
	{
		if (wegPtr != rueckWeg)
		{
			filteredWege.push_back(wegPtr);
		}
	}

	// Erzeuge einen zufaelligen Index zwischen 0 und groesse von filteredWege list.
	// Dann waehle einen Index zufaellig.
	// Gibt diesen zufaellig gewaehlten Index(Weg) zurueck.
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, filteredWege.size() - 1);
	int randomIndex = dis(gen);
	auto it = filteredWege.begin();
	std::advance(it, randomIndex);
	return *it;
}

// Verbinde zwei uebergebene Wege zueinander.
// Einer fuehrt zu der Zielkreuzung -> Hinweg
// Andere fuehrt zu der Startkreuzung -> Rueckweg

// Achtung ! -> Haengt von der Perspektive ab
// Lass uns sagen, dass es zwei Kreuzungen gibt -> Kr1, Kr2
// und zwei Wege gibt -> W1, W2
// W1, Rueckweg von W2
// W2, Rueckweg von W1
// W1 fuehrt aus Kr1
// W2 fuehrt aus Kr2
// Weg List der Kr1 enthaelt W1, nicht W2. Denn W1 fuehrt aus Kr1. Kr1 ist die Startkreuzung von W1, Kr2 ist aber die Zielkreuzung von W1.
// Weg List der Kr2 enthaelt W2, nicht W1. Denn W2 fuehrt aus Kr2. Kr2 ist die Startkreuzung von W2, Kr1 ist aber die Zielkreuzung von W2.
void Kreuzung::vVerbinde(string sNameHinweg, string sNameRuckweg,
						 double dWegLaenge, weak_ptr<Kreuzung> pStartKreuzung,
						 const weak_ptr<Kreuzung> pZielKreuzung,
						 Tempolimit eTempolimit, bool bUeberholverbot)
{

	shared_ptr<Weg> pHinweg = make_shared<Weg>(sNameHinweg,
											   dWegLaenge,
											   pZielKreuzung,
											   eTempolimit,
											   bUeberholverbot);
	shared_ptr<Weg> pRueckweg = make_shared<Weg>(sNameRuckweg,
												 dWegLaenge,
												 pStartKreuzung,
												 eTempolimit,
												 bUeberholverbot);

	pHinweg->setRueckweg(pRueckweg);
	pRueckweg->setRueckweg(pHinweg);

	pZielKreuzung.lock()->p_pWege.push_back(pRueckweg);
	pStartKreuzung.lock()->p_pWege.push_back(pHinweg);
}

// Tanken vom uebergebenen Fahrzeug.
// Wen die Kreuzung keine Kapazitaet hat, darf das Fahrzeug nicht getankt werden.
void Kreuzung::vTanken(Fahrzeug &fahrzeug)
{
	if (this->getTankstelle() <= 0)
	{
		return;
	}
	double dTankvolumen = fahrzeug.getTankvolumen();
	double dTankinhalt = fahrzeug.getTankinhalt();
	double dBrauchteTank = dTankvolumen - dTankinhalt;
	fahrzeug.dTanken(dBrauchteTank);
	this->setTankstelleMinus(dBrauchteTank);
}

// das uebergebene Fahrzeug wird zuerst getankt dann von der Kreuzung angenommen.(als parkend bis Startzeit)
void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> fahrzeug, double dStartzeit)
{
	if (p_pWege.empty())
	{
		throw runtime_error("Diese Kreuzung " + getName() + " enthaelt keinen Weg.");
	}
	vTanken(*fahrzeug);
	p_pWege.back()->vAnnahme(std::move(fahrzeug), dStartzeit);
}

// Simuliere jeden Weg, der sich zu der Kreuzung verbindet.
void Kreuzung::vSimulieren()
{
	// Simulieren der Wege an einer Kreuzung
	if (p_pWege.empty())
	{
		throw runtime_error("Diese Kreuzung " + getName() + " enthaelt keinen Weg.");
	}
	list<shared_ptr<Weg>>::iterator it;

	for (it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		(*it)->vSimulieren();
	}
}

void Kreuzung::vEinlesen(istream &is)
{
	Simulationsobjekt::vEinlesen(is);
	is >> p_dTankstelle;
}

// Kontrolliere, ob uebergebenen Weg in der Liste p_pWege ist.
bool Kreuzung::istInWegList(Weg &weg)
{
	if (p_pWege.empty())
	{
		throw runtime_error("Diese Kreuzung " + getName() + " enthaelt keinen Weg.");
	}

	for (auto &wegPtr : p_pWege)
	{
		if (wegPtr.get() == &weg)
		{
			return true;
		}
	}
	return false;
}
