#pragma once

#include "../../rendering/drawable.hpp"
#include "../../simulation/updatable.hpp"

class Vehicle : public Drawable, public Updatable {

	public:
		Vehicle(const glm::vec3 &, const glm::vec3 &);
		virtual std::string getType() const override { return "Vehicle"; }
		virtual glm::vec3 getColor() const override { return {0.3f, 0.3f, 0.3f}; }
		virtual RenderTypeName getRenderType() const override { return RenderTypeName::CUBE; }
		virtual bool isDynamic() const override { return true; }

		virtual void update(float) override;

		void setTurnSpeed(float);
		void setAcceleration(float);
	protected:
		void initModelMatrix();
	private:
		glm::vec3 m_pos, m_dir;
		float m_speed, m_turnSpeed, m_acceleration;
};
