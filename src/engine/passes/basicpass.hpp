#ifndef _BASICPASS_
#define _BASICPASS_

#include "pass.hpp"

class BasicPass : public Pass {

 	public:

 		BasicPass();

 		void draw(const Camera &);

};

#endif // _BASICPASS_