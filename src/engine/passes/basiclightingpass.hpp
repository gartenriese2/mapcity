#ifndef _BASICLIGHTINGPASS_
#define _BASICLIGHTINGPASS_

#include "pass.hpp"
#include "../gl/shaderstoragebuffer.hpp"

#include <vector>

class BasicLightingPass : public Pass {

 	public:

 		BasicLightingPass();

 		void draw(const Camera &, const std::vector<std::shared_ptr<Light>>);

 	private:

 		ShaderStorageBuffer m_lightBuffer;

};

#endif // _BASICLIGHTINGPASS_