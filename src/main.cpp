#include <cstdlib>
#include <memory>

#include "demo.hpp"
void demo() {
	Demo demo({1920, 1080});
	while (demo.render()) {

	}
}

#include "streets/street.hpp"
#include "rendering/manager.hpp"
void rendering() {

	const glm::uvec2 size({1920, 1080});
	engine::Engine engine(size, "Render", true);
	engine.showFPS(true);
	engine.getInputPtr()->addKeyFunc([&](const int key, const int, const int action, const int){
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(engine.getWindowPtr()->getGLFWWindow(), GL_TRUE);
		}
	});

	core::Camera cam;
	cam.setRatio(static_cast<float>(size.x) / static_cast<float>(size.y));
	cam.setFov(glm::radians(45.f));
	cam.translate({0.f, 0.f, 500.f});
	Manager manager(cam);


	std::vector<std::shared_ptr<Drawable>> streets;
	auto addStreet = [&streets](const glm::vec3 & a, const glm::vec3 & b){
		streets.emplace_back(std::make_shared<StraightSmallStreet>(a, b));
	};
	addStreet({-300, 0, 0}, {100, 0, 0});
	addStreet({-200, 100, 0}, {100, 100, 0});
	addStreet({100, -50, 0}, {100, 200, 0});
	addStreet({-100, -100, 0}, {-100, 100, 0});
	addStreet({100, 50, 0}, {200, 50, 0});
	addStreet({-200, 0, 0}, {-300, -100, 0});
	for (const auto & str : streets) {
		manager.addStreet(str);
	}

	while (engine.render()) {
		manager.draw();
	}
}

int main() {

	rendering();
	// demo();

	return EXIT_SUCCESS;

}
