#include <cstdlib>
#include <memory>

#include "demo.hpp"
void demo() {
	Demo demo({1920, 1080});
	while (demo.render()) {

	}
}

#include "streets/street.hpp"
#include "rendering/rendering.hpp"
void rendering() {

	Rendering renderer({1920, 1080});
	auto & manager = renderer.getManager();

	// add streets
	std::vector<std::shared_ptr<Drawable>> streets;
	auto addSmallStreet = [&streets](const glm::vec3 & a, const glm::vec3 & b){
		streets.emplace_back(std::make_shared<StraightSmallStreet>(a, b));
	};
	auto addMediumStreet = [&streets](const glm::vec3 & a, const glm::vec3 & b){
		streets.emplace_back(std::make_shared<StraightMediumStreet>(a, b));
	};
	addMediumStreet({-300, 0, 0}, {100, 0, 0});
	addSmallStreet({-200, 100, 0}, {100, 100, 0});
	addMediumStreet({100, -200, 0}, {100, 200, 0});
	addSmallStreet({-100, -100, 0}, {-100, 100, 0});
	addSmallStreet({100, 50, 0}, {200, 50, 0});
	addSmallStreet({-200, 0, 0}, {-300, -100, 0});
	addSmallStreet({175, -75, 0}, {-100, -75, 0});
	addSmallStreet({175, -150, 0}, {175, 50, 0});
	for (const auto & str : streets) {
		manager.addStreet(str);
	}

	while (renderer.render());

}

int main() {

	rendering();
	// demo();

	return EXIT_SUCCESS;

}
