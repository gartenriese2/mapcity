#include "DemandFunction.hpp"

DemandFunction::DemandFunction() {
	demandVector.clear();
	nExp = 1.3;
}

DemandFunction::~DemandFunction() {

}

void DemandFunction::addDemandFunctionStruct(float x, float y, float height, float positive, float negative) {
	
	DemandFunctionStruct d;
	d.height = height;
	d.positive = positive;
	d.negative = negative;
	d.x = x;
	d.y = y;
	demandVector.push_back(d);

}

float DemandFunction::addDemandsTogether(float x, float y) {

	float demand = 0;

	for (int i = 0; i < demandVector.size(); ++i) {
		
		demand += getZforFunction(demandVector[i], x, y);

	}

	// demandVector.clear();
	return demand;

}

float DemandFunction::getZforFunction(DemandFunctionStruct d, float x, float y) {

	float pxy = pow(fabs(x-d.x),2)+pow(fabs(y-d.y),2);
	float nxy = pow(fabs(x-d.x),nExp)+pow(fabs(y-d.y),nExp);
	if (nxy == 0) nxy = 0.0001;

	return getZforStruct(d, pxy, nxy);

}

float DemandFunction::getZforStruct(DemandFunctionStruct d, float pxy, float nxy) {

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