#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Bitmap.hpp"
#include <vector>
#include <iostream>
#include "glmincludes.hpp"

class Terrain {
	
	public:
		
		Terrain(const Bitmap & b);
		
		const std::vector<float> & getVertices() const { return m_terrainVertices; }
		const std::vector<float> & getNormals() const { return m_terrainNormals; }
	
	private:
		
		Bitmap map;
		std::vector<float> m_terrainVertices;
		std::vector<float> m_terrainNormals;

		void createVerticesFromBitmap();
		void createNormalsFromBitmap();

};

#endif