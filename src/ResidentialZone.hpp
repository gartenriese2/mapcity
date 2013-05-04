#ifndef RESIDENTIALZONE_HPP
#define RESIDENTIALZONE_HPP

#include "Zone.hpp"

class ResidentialZone : public Zone {
	public:
		ResidentialZone();
		~ResidentialZone();
		inline int getResidents() { return this->residents; };
		int getChildren();

		
	private:
		int residents;
		
};

#endif