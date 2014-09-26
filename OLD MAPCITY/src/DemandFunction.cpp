#include "DemandFunction.hpp"

DemandFunction::DemandFunction() {
	demandVector.clear();
	nExp = 1.3f;
}

DemandFunction::~DemandFunction() {

}

void DemandFunction::addDemandFunctionStruct(const float x, const float y, const float height, const float positive, const float negative) {
	
	DemandFunctionStruct d;
	d.height = height;
	d.positive = positive;
	d.negative = negative;
	d.x = x;
	d.y = y;
	demandVector.push_back(d);

}

float DemandFunction::addDemandsTogether(const float x, const float y) const {

	float demand = 0;

	for (unsigned long i = 0; i < demandVector.size(); ++i) {
		
		demand += getZforFunction(demandVector[i], x, y);

	}

	// demandVector.clear();
	return demand;

}

float DemandFunction::getZforFunction(const DemandFunctionStruct & d, const float x, const float y) const {

	float pxy = static_cast<float>(pow(fabs(x-d.x),2.f)+pow(fabs(y-d.y),2.f));
	float nxy = static_cast<float>(pow(fabs(x-d.x),nExp)+pow(fabs(y-d.y),nExp));
	if (nxy == 0) nxy = 0.0001f;

	return getZforStruct(d, pxy, nxy);

}

float DemandFunction::getZforStruct(const DemandFunctionStruct & d, const float pxy, const float nxy) const {

	float neg,pos;

	if (d.negative == 0) neg = 0;
	else neg = 1 / (d.negative * nxy);
	pos = d.positive * pxy;
	
	if (d.height > 0) {
		// add demand

		if (neg > 2*d.height) neg = 2*d.height;
		if (pos+neg > d.height && neg < d.height) return 0;

		return d.height - pos - neg;

	} else {
		// sub demand

		if (pos > -d.height) return 0;

		return d.height + pos;

	}

}