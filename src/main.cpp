#include "objects/streets/street.hpp"
#include "objects/terrain/terrain.hpp"
#include "objects/buildings/building.hpp"
#include "objects/vehicles/vehicle.hpp"

#include "objects/objectmanager.hpp"
#include "rendering/rendering.hpp"
#include "simulation/simulation.hpp"

#include <memory>
#include <cstdlib>

int main() {

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
			glm::vec3(-30.f, 50.f, 0.f), 20.f);
	objManager.add<ResidentialBuilding>(glm::vec3(10.f, 10.f, 0.f), glm::vec3(40.f, 10.f, 0.f),
			glm::vec3(10.f, 50.f, 0.f), 30.f);
	objManager.add<OfficeBuilding>(glm::vec3(50.f, 10.f, 0.f), glm::vec3(90.f, 10.f, 0.f),
			glm::vec3(50.f, 50.f, 0.f), 25.f);

	// car
	objManager.add<UDriveItVehicle>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f),
			renderer.getInputPtr(), "ford tourneo custom", "french racing blue");

	/*
	 *	Rendering
	 */

	while (renderer.render()) {
		simulation.update();
	}

	return EXIT_SUCCESS;

}
