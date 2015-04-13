#include "objects/streets/street.hpp"
#include "objects/streets/intersection.hpp"
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

		CarSpawner(ObjectManager & oMan, const std::shared_ptr<Path> & path, const float relPos)
		  : m_objManager{oMan},
			m_path{path},
			m_relPathPos{relPos}
		{
			LOG_ASSERT(relPos >= 0.f && relPos <= 1.f, "relPos not on Path");
		}

		virtual void update(const float t) {
			const auto dist = t * 50.f;
			auto it = m_cars.begin();
			while (it != m_cars.end()) {
				auto ptr = m_objManager.get(*it);
				auto carPtr = std::dynamic_pointer_cast<Car>(ptr);
				const auto relPos = m_path->advance(carPtr->getPosition(), dist);
				if (relPos < 0.f || relPos > 1.f) {
					m_objManager.remove(*it);
					it = m_cars.erase(it);
					spawn();
				} else {
					const auto newPos = m_path->getPosition(relPos);
					carPtr->setPosition({newPos.x, newPos.y, carPtr->getPosition().z});
					++it;
				}
			}
		}
		virtual std::string getType() const { return "CarSpawner"; }

		void spawn() {
			const auto pos = m_path->getPosition(m_relPathPos);
			const auto dir = m_path->getDirection(m_relPathPos);
			m_cars.emplace_back(m_objManager.add<Car>(glm::vec3(pos.x, pos.y, 0.f), dir));
		}

	private:

		ObjectManager & m_objManager;

		std::shared_ptr<Path> m_path;
		float m_relPathPos;

		std::vector<IDType> m_cars;
};

void demo0(ObjectManager &, const std::unique_ptr<core::Input> &);
void demo1(ObjectManager &, DrawableManager &);

void demo0(ObjectManager & objManager, const std::unique_ptr<core::Input> & inputPtr) {
	// streets
	auto spawnerFunc = [&](const IDType ID){
		auto strPtr = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID));
		const auto & config = strPtr->getConfig();
		auto count = 0u;
		for (const auto & path : strPtr->getPaths()) {
			if (config.getLanes()[count].allows(LANETYPE::CAR)) {
				auto spawnerID = objManager.add<CarSpawner>(objManager, path, 0.f);
				std::dynamic_pointer_cast<CarSpawner>(objManager.get(spawnerID))->spawn();
			}
			++count;
		}
	};
	spawnerFunc(objManager.add<StraightStreet>(glm::vec3(-300, 0, 0.02f), glm::vec3(100, 0, 0.02f), "MediumStreet"));
	spawnerFunc(objManager.add<StraightStreet>(glm::vec3(-200, 100, 0.01f), glm::vec3(100, 100, 0.01f), "SmallStreet"));
	spawnerFunc(objManager.add<StraightStreet>(glm::vec3(100, -200, 0.02f), glm::vec3(100, 200, 0.02f), "MediumStreet"));
	spawnerFunc(objManager.add<StraightStreet>(glm::vec3(-100, -100, 0.01f), glm::vec3(-100, 100, 0.01f), "SmallStreet"));
	spawnerFunc(objManager.add<StraightStreet>(glm::vec3(100, 50, 0.01f), glm::vec3(200, 50, 0.01f), "SmallStreet"));
	spawnerFunc(objManager.add<StraightStreet>(glm::vec3(-200, 0, 0.01f), glm::vec3(-300, -100, 0.01f), "SmallStreet"));
	spawnerFunc(objManager.add<StraightStreet>(glm::vec3(175, -75, 0.01f), glm::vec3(-100, -75, 0.01f), "SmallStreet"));
	spawnerFunc(objManager.add<StraightStreet>(glm::vec3(175, -150, 0.01f), glm::vec3(175, 50, 0.01f), "SmallStreet"));

	// buildings
	objManager.add<ResidentialBuilding>(glm::vec3(-30.f, 10.f, 0.f), glm::vec3(0.f, 10.f, 0.f),
			glm::vec3(-30.f, 50.f, 0.f), 20.f);
	objManager.add<ResidentialBuilding>(glm::vec3(10.f, 10.f, 0.f), glm::vec3(40.f, 10.f, 0.f),
			glm::vec3(10.f, 50.f, 0.f), 30.f);
	objManager.add<OfficeBuilding>(glm::vec3(50.f, 10.f, 0.f), glm::vec3(90.f, 10.f, 0.f),
			glm::vec3(50.f, 50.f, 0.f), 25.f);

	// cars
	objManager.add<UDriveItCar>(glm::vec3(0.f, 0.f, 0.f), glm::vec3(1.f, 0.f, 0.f), inputPtr);
}

void demo1(ObjectManager & objManager, DrawableManager & drawableManager) {
	auto ID0 = objManager.add<StraightStreet>(glm::vec3(-50, -25, 0.01f), glm::vec3(0, -25, 0.01f), "SmallStreet");
	auto ptr0 = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID0));
	auto ID1 = objManager.add<StraightStreet>(glm::vec3(0, -25, 0.02f), glm::vec3(25, 0, 0.02f), "MediumStreet");
	auto ptr1 = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID1));
	objManager.add<Intersection>(std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>>{ptr0, ptr1});
	auto ID2 = objManager.add<StraightStreet>(glm::vec3(25, 0, 0.01f), glm::vec3(-25, 50, 0.01f), "SmallStreet");
	auto ptr2 = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID2));
	objManager.add<Intersection>(std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>>{ptr2, ptr1});
	auto ID3 = objManager.add<StraightStreet>(glm::vec3(-25, 50, 0.02f), glm::vec3(-25, 0, 0.02f), "MediumStreet");
	auto ptr3 = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID3));
	objManager.add<Intersection>(std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>>{ptr2, ptr3});
	auto ID4 = objManager.add<StraightStreet>(glm::vec3(-25, 0, 0.01f), glm::vec3(-75, 50, 0.01f), "SmallStreet");
	auto ptr4 = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID4));
	objManager.add<Intersection>(std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>>{ptr4, ptr3});
	auto ID5 = objManager.add<StraightStreet>(glm::vec3(-75, 50, 0.02f), glm::vec3(-50, 75, 0.02f), "MediumStreet");
	auto ptr5 = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID5));
	objManager.add<Intersection>(std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>>{ptr4, ptr5});
	auto ID6 = objManager.add<StraightStreet>(glm::vec3(-50, 75, 0.01f), glm::vec3(0, 75, 0.01f), "SmallStreet");
	auto ptr6 = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID6));
	objManager.add<Intersection>(std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>>{ptr6, ptr5});
	auto ID7 = objManager.add<StraightStreet>(glm::vec3(0, 75, 0.02f), glm::vec3(50, 75, 0.02f), "MediumStreet");
	auto ptr7 = std::dynamic_pointer_cast<StraightStreet>(objManager.get(ID7));
	objManager.add<Intersection>(std::pair<std::shared_ptr<Street>, std::shared_ptr<Street>>{ptr6, ptr7});
	drawableManager.updateBuffer("SmallStreet");
	drawableManager.updateBuffer("MediumStreet");
}


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

	// demo0(objManager, renderer.getInputPtr());
	demo1(objManager, renderer.getDrawableManager());

	/*
	 *	Rendering
	 */

	while (renderer.render()) {
		simulation.update();
	}

	return EXIT_SUCCESS;

}
