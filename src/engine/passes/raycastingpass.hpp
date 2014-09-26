#ifndef _RAYCASTINGPASS_
#define _RAYCASTINGPASS_

#include "pass.hpp"
#include "../gl/shaderstoragebuffer.hpp"

namespace gl {
	class FBO;
};

class RaycastingPass : public Pass {

	public:

		RaycastingPass();

		void draw(const Camera &, const gl::FBO &, const std::vector<std::shared_ptr<Light>>);

	private:

		ShaderStorageBuffer m_lightBuffer;

};

#endif // _RAYCASTINGPASS_
