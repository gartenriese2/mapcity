#ifndef _RAYCOMPUTINGPASS_
#define _RAYCOMPUTINGPASS_

#include "pass.hpp"
#include "../gl/shaderstoragebuffer.hpp"

#include "../gl/texture.hpp"

class RaycomputingPass : public Pass {

	public:

		RaycomputingPass(gl::Texture &, gl::Texture &, gl::Texture &, gl::Texture &);

		void draw(const Camera &, const std::vector<std::shared_ptr<Light>>);

	private:

		gl::Texture & m_positionTex;
		gl::Texture & m_directionTex;
		gl::Texture & m_colorTex;
		gl::Texture & m_result;

		ShaderStorageBuffer m_triangleBuffer;
		ShaderStorageBuffer m_lightBuffer;

};

#endif // _RAYCOMPUTINGPASS_
