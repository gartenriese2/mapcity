#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Bitmap.hpp"
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

class Terrain {
	public:
		Terrain(Bitmap b);
		
		inline const float * getVertices() { return terrainVertices; }
		inline const float * getNormals() { return terrainNormals; }
	private:
		Bitmap map;
		float * terrainVertices;
		float * terrainNormals;

		void createVerticesFromBitmap();
		void createNormalsFromBitmap();
};

#endif