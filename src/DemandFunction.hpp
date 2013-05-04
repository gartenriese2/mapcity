#ifndef DEMANDFUNCTION_HPP
#define DEMANDFUNCTION_HPP

#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

struct DemandFunctionStruct {
	float x;
	float y;
	float positive;
	float negative;
	float height;
};

class DemandFunction {

	public:
		
		DemandFunction();
		~DemandFunction();
		float getZforFunction(int, float, float);
		float getZforFunction(DemandFunctionStruct, float, float);
		void addDemandFunctionStruct(float, float, float, float, float);
		float addDemandsTogether(float, float);
		float getZforStruct(DemandFunctionStruct, float, float);
		
	private:
		
		std::vector<DemandFunctionStruct> demandVector;
		float nExp;
		
	
};

#endif
