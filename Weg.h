#ifndef WEG_H_
#define WEG_H_

#include <string>
#include <memory>

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

class Fahrzeug;
class Kreuzung;

using namespace std;
using namespace vertagt;
extern double dGlobaleZeit;

class Weg : public Simulationsobjekt{
public:
	// Konstruktoren
	Weg() : Simulationsobjekt(){}
	Weg(string sName, double dLaenge, Tempolimit eTempolimit = Tempolimit::Autobahn);
	Weg(string sName, double dLaenge, weak_ptr<Kreuzung>pZielkreuzung ,Tempolimit eTempolimit= Tempolimit::Autobahn, bool bUeberholverbot = true);

	// Getters
    double getTempolimit() const;
    Tempolimit gettTempolimit() const;
    void getFahrzeuge() const;
    shared_ptr<Weg> getRueckweg();
    shared_ptr<Kreuzung> getKreuzung() const;
	double getLaenge() const{return p_dLaenge;}
	double getSchranke()const{return this->p_dSchranke;}
	VListe<unique_ptr<Fahrzeug>>* getFahrzeugList(){return &p_pFahrzeuge;}
	bool getUeberholverbot()const{return this->p_bUeberholverbot;}

	// Setters
    void setTempolimiti(int iTempolimit);
    void setFahrzeug(unique_ptr<Fahrzeug> fahrzeug);
    void setFahrzeugList(list<unique_ptr<Fahrzeug>> fahrzeugList);
	void setLaenge(double dLaenge){this->p_dLaenge = dLaenge;}
	void setRueckweg(weak_ptr<Weg> pRueckweg){this->p_pRueckweg = pRueckweg;}
	void setUeberholverbot(bool bUeberholverbot){this->p_bUeberholverbot = bUeberholverbot;}
	void setSchranke(double dSchranke){this->p_dSchranke = dSchranke;}
	void setTempolimit(Tempolimit eTempolimit){this->p_eTempolimit = eTempolimit;}

    // Bools
	bool bIsLetzteFahrzeug(Fahrzeug& fahrzeug_gesucht);

    // Voids
	void vSimulieren() override;
    void vAusgeben() const override;
    void vAusgeben(ostream& ausgabes) const override;
    void static vKopf();
    void vAnnahme(unique_ptr<Fahrzeug> fahrzeug);

protected:
private:
	double p_dLaenge = 0.0;
	VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
	const weak_ptr<Kreuzung> p_pZielkreuzung;
	Tempolimit p_eTempolimit = Autobahn;
	bool p_bUeberholverbot = true;
	double p_dSchranke = 0.0;
	weak_ptr<Weg> p_pRueckweg;

};

ostream& operator<<(ostream& ausgabe,const Weg& weg);


#endif /* WEG_H_ */