#include <cstdlib>
#include <memory>

void demo();
void rendering();

#include "demo.hpp"
void demo() {
	Demo demo({1920, 1080});
	while (demo.render()) {

	}
}

#include "streets/street.hpp"
#include "rendering/rendering.hpp"
#include "terrain/terrain.hpp"
#include "buildings/building.hpp"
void rendering() {

	/*
	 *	Initialization
	 */

	Rendering renderer({1920, 1080});
	auto & manager = renderer.getManager();

	/*
	 *	Objects
	 */

	// terrain
	std::shared_ptr<Drawable> terrain
			= std::make_shared<Terrain>(glm::vec3(-500,-500,0.f), glm::vec3(500,500,0.f));
	manager.add(terrain);

	// streets
	std::vector<std::shared_ptr<Drawable>> streets;
	auto addSmallStreet = [&streets](const glm::vec3 & a, const glm::vec3 & b){
		streets.emplace_back(std::make_shared<StraightSmallStreet>(a, b));
	};
	auto addMediumStreet = [&streets](const glm::vec3 & a, const glm::vec3 & b){
		streets.emplace_back(std::make_shared<StraightMediumStreet>(a, b));
	};
	addMediumStreet({-300, 0, 0.02f}, {100, 0, 0.02f});
	addSmallStreet({-200, 100, 0.01f}, {100, 100, 0.01f});
	addMediumStreet({100, -200, 0.02f}, {100, 200, 0.02f});
	addSmallStreet({-100, -100, 0.01f}, {-100, 100, 0.01f});
	addSmallStreet({100, 50, 0.01f}, {200, 50, 0.01f});
	addSmallStreet({-200, 0, 0.01f}, {-300, -100, 0.01f});
	addSmallStreet({175, -75, 0.01f}, {-100, -75, 0.01f});
	addSmallStreet({175, -150, 0.01f}, {175, 50, 0.01f});
	for (const auto & str : streets) {
		manager.add(str);
	}

	// buildings
	std::vector<std::shared_ptr<Drawable>> buildings;
	auto addOfficeBuilding = [&buildings](const glm::vec3 & a, const float width,
			const float depth, const float height){
		buildings.emplace_back(std::make_shared<OfficeBuilding>(a, a + glm::vec3{width, 0, 0},
				a + glm::vec3{0, depth, 0}, height));
	};
	auto addResidentialBuilding = [&buildings](const glm::vec3 & a, const float width,
			const float depth, const float height){
		buildings.emplace_back(std::make_shared<ResidentialBuilding>(a, a + glm::vec3{width, 0, 0},
				a + glm::vec3{0, depth, 0}, height));
	};
	addResidentialBuilding({-30.f, 10.f, 0.f}, 30.f, 40.f, 100.f);
	addResidentialBuilding({10.f, 10.f, 0.f}, 30.f, 40.f, 120.f);
	addOfficeBuilding({50.f, 10.f, 0.f}, 40.f, 40.f, 150.f);
	for (const auto & b : buildings) {
		manager.add(b);
	}

	/*
	 *	Rendering
	 */

	while (renderer.render());

}

int main() {

	rendering();
	// demo();

	return EXIT_SUCCESS;

}
