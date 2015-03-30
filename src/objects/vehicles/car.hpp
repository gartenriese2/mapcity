#pragma once

#include "vehicle.hpp"

class Car : public Vehicle {
	public:
		Car(const glm::vec3 &, const glm::vec3 &, const std::string & = "", const std::string & = "");
		virtual std::string getType() const override { return "Car"; }
		virtual bool isUnicolored() const override { return false; }
		virtual void update(float) override;
};

#include <MonoEngine/core/input.hpp>
#include <memory>

class UDriveItCar : public Vehicle {
	public:
		UDriveItCar(const glm::vec3 &, const glm::vec3 &, const std::unique_ptr<core::Input> &,
				const std::string & = "", const std::string & = "");
		void setTurnSpeed(float);
		void setAcceleration(float);
		virtual std::string getType() const override { return "UDriveItCar"; }
		virtual bool isUnicolored() const override { return false; }
		virtual void update(float) override;
	private:
		void initKeys(const std::unique_ptr<core::Input> &);
		float m_turnSpeed, m_acceleration;
};
