#include "Bundesstrasse.hpp"

Bundesstrasse::Bundesstrasse(const vectorVec3 & waypoints) {

	setWaypoints(waypoints);
	setWidth(k_width);
	setColor(k_color);
	
	createObject();

}

Bundesstrasse::~Bundesstrasse() {
	
}