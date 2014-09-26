#include "Household.hpp"

Household::Household() {

	people.push_back(0);	// 0-Kleinkinder
	people.push_back(0);	// 1-Kinder
	people.push_back(0);	// 2-Jugendliche
	people.push_back(0);	// 3-Studenten
	people.push_back(0);	// 4-Arbeitssuchende
	people.push_back(0);	// 5-Dauerhaft Arbeitslose
	people.push_back(0);	// 6-Rentner
	children = 0;

	createRandomPeople();

	cars = 0;
	bikes = 0;

	createTransportation();
	
}

Household::~Household() {

}

int Household::getMinors() const {
	return people[0] + people[1] + people[2];
}

int Household::getChildren() const {
	return children;
}

int Household::getAdults() const {
	return people[3] + people[4] + people[5] + people[6];
}

int Household::getPensioners() const {
	return people[6];
}

int Household::getStudents() const {
	return people[3];
}

int Household::getUnemployed() const {
	return people[5];
}

int Household::getWorker() const {
	return people[4];
}

unsigned int Household::getResidents() const {
	unsigned int res = 0;
	for (auto p : people) {
		res += p;
	}
	return res;
}

void Household::createRandomPeople() {

	float added = A_RENTNER + B_FAMILIEN + C_PAARE + D_ALLEINLEBENDE + E_WGS;
	int ran = rand() % (int)added;
	if (ran < A_RENTNER) {
		
		added = A1_EINRENTNER + A2_ZWEIRENTNER;
		ran = rand() % (int)added;
		if (ran < A1_EINRENTNER) people[6] += 1;
		else people[6] += 2;

	} else if (ran < A_RENTNER + B_FAMILIEN) {

		added = B1_EINELTERNTEIL + B2_ZWEIELTERNTEILE;
		ran = rand() % (int)added;
		if (ran < B1_EINELTERNTEIL) {

			added = B1_ALLEINERZIEHENDARBEITSSUCHEND + B1_ALLEINERZIEHENDARBEITSLOS;
			ran = rand() % (int)added;
			
			if (ran < B1_ALLEINERZIEHENDARBEITSSUCHEND) people[4] += 1;
			else people[5] += 1;

			int c;
			added = B1_EINKIND + B1_ZWEIKINDER + B1_DREIKINDER;
			ran = rand() % (int)added;
			if (ran < B1_EINKIND) c = 1;
			else if (ran < B1_EINKIND + B1_ZWEIKINDER) c = 2;
			else c = 3;

			children = c;

			added = B1_KLEINKIND + B1_KIND + B1_JUGENDLICHER + B1_STUDENT + B1_ARBEITSSUCHENDESKIND;
			for (int i = 0; i < c; i++) {

				ran = rand() % (int)added;
				if (ran < B1_KLEINKIND) people[0] += 1;
				else if (ran < B1_KLEINKIND + B1_KIND) people[1] += 1;
				else if (ran < B1_KLEINKIND + B1_KIND + B1_JUGENDLICHER) people[2] += 1;
				else if (ran < B1_KLEINKIND + B1_KIND + B1_JUGENDLICHER + B1_STUDENT) people[3] += 1;
				else people[4] += 1;

			}

		} else {

			added = B2_ELTERNARBEITSSUCHEND + B2_ELTERNARBEITSLOS + B2_ELTERNMIX;
			ran = rand() % (int)added;
			if (ran < B2_ELTERNARBEITSSUCHEND) people[4] += 2;
			else if (ran < B2_ELTERNARBEITSSUCHEND + B2_ELTERNARBEITSLOS) people[5] += 2;
			else { people[4] += 1; people[5] += 1; }

			int c;
			added = B2_EINKIND + B2_ZWEIKINDER + B2_DREIKINDER;
			ran = rand() % (int)added;
			if (ran < B2_EINKIND) c = 1;
			else if (ran < B2_EINKIND + B2_ZWEIKINDER) c = 2;
			else c = 3;

			children = c;

			added = B2_KLEINKIND + B2_KIND + B2_JUGENDLICHER + B2_STUDENT + B2_ARBEITSSUCHENDESKIND;
			for (int i = 0; i < c; i++) {

				ran = rand() % (int)added;
				if (ran < B2_KLEINKIND) people[0] += 1;
				else if (ran < B2_KLEINKIND + B2_KIND) people[1] += 1;
				else if (ran < B2_KLEINKIND + B2_KIND + B2_JUGENDLICHER) people[2] += 1;
				else if (ran < B2_KLEINKIND + B2_KIND + B2_JUGENDLICHER + B2_STUDENT) people[3] += 1;
				else people[4] += 1;

			}

		}

	} else if (ran < A_RENTNER + B_FAMILIEN + C_PAARE) {
		
		added = C1_ZWEIARBEITSSUCHEND + C2_ZWEIARBEITSLOS + C3_ZWEIMIX;
		ran = rand() % (int)added;
		if (ran < C1_ZWEIARBEITSSUCHEND) people[4] += 2;
		else if (ran < C1_ZWEIARBEITSSUCHEND + C2_ZWEIARBEITSLOS) people[5] += 2;
		else { people[4] += 1; people[5] += 1; }

	} else if (ran < A_RENTNER + B_FAMILIEN + C_PAARE + D_ALLEINLEBENDE) {
		
		added = D1_ALLEINSTUDENT + D2_ALLEINARBEITSSUCHEND + D3_ALLEINARBEITSLOS;
		ran = rand() % (int)added;
		if (ran < D1_ALLEINSTUDENT) people[3] += 1;
		else if (ran < D1_ALLEINSTUDENT + D2_ALLEINARBEITSSUCHEND) people[4] += 1;
		else people[5] += 1;

	} else {

		added = E1_ZWEIERWG + E2_DREIERWG + E3_VIERERWG + E4_FUNFERWG;
		ran = rand() % (int)added;
		if (ran < E1_ZWEIERWG) people[3] += 2;
		else if (ran < E1_ZWEIERWG + E2_DREIERWG) people[3] += 3;
		else if (ran < E1_ZWEIERWG + E2_DREIERWG + E3_VIERERWG) people[3] += 4;
		else people[3] += 5;

	}

}

void Household::createTransportation() {

	/*
		Je reicher desto mehr Autos & Fahrräder
	*/

	cars = (int)(wealth * getAdults());
	bikes = (int)(wealth * (getAdults() + getMinors() - people[0]));

	if (people[4] > 0 && cars == 0) cars++;

}

void Household::printResidents() const {
	
	std::cout << "In diesem Haushalt leben " << getAdults() << " Erwachsene: " << std::endl;
	if (people[4] > 0) std::cout << "\t" << people[4] << " Arbeiter" << std::endl;
	if (people[5] > 0) std::cout << "\t" << people[5] << " Arbeitslose" << std::endl;
	if (people[6] > 0) std::cout << "\t" << people[6] << " Rentner" << std::endl;
	if (people[3] > 0) std::cout << "\t" << people[3] << " Studenten" << std::endl;
	if (getMinors() > 0) std::cout << "und " << getMinors() << " Minderjährige: " << std::endl;
	if (people[2] > 0) std::cout << "\t" << people[2] << " Jugendliche" << std::endl;
	if (people[1] > 0) std::cout << "\t" << people[1] << " Kinder" << std::endl;
	if (people[0] > 0) std::cout << "\t" << people[0] << " Kleinkinder" << std::endl;

}

void Household::printTransportation() const {

	std::cout << "Dieser Haushalt besitzt ";

	if (cars > 0) {
		std::cout << cars << " Autos";
		if (bikes > 0 ) std::cout << " und " << bikes << " Fahrräder." << std::endl;
		else std::cout << "." << std::endl;
	} else if (bikes > 0) {
		std::cout << bikes << " Fahrräder." << std::endl;
	} else {
		std::cout << "weder Autos noch Fahrräder." << std::endl;
	}

}