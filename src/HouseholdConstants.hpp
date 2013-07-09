#ifndef HOUSEHOLDCONSTANTS_HPP
#define HOUSEHOLDCONSTANTS_HPP

namespace HouseholdConstants {

	/*
	* an Deutschland angelehnt
	*/

	// type0
	const float PENSIONERS = 25.7f; // 25.7% Rentner
	const float FAMILIES = 73.4f;	// 47.7% Familien
	const float SINGLES = 98.5f;	// 25.1% Alleinlebende
	const float SHARED = 100.0f;	//  1.5% Wohngemeinschaften

	// Rentner
	const float PENSIONERSINGLE = 59.4f;	// 59.4% Alleinlebende Rentner
	const float PENSIONERCOUPLE = 100.0f;	// 40.6% Zusammenlebende Rentner

	// Familien
	const float PARENTSINGLE = 13.9f;	// 13.9% Alleinerziehende
	const float PARENTCOUPLE = 100.0f;	// 86.1% Paare

	// Alleinlebende
	const float SINGLEWORKER = 73.8f;		// 73.8% Alleinlebende Arbeitssuchende
	const float SINGLEUNEMPLOYED = 98.f;	// 24.2% Alleinlebende dauerhaft Arbeitslose
	const float SINGLESTUDENT = 100.f;		//  2.0% Alleinlebende Studenten

	// Wohngemeinschaften
	const float SHAREDTWO = 50.0f;		// 50.0% 2er-WG
	const float SHAREDTHREE = 85.0f;	// 35.0% 3er-WG
	const float SHAREDFOUR = 95.0f;		// 10.0% 4er-WG
	const float SHAREDFIVE = 100.0f;	//  5.0% 5er-WG

	// Alleinerziehende -> Arbeitssituation
	const float SINGLEPARENTWORKER = 57.5f;		// 57.5% Alleinerziehende Arbeitssuchende
	const float SINGLEPARENTUNEMPLOYED = 100.f;	// 42.5% Alleinerziehende dauerhaft Arbeitslose

	// Alleinerziehende -> Kinder
	const float SINGLEONEKID = 69.1f;		// 69.1% Alleinerziehende mit 1 Kind
	const float SINGLETWOKIDS = 93.4f;		// 24.3% Alleinerziehende mit 2 Kindern
	const float SINGLETHREEKIDS = 100.f;	//  6.6% Alleinerziehende mit 3 Kindern

	// Alleinerziehende -> Kindesalter
	const float SINGLEINFANT = 17.2f;		// 17.2% Kleinkinder bei Alleinerziehenden
	const float SINGLEKID = 47.2f;			// 30.0% Kinder bei Alleinerziehenden
	const float SINGLETEEN = 59.1f;			// 11.9% Jugendliche bei Alleinerziehenden
	const float SINGLEWITHSTUDENT = 77.1f;	// 18.0% Studenten bei Alleinerziehenden
	const float SINGLEWITHWORKER = 100.f;	// 22.9% Arbeitssuchende Kinder bei Alleinerziehenden

	// Paare -> Arbeitssituation
	const float COUPLEONLYWORKER = 56.f;		// 56.0% arbeitssuchende Paare
	const float COUPLEONLYUNEMPLOYED = 60.f;	//  4.0% dauerhaft arbeitslose Paare
	const float COUPLEWORKERUNEMPLOYED = 100.f;	// 40.0% Paar mit arbeitssuchend/arbeitslos

	// Paare -> Kinder
	const float COUPLEZEROKIDS = 45.6f;		// 45.6% Paare ohne Kinder
	const float COUPLEONEKID = 71.5f;		// 25.9% Paare mit 1 Kind
	const float COUPLETWOKIDS = 92.9f;		// 21.4% Paare mit 2 Kindern
	const float COUPLETHREEKIDS = 100.f;	//  7.1% Paare mit 3 Kindern

	// Paare -> Kindesalter
	const float COUPLEINFANT = 30.1f;		// 30.1% Kleinkinder bei Paaren
	const float COUPLEKID = 61.7f;			// 31.6% Kinder bei Paaren
	const float COUPLETEEN = 72.0f;			// 10.3% Jugendliche bei Paaren
	const float COUPLESTUDENT = 84.0f;		// 12.0% Studenten bei Paaren
	const float COUPLEWITHWORKER = 100.f;	// 16.0% Arbeitssuchende Kinder bei Paaren

	/*
	* simpel:
	*/

	const float A_RENTNER = 51.f;
		const float A1_EINRENTNER = 50.f; // {0,0,0,0,0,0,1}
		const float A2_ZWEIRENTNER = 50.f; // {0,0,0,0,0,0,2}
	const float B_FAMILIEN = 58.f;
		const float B1_EINELTERNTEIL = 25.f;
			const float B1_ALLEINERZIEHENDARBEITSSUCHEND = 60.f;
			const float B1_ALLEINERZIEHENDARBEITSLOS = 40.f;

			const float B1_KLEINKIND = 35.f;
			const float B1_KIND = 60.f;
			const float B1_JUGENDLICHER = 25.f;
			const float B1_STUDENT = 35.f;
			const float B1_ARBEITSSUCHENDESKIND = 45.f;

			const float B1_EINKIND = 120.f;
			const float B1_ZWEIKINDER = 70.f;
			const float B1_DREIKINDER = 35.f;

		const float B2_ZWEIELTERNTEILE = 75.f;
			const float B2_ELTERNARBEITSSUCHEND = 65.f;
			const float B2_ELTERNARBEITSLOS = 4.f;
			const float B2_ELTERNMIX = 25.f;

			const float B2_KLEINKIND = 60.f;
			const float B2_KIND = 65.f;
			const float B2_JUGENDLICHER = 20.f;
			const float B2_STUDENT = 25.f;
			const float B2_ARBEITSSUCHENDESKIND = 30.f;

			const float B2_EINKIND = 50.f;
			const float B2_ZWEIKINDER = 60.f;
			const float B2_DREIKINDER = 30.f;

	const float C_PAARE = 37.f;
		const float C1_ZWEIARBEITSSUCHEND = 65.f;
		const float C2_ZWEIARBEITSLOS = 5.f;
		const float C3_ZWEIMIX = 20.f;
	const float D_ALLEINLEBENDE = 50.f;
		const float D1_ALLEINSTUDENT = 5.f;
		const float D2_ALLEINARBEITSSUCHEND = 60.f;
		const float D3_ALLEINARBEITSLOS = 10.f;
	const float E_WGS = 3.f;
		const float E1_ZWEIERWG = 50.f;
		const float E2_DREIERWG = 35.f;
		const float E3_VIERERWG = 10.f;
		const float E4_FUNFERWG = 5.f;
	
}

#endif