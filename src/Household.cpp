#include "Household.hpp"

Tree Household::householdTree;

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

Household::Household(float wealth, float ecologicalSensibility, int size) {

	// wealth = [0;1]
	this->wealth = wealth;


	
	
}

Household::~Household() {

}

int Household::getMinors() {
	return people[0] + people[1] + people[2];
}

int Household::getChildren() {
	return children;
}

int Household::getAdults() {
	return people[3] + people[4] + people[5] + people[6];
}

int Household::getPensioners() {
	return people[6];
}

int Household::getStudents() {
	return people[3];
}

int Household::getUnemployed() {
	return people[5];
}

int Household::getWorker() {
	return people[4];
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

Tree Household::setTreeRealistic() {

	Tree t;

	Node root = t.getRoot();
	root.addChild(PENSIONERS);
	root.addChild(FAMILIES);
	root.addChild(SINGLES);
	root.addChild(SHARED);


	Node pensioners = root.getChildren()[0];
	int arr [] = {0,0,0,0,0,0,1};
	pensioners.addChild(PENSIONERSINGLE,arr);
	int arr2 [] = {0,0,0,0,0,0,2};
	pensioners.addChild(PENSIONERCOUPLE,arr2);

	Node families = root.getChildren()[1];
	families.addChild(PARENTSINGLE);
	families.addChild(PARENTCOUPLE);

	Node singles = root.getChildren()[2];
	int arr3 [] = {0,0,0,0,1,0,0};
	singles.addChild(SINGLEWORKER, arr3);
	int arr4 [] = {0,0,0,0,0,1,0};
	singles.addChild(SINGLEUNEMPLOYED, arr4);
	int arr5 [] = {0,0,0,1,0,0,0};
	singles.addChild(SINGLESTUDENT, arr5);

	Node shared = root.getChildren()[3];
	int arr6 [] = {0,0,0,2,0,0,0};
	shared.addChild(SHAREDTWO, arr6);
	int arr7 [] = {0,0,0,3,0,0,0};
	shared.addChild(SHAREDTHREE, arr7);
	int arr8 [] = {0,0,0,4,0,0,0};
	shared.addChild(SHAREDFOUR, arr8);
	int arr9 [] = {0,0,0,5,0,0,0};
	shared.addChild(SHAREDFIVE, arr9);

	Node singleParents = families.getChildren()[0];
	// singleParents.addChild(SINGLEPARENTWORKER)

	return t;

}

void Household::createPeople(Node n) {

		if (n.hasChildren()) {
			// Innenknoten
			float ran = (float)(rand() % (int)(n.getSumOfValues(n.getChildren().size()) * 1000)) / 1000.f;
			std::cout << ran << std::endl;
			for (int i = 0; i < n.getChildren().size(); i++) {
				if (ran < n.getChildren()[i].getValue()) {
					createPeople(n.getChildren()[i]);
					break;
				}
			}
		} else {
			// Blattknoten
			for (int i = 0; i < 7; i++) {
				people[i] = n.getAmount()[i];
			}
		}
	

}

void Household::setSimpleTree() {

	if (!Household::householdTree.getRoot().hasChildren()) {

		Node root = Household::householdTree.getRoot();

		Node A = Household::householdTree.getRoot().addChild(A_RENTNER);
		Node B = Household::householdTree.getRoot().addChild(B_FAMILIEN);
		Node C = Household::householdTree.getRoot().addChild(C_PAARE);
		Node D = Household::householdTree.getRoot().addChild(D_ALLEINLEBENDE);
		Node E = Household::householdTree.getRoot().addChild(E_WGS);

		std::cout << Household::householdTree.getRoot().getChildren().size() << std::endl;

		int arrA1 [] = {0,0,0,0,0,0,1};
		A.addChild(A1_EINRENTNER, arrA1);
		int arrA2 [] = {0,0,0,0,0,0,2};
		A.addChild(A2_ZWEIRENTNER, arrA2);

		Node B1 = B.addChild(B1_EINELTERNTEIL);
		Node B2 = B.addChild(B2_ZWEIELTERNTEILE);
		

		int arrC1 [] = {0,0,0,0,2,0,0};
		C.addChild(C1_ZWEIARBEITSSUCHEND, arrC1);
		int arrC2 [] = {0,0,0,0,0,2,0};
		C.addChild(C2_ZWEIARBEITSLOS, arrC2);
		int arrC3 [] = {0,0,0,0,1,1,0};
		C.addChild(C3_ZWEIMIX, arrC3);

		int arrD1 [] = {0,0,0,1,0,0,0};
		D.addChild(D1_ALLEINSTUDENT, arrD1);
		int arrD2 [] = {0,0,0,0,1,0,0};
		D.addChild(D2_ALLEINARBEITSSUCHEND, arrD2);
		int arrD3 [] = {0,0,0,0,0,1,0};
		D.addChild(D3_ALLEINARBEITSLOS, arrD3);

		int arrE1 [] = {0,0,0,2,0,0,0};
		E.addChild(E1_ZWEIERWG, arrE1);
		int arrE2 [] = {0,0,0,3,0,0,0};
		E.addChild(E2_DREIERWG, arrE2);
		int arrE3 [] = {0,0,0,4,0,0,0};
		E.addChild(E3_VIERERWG, arrE3);
		int arrE4 [] = {0,0,0,5,0,0,0};
		E.addChild(E4_FUNFERWG, arrE4);

	}

	// std::cout << Household::householdTree.getRoot().getChildren().size() << std::endl;

}

void Household::createSimplePeople(Node n) {

	// std::cout << n.getChildren().size() << std::endl;

	if (n.hasChildren()) {
		// Innenknoten
		float ran = (float)(rand() % (int)(n.getSumOfValues(n.getChildren().size()) * 1000)) / 1000.f;
		std::cout << ran << std::endl;
		for (int i = 0; i < n.getChildren().size(); i++) {
			if (ran < n.getChildren()[i].getSumOfValues(i)) {
				createSimplePeople(n.getChildren()[i]);
				break;
			}
		}
	} else {
		// Blattknoten
		for (int i = 0; i < 7; i++) {
			people[i] = n.getAmount()[i];
		}
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

void Household::printResidents() {
	
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

void Household::printTransportation() {

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