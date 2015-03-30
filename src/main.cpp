#include "objects/streets/street.hpp"
#include "objects/terrain/terrain.hpp"
#include "objects/buildings/building.hpp"
#include "objects/vehicles/car.hpp"

#include "objects/objectmanager.hpp"
#include "rendering/rendering.hpp"
#include "simulation/simulation.hpp"

#include <memory>
#include <cstdlib>

class CarSpawner : public Updatable {

	public:

		CarSpawner(ObjectManager & oMan, const IDType path, const float relPos)
		  : m_objManager{oMan},
			m_path{path},
			m_relPathPos{relPos}
		{
			LOG_ASSERT(relPos >= 0.f && relPos <= 1.f, "relPos not on Path");
		}

		virtual void update(const float t) {
			auto path = std::dynamic_pointer_cast<Path>(m_objManager.get(m_path));
			if (!path) {
				LOG_WARNING("path is not a Path!");
				return;
			}
			const auto dist = t * 50.f;
			auto it = m_cars.begin();
			while (it != m_cars.end()) {
				auto ptr = m_objManager.get(*it);
				auto carPtr = std::dynamic_pointer_cast<Car>(ptr);
				const auto relPos = path->advance(carPtr->getPosition(), dist);
				if (relPos < 0.f || relPos > 1.f) {
					m_objManager.remove(*it);
					it = m_cars.erase(it);
					spawn();
				} else {
					const auto newPos = path->getPosition(relPos);
					carPtr->setPosition({newPos.x, newPos.y, carPtr->getPosition().z});
					++it;
				}
			}
		}
		virtual std::string getType() const { return "CarSpawner"; }

		void spawn() {
			auto ptr = m_objManager.get(m_path);
			auto path = std::dynamic_pointer_cast<Path>(ptr);
			if (!path) {
				LOG_WARNING("path is not a Path!");
				return;
			}
			const auto pos = path->getPosition(m_relPathPos);
			const auto dir = path->getDirection(m_relPathPos);
			m_cars.emplace_back(m_objManager.add<Car>(glm::vec3(pos.x, pos.y, 0.f), dir));
		}

	private:

		ObjectManager & m_objManager;

		IDType m_path;
		float m_relPathPos;

		std::vector<IDType> m_cars;
};

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
	auto spawnerFunc = [&](const IDType ID){
		auto strPtr = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID));
		for (const auto & path : strPtr->getPaths()) {
			auto spawnerID = objManager.add<CarSpawner>(objManager, path->ID(), 0.f);
			std::dynamic_pointer_cast<CarSpawner>(objManager.get(spawnerID))->spawn();
		}
	};
	spawnerFunc(objManager.add<StraightMediumStreet>(glm::vec3(-300, 0, 0.02f), glm::vec3(100, 0, 0.02f)));
	spawnerFunc(objManager.add<StraightSmallStreet>(glm::vec3(-200, 100, 0.01f), glm::vec3(100, 100, 0.01f)));
	spawnerFunc(objManager.add<StraightMediumStreet>(glm::vec3(100, -200, 0.02f), glm::vec3(100, 200, 0.02f)));
	spawnerFunc(objManager.add<StraightSmallStreet>(glm::vec3(-100, -100, 0.01f), glm::vec3(-100, 100, 0.01f)));
	spawnerFunc(objManager.add<StraightSmallStreet>(glm::vec3(100, 50, 0.01f), glm::vec3(200, 50, 0.01f)));
	spawnerFunc(objManager.add<StraightSmallStreet>(glm::vec3(-200, 0, 0.01f), glm::vec3(-300, -100, 0.01f)));
	spawnerFunc(objManager.add<StraightSmallStreet>(glm::vec3(175, -75, 0.01f), glm::vec3(-100, -75, 0.01f)));
	spawnerFunc(objManager.add<StraightSmallStreet>(glm::vec3(175, -150, 0.01f), glm::vec3(175, 50, 0.01f)));

	// buildings
	objManager.add<ResidentialBuilding>(glm::vec3(-30.f, 10.f, 0.f), glm::vec3(0.f, 10.f, 0.f),
			glm::vec3(-30.f, 50.f, 0.f), 20.f);
	objManager.add<ResidentialBuilding>(glm::vec3(10.f, 10.f, 0.f), glm::vec3(40.f, 10.f, 0.f),
			glm::vec3(10.f, 50.f, 0.f), 30.f);
	objManager.add<OfficeBuilding>(glm::vec3(50.f, 10.f, 0.f), glm::vec3(90.f, 10.f, 0.f),
			glm::vec3(50.f, 50.f, 0.f), 25.f);

	// cars
	objManager.add<UDriveItCar>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f),
			renderer.getInputPtr());
	objManager.add<Car>(glm::vec3(10.f, 5.f, 0.f), glm::vec3(-1.f, 0.f, 0.f));
	objManager.add<Car>(glm::vec3(16.f, 5.f, 0.f), glm::vec3(-1.f, 0.f, 0.f));
	objManager.add<Car>(glm::vec3(23.f, 5.f, 0.f), glm::vec3(-1.f, 0.f, 0.f));
	objManager.add<Car>(glm::vec3(29.f, 5.f, 0.f), glm::vec3(-1.f, 0.f, 0.f));
	objManager.add<Car>(glm::vec3(34.f, 5.f, 0.f), glm::vec3(-1.f, 0.f, 0.f));

	/*
	 *	Rendering
	 */

	while (renderer.render()) {
		simulation.update();
	}

	return EXIT_SUCCESS;

}
