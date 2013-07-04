#include "Terrain.hpp"

Terrain::Terrain(const Bitmap & b) {
	map = b;
	createVerticesFromBitmap();
}

void Terrain::createVerticesFromBitmap() {

	for (int z = 0; z < map.getHeight() - 1; z++) {
		
		for (int x = 0; x < map.getWidth() - 1; x++) {
			
			float h00 = map.getData()[3 * (z * map.getWidth() + x)];
			float h01 = map.getData()[3 * (z * (map.getWidth() + 1) + x)];
			float h10 = map.getData()[3 * (z * map.getWidth() + x + 1)];
			float h11 = map.getData()[3 * (z * (map.getWidth() + 1) + x + 1)];

			m_terrainVertices.push_back(x);
			m_terrainVertices.push_back(h00);
			m_terrainVertices.push_back(z);

			m_terrainVertices.push_back(x);
			m_terrainVertices.push_back(h01);
			m_terrainVertices.push_back(z + 1);

			m_terrainVertices.push_back(x + 1);
			m_terrainVertices.push_back(h10);
			m_terrainVertices.push_back(z);

			m_terrainVertices.push_back(x + 1);
			m_terrainVertices.push_back(h10);
			m_terrainVertices.push_back(z);

			m_terrainVertices.push_back(x);
			m_terrainVertices.push_back(h01);
			m_terrainVertices.push_back(z + 1);

			m_terrainVertices.push_back(x + 1);
			m_terrainVertices.push_back(h11);
			m_terrainVertices.push_back(z + 1);

		}
		
	}

}

void Terrain::createNormalsFromBitmap() {

	for (int z = 0; z < map.getHeight() - 1; z++) {
		
		for (int x = 0; x < map.getWidth() - 1; x++) {
			
			

		}
		
	}

}