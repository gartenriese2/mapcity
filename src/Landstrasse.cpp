#include "Landstrasse.hpp"

Landstrasse::Landstrasse(vectorVec3 waypoints) {

	setWaypoints(waypoints);
	setWidth(k_width);
	setColor(k_color);
	
	createObject();

}

Landstrasse::~Landstrasse() {
	
}