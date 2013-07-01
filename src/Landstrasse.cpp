#include "Landstrasse.hpp"

Landstrasse::Landstrasse(std::vector<glm::vec3> waypoints) {

	setWaypoints(waypoints);
	setWidth(k_width);
	setColor(k_color);
	
	createObject();

}

Landstrasse::~Landstrasse() {
	
}