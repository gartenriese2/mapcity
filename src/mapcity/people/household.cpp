#include "household.hpp"

#include "../../engine/debug.hpp"

#include <random>
#include <cassert>

Household::Household() {

}

unsigned int Household::getNum(People::AGE age) const {

	unsigned int num {0};
	for (const auto pplPtr : m_people) {
		if (pplPtr->getAge() == age) ++num;
	}
	return num;

}

unsigned int Household::getNum(People::OCCUPATION occ) const {

	unsigned int num {0};
	for (const auto pplPtr : m_people) {
		if (pplPtr->getOccupation() == occ) ++num;
	}
	return num;

}

void Household::addPeople(std::shared_ptr<People> ppl) {

	if (ppl) {
		
		m_people.emplace_back(ppl);

	}

}

/*
*	STATIC
*/

void addChild(Household & house, const std::vector<float> & percentages, float perc) {

	assert(percentages.size() == 4);

	if (perc < percentages[0]) {
		house.addPeople(std::make_shared<People>(People::AGE::INFANT, People::OCCUPATION::NONE));
	} else if (perc < percentages[1]) {
		house.addPeople(std::make_shared<People>(People::AGE::KID, People::OCCUPATION::PRESCHOOL));
	} else if (perc < percentages[2]) {
		house.addPeople(std::make_shared<People>(People::AGE::TEEN, People::OCCUPATION::SCHOOL));
	} else if (perc < percentages[3]) {
		house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::UNIVERSITY));
	} else {
		house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::WORK));
	}

}

const Household Household::generateRandomHousehold() {

	/*
	* an Deutschland angelehnt
	*/

	// root
	constexpr float PENSIONERS {25.7f}; // 25.7% Rentner
	constexpr float FAMILIES {73.4f};	// 47.7% Familien
	constexpr float SINGLES {98.5f};	// 25.1% Alleinlebende
	//constexpr float SHARED {100.f};	//  1.5% Wohngemeinschaften

	// Rentner
	constexpr float PENSIONERSINGLE {59.4f};	// 59.4% Alleinlebende Rentner
	//constexpr float PENSIONERCOUPLE {100.f};	// 40.6% Zusammenlebende Rentner

	// Familien
	constexpr float PARENTSINGLE {13.9f};	// 13.9% Alleinerziehende
	//constexpr float PARENTCOUPLE {100.f};	// 86.1% Paare

	// Alleinlebende
	constexpr float SINGLEWORKER {73.8f};		// 73.8% Alleinlebende Arbeitssuchende
	constexpr float SINGLEUNEMPLOYED {98.f};	// 24.2% Alleinlebende dauerhaft Arbeitslose
	//constexpr float SINGLESTUDENT {100.f};		//  2.0% Alleinlebende Studenten

	// Wohngemeinschaften
	constexpr float SHAREDTWO {50.0f};		// 50.0% 2er-WG
	constexpr float SHAREDTHREE {85.0f};	// 35.0% 3er-WG
	constexpr float SHAREDFOUR {95.0f};		// 10.0% 4er-WG
	//constexpr float SHAREDFIVE {100.f};	//  5.0% 5er-WG

	// Alleinerziehende -> Arbeitssituation
	constexpr float SINGLEPARENTWORKER {57.5f};		// 57.5% Alleinerziehende Arbeitssuchende
	//constexpr float SINGLEPARENTUNEMPLOYED {100.f};	// 42.5% Alleinerziehende dauerhaft Arbeitslose

	// Alleinerziehende -> Kinder
	constexpr float SINGLEONEKID {69.1f};		// 69.1% Alleinerziehende mit 1 Kind
	constexpr float SINGLETWOKIDS {93.4f};		// 24.3% Alleinerziehende mit 2 Kindern
	//constexpr float SINGLETHREEKIDS {100.f};	//  6.6% Alleinerziehende mit 3 Kindern

	// Alleinerziehende -> Kindesalter
	constexpr float SINGLEINFANT {17.2f};		// 17.2% Kleinkinder bei Alleinerziehenden
	constexpr float SINGLEKID {47.2f};			// 30.0% Kinder bei Alleinerziehenden
	constexpr float SINGLETEEN {59.1f};			// 11.9% Jugendliche bei Alleinerziehenden
	constexpr float SINGLEWITHSTUDENT {77.1f};	// 18.0% Studenten bei Alleinerziehenden
	//constexpr float SINGLEWITHWORKER {100.f};	// 22.9% Arbeitssuchende Kinder bei Alleinerziehenden

	// Paare -> Arbeitssituation
	constexpr float COUPLEONLYWORKER {56.f};		// 56.0% arbeitssuchende Paare
	constexpr float COUPLEONLYUNEMPLOYED {60.f};	//  4.0% dauerhaft arbeitslose Paare
	//constexpr float COUPLEWORKERUNEMPLOYED {100.f};	// 40.0% Paar mit arbeitssuchend/arbeitslos

	// Paare -> Kinder
	constexpr float COUPLEZEROKIDS {45.6f};		// 45.6% Paare ohne Kinder
	constexpr float COUPLEONEKID {71.5f};		// 25.9% Paare mit 1 Kind
	constexpr float COUPLETWOKIDS {92.9f};		// 21.4% Paare mit 2 Kindern
	//constexpr float COUPLETHREEKIDS {100.f};	//  7.1% Paare mit 3 Kindern

	// Paare -> Kindesalter
	constexpr float COUPLEINFANT {30.1f};		// 30.1% Kleinkinder bei Paaren
	constexpr float COUPLEKID {61.7f};			// 31.6% Kinder bei Paaren
	constexpr float COUPLETEEN {72.0f};			// 10.3% Jugendliche bei Paaren
	constexpr float COUPLESTUDENT {84.0f};		// 12.0% Studenten bei Paaren
	//constexpr float COUPLEWITHWORKER {100.f};	// 16.0% Arbeitssuchende Kinder bei Paaren

	static const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	static const std::default_random_engine generator(static_cast<unsigned long>(seed));
	static const std::uniform_real_distribution<float> distribution(0.f,100.f);
	static auto percent = std::bind(distribution, generator);

	Household house;

	const auto root = percent();
	if (root < PENSIONERS) {
		
		house.addPeople(std::make_shared<People>(People::AGE::SENIOR, People::OCCUPATION::NONE));
		if (percent() >= PENSIONERSINGLE) {
			house.addPeople(std::make_shared<People>(People::AGE::SENIOR, People::OCCUPATION::NONE));
		}

	} else if (root < FAMILIES) {
		
		const auto tmp = percent();
		if (tmp < PARENTSINGLE) {
			// Alleinerziehend
			if (percent() < SINGLEPARENTWORKER) {
				house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::WORK));
			} else {
				house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::NONE));
			}

			const std::vector<float> percentages {SINGLEINFANT, SINGLEKID, SINGLETEEN, SINGLEWITHSTUDENT};
			const auto num = percent();
			if (num < SINGLEONEKID) {
				addChild(house, percentages, percent());
			} else if (num < SINGLETWOKIDS) {
				addChild(house, percentages, percent());
				addChild(house, percentages, percent());
			} else {
				addChild(house, percentages, percent());
				addChild(house, percentages, percent());
				addChild(house, percentages, percent());
			}

		} else {
			// Paar
			const auto work = percent();
			if (work < COUPLEONLYWORKER) {
				house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::WORK));
				house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::WORK));
			} else if (work < COUPLEONLYUNEMPLOYED) {
				house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::NONE));
				house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::NONE));
			} else {
				house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::WORK));
				house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::NONE));
			}

			const auto num = percent();
			if (num > COUPLEZEROKIDS) {
				
				const std::vector<float> percentages {COUPLEINFANT, COUPLEKID, COUPLETEEN, COUPLESTUDENT};
				if (num < COUPLEONEKID) {
					addChild(house, percentages, percent());
				} else if (num < COUPLETWOKIDS) {
					addChild(house, percentages, percent());
					addChild(house, percentages, percent());
				} else {
					addChild(house, percentages, percent());
					addChild(house, percentages, percent());
					addChild(house, percentages, percent());
				}

			}
		}

	} else if (root < SINGLES) {

		const auto work = percent();
		if (work < SINGLEWORKER) {
			house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::WORK));
		} else if (work < SINGLEUNEMPLOYED) {
			house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::NONE));
		} else {
			house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::UNIVERSITY));
		}

	} else {

		house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::UNIVERSITY));
		house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::UNIVERSITY));

		const auto num = percent();
		if (num > SHAREDTWO) {
			house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::UNIVERSITY));
		}
		if (num > SHAREDTHREE) {
			house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::UNIVERSITY));
		}
		if (num > SHAREDFOUR) {
			house.addPeople(std::make_shared<People>(People::AGE::ADULT, People::OCCUPATION::UNIVERSITY));
		}

	}

	return house;

}

const std::vector<Household> Household::generateRandomHouseholds(unsigned int n) {

	assert(n > 0);

	std::vector<Household> vec;

	for (unsigned int i {0}; i < n; ++i) {
		vec.emplace_back(std::move(Household::generateRandomHousehold()));
	}

	return vec;

}
