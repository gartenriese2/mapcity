#include "Bundesstrasse.hpp"

Bundesstrasse::Bundesstrasse(std::vector<glm::vec3> waypoints) {

	setWaypoints(waypoints);
	setWidth(k_width);
	setColor(k_color);
	
	createObject();

}

Bundesstrasse::~Bundesstrasse() {
	
}