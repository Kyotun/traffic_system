#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>
#include <map>
#include <memory>

#include "Tempolimit.h"
#include "Kreuzung.h"

using namespace std;

class Simulation{
public:

    // Getters
	shared_ptr<Kreuzung> getKreuzung(const string& name);

    // Voids
    void vCheckKreuzung(const string& name);
	void vCheckDoppelKreuzung(const string& name);
    void vAddKreuzung(const string& name, shared_ptr<Kreuzung> kreuzung);
    void vAktualisiereKreuzung(const string& name, shared_ptr<Kreuzung> kreuzung);
    void vSimulieren(double dDauer, double dZeitschritt);

    // Checkers
	void vCheckKreuzungName(string name);

    // Converters
	Tempolimit convertTempolimit(int iTempolimit);

private:
	map<string, shared_ptr<Kreuzung>> kreuzungenMap;
};

#endif /* SIMULATION_H_ */