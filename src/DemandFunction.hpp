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
		
		float getZforFunction(const DemandFunctionStruct &, const float, const float) const;
		void addDemandFunctionStruct(const float, const float, const float, const float, const float);
		float addDemandsTogether(const float, const float) const;
		float getZforStruct(const DemandFunctionStruct &, const float, const float) const;
		
	private:
		
		std::vector<DemandFunctionStruct> demandVector;
		float nExp;
		
	
};

#endif
