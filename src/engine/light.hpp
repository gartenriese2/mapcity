#ifndef _LIGHT_
#define _LIGHT_

#include "glmincludes.hpp"

struct LightData {
	
	glm::vec4 bools;
	glm::vec4 position;
	glm::vec4 color;
	glm::vec4 ambient;
	glm::vec4 direction;
	glm::vec4 attenuation;
	glm::vec4 spot;
};

class Light {

	public:

		Light(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);

		const LightData & getData() const { return m_lightData; }

		void enable() { m_lightData.bools[0] = 1.f; }
		void disable() { m_lightData.bools[0] = 0.f; }

		void setAsDirectionalLight() { m_lightData.bools[1] = 0.f; }
		void setAsLocalLight() { m_lightData.bools[1] = 1.f; }
		void setAsSpotLight() { m_lightData.bools[2] = 1.f; setAsLocalLight(); }

		const glm::vec3 getPosition() const { return glm::vec3(m_lightData.position); }
		void setPosition(const glm::vec3 & pos) { m_lightData.position = glm::vec4(pos, 1.f); }

		const glm::vec3 getColor() const { return glm::vec3(m_lightData.color); }
		void setColor(const glm::vec3 & color) { m_lightData.color = glm::vec4(color, 1.f); }

		const glm::vec3 getDirection() const { return glm::vec3(m_lightData.direction); }
		void setDirection(const glm::vec3 & dir) { m_lightData.direction = glm::vec4(dir, 1.f); }
		
		float getAmbientTerm() const { return m_lightData.ambient.x / m_lightData.color.x; }
		void setAmbientTerm(float f) { m_lightData.ambient = f * m_lightData.color; }

		const glm::vec3 getAttenuations() const { return glm::vec3(m_lightData.attenuation); }
		void setConstantAttenuation(float f) { m_lightData.attenuation[0] = f; }
		void setLinearAttenuation(float f) { m_lightData.attenuation[1] = f; }
		void setQuadraticAttenuation(float f) { m_lightData.attenuation[2] = f; }

		float getSpotCutoff() const { return m_lightData.spot[0]; }
		float getSpotExponent() const { return m_lightData.spot[1]; }
		void setSpotCutoff(float f) { m_lightData.spot[0] = f; }
		void setSpotExponent(float f) { m_lightData.spot[1] = f; }

		void rotate(float, const glm::vec3 &);

	private:

		struct LightData m_lightData;

};

#endif // _LIGHT_