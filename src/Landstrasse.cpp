#include "Landstrasse.hpp"

Landstrasse::Landstrasse(const vectorVec3 & waypoints) {

	setWaypoints(waypoints);
	setWidth(k_width);
	setColor(k_color);
	
	createObject();

}

Landstrasse::~Landstrasse() {
	
}