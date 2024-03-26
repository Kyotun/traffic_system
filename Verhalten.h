#ifndef VERHALTEN_H_
#define VERHALTEN_H_

#include <memory>

class Weg;
class Fahrzeug;

using namespace std;

class Verhalten{
public:
	// Konstruktoren
	Verhalten() = default;
	Verhalten(Weg& weg): p_pWeg(&weg){}

	// Destruktor
	virtual ~Verhalten(){}

	// Getters
	Weg* getpWeg() const{return p_pWeg;}

    // Double
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) = 0;

protected:
	Weg* p_pWeg = nullptr;
private:
};

#endif /* VERHALTEN_H_ */