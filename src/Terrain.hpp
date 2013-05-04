#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Bitmap.hpp"
#include <vector>
#include <iostream>

class Terrain {
	public:
		Terrain(Bitmap b);
		
		inline const float * getVertices() { return terrainVertices; }
	private:
		float * terrainVertices;

		void createVerticesFromBitmap(Bitmap b);
};

#endif