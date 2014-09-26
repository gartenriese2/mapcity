#ifndef _NORMALPASS_
#define _NORMALPASS_

#include "pass.hpp"

class NormalPass : public Pass {

 	public:

 		NormalPass();

 		void draw(const Camera &);

 	private:

};

#endif // _NORMALPASS_