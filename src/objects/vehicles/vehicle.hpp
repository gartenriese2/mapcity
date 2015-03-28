#pragma once

#include "../../rendering/drawable.hpp"
#include "../../simulation/updatable.hpp"

class Vehicle : public Drawable, public Updatable {

	public:
		Vehicle(const glm::vec3 &, const glm::vec3 &, const std::string & = "",
				const std::string & = "");
		virtual glm::vec3 getColor() const override { return m_color; }
		virtual RenderTypeName getRenderType() const override { return RenderTypeName::CUBE; }
		virtual bool isDynamic() const override { return true; }
	protected:
		void initModelMatrix();
		void initColor(const std::string &);
		void initSize(const std::string &);
		float m_speed;
		glm::vec3 m_pos, m_dir, m_color, m_size;
};

class Car : public Vehicle {
	public:
		Car(const glm::vec3 &, const glm::vec3 &, const std::string & = "", const std::string & = "");
		virtual std::string getType() const override { return "Car"; }
		virtual void update(float) override;
};

#include <MonoEngine/core/input.hpp>
#include <memory>

class UDriveItVehicle : public Vehicle {
	public:
		UDriveItVehicle(const glm::vec3 &, const glm::vec3 &, const std::unique_ptr<core::Input> &,
				const std::string & = "", const std::string & = "");
		void setTurnSpeed(float);
		void setAcceleration(float);
		virtual std::string getType() const override { return "UDriveItVehicle"; }
		virtual void update(float) override;
	private:
		void initKeys(const std::unique_ptr<core::Input> &);
		float m_turnSpeed, m_acceleration;
};
