#ifndef _GBUFFERPASS_
#define _GBUFFERPASS_

#include "pass.hpp"

namespace gl {
	class FBO;
};

class GBufferPass : public Pass {

	public:

		GBufferPass();

		void draw(const Camera &, const gl::FBO &);

};

#endif // _GBUFFERPASS_
