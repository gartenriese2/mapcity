#include <cstdlib>

void demo();
void rendering();

#include "demo.hpp"
void demo() {
	Demo demo({1920, 1080});
	while (demo.render()) {

	}
}

#include "objects/streets/street.hpp"
#include "objects/terrain/terrain.hpp"
#include "objects/buildings/building.hpp"
#include "objects/vehicles/vehicle.hpp"

#include "objects/objectmanager.hpp"
#include "rendering/rendering.hpp"
#include "simulation/simulation.hpp"

#include <memory>

void rendering() {

	/*
	 *	Initialization
	 */

	Rendering renderer({1920, 1080});
	Simulation simulation;

	/*
	 *	Objects
	 */

	ObjectManager objManager(renderer.getDrawableManager(), simulation.getUpdatableManager());

	// terrain
	objManager.add<Terrain>(glm::vec3(-500,-500,0.f), glm::vec3(500,500,0.f));

	// streets
	objManager.add<StraightMediumStreet>(glm::vec3(-300, 0, 0.02f), glm::vec3(100, 0, 0.02f));
	objManager.add<StraightSmallStreet>(glm::vec3(-200, 100, 0.01f), glm::vec3(100, 100, 0.01f));
	objManager.add<StraightMediumStreet>(glm::vec3(100, -200, 0.02f), glm::vec3(100, 200, 0.02f));
	objManager.add<StraightSmallStreet>(glm::vec3(-100, -100, 0.01f), glm::vec3(-100, 100, 0.01f));
	objManager.add<StraightSmallStreet>(glm::vec3(100, 50, 0.01f), glm::vec3(200, 50, 0.01f));
	objManager.add<StraightSmallStreet>(glm::vec3(-200, 0, 0.01f), glm::vec3(-300, -100, 0.01f));
	objManager.add<StraightSmallStreet>(glm::vec3(175, -75, 0.01f), glm::vec3(-100, -75, 0.01f));
	objManager.add<StraightSmallStreet>(glm::vec3(175, -150, 0.01f), glm::vec3(175, 50, 0.01f));

	// buildings
	objManager.add<ResidentialBuilding>(glm::vec3(-30.f, 10.f, 0.f), glm::vec3(0.f, 10.f, 0.f),
			glm::vec3(-30.f, 50.f, 0.f), 100.f);
	objManager.add<ResidentialBuilding>(glm::vec3(10.f, 10.f, 0.f), glm::vec3(40.f, 10.f, 0.f),
			glm::vec3(10.f, 50.f, 0.f), 120.f);
	objManager.add<OfficeBuilding>(glm::vec3(50.f, 10.f, 0.f), glm::vec3(90.f, 10.f, 0.f),
			glm::vec3(50.f, 50.f, 0.f), 150.f);

	// car
	auto car = objManager.add<Vehicle>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f));

	renderer.getInputPtr()->addKeyFunc([&](const int key, const int, const int action, const int){
		if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
			car->setAcceleration(30.f);
		}
		if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
			car->setAcceleration(0.f);
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
			car->setAcceleration(-45.f);
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
			car->setAcceleration(0.f);
		}
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
			car->setTurnSpeed(5.f);
		}
		if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
			car->setTurnSpeed(0.f);
		}
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
			car->setTurnSpeed(-5.f);
		}
		if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
			car->setTurnSpeed(0.f);
		}
	});

	/*
	 *	Rendering
	 */

	while (renderer.render()) {
		simulation.update();
	}

}

int main() {

	rendering();
	// demo();

	return EXIT_SUCCESS;

}
