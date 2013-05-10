#include "Terrain.hpp"

Terrain::Terrain(Bitmap b) {
	map = b;
	createVerticesFromBitmap();
}

void Terrain::createVerticesFromBitmap() {

	int size = (map.getHeight() - 1) * (map.getWidth() - 1) * 18;
	terrainVertices = new float[size];

	int counter = 0;

	for (int z = 0; z < map.getHeight() - 1; z++) {
		
		for (int x = 0; x < map.getWidth() - 1; x++) {
			
			float h00 = map.getData()[3 * (z * map.getWidth() + x)];
			float h01 = map.getData()[3 * (z * (map.getWidth() + 1) + x)];
			float h10 = map.getData()[3 * (z * map.getWidth() + x + 1)];
			float h11 = map.getData()[3 * (z * (map.getWidth() + 1) + x + 1)];

			terrainVertices[counter++] = x;
			terrainVertices[counter++] = h00;
			terrainVertices[counter++] = z;

			terrainVertices[counter++] = x;
			terrainVertices[counter++] = h01;
			terrainVertices[counter++] = z + 1;

			terrainVertices[counter++] = x + 1;
			terrainVertices[counter++] = h10;
			terrainVertices[counter++] = z;

			terrainVertices[counter++] = x + 1;
			terrainVertices[counter++] = h10;
			terrainVertices[counter++] = z;

			terrainVertices[counter++] = x;
			terrainVertices[counter++] = h01;
			terrainVertices[counter++] = z + 1;

			terrainVertices[counter++] = x + 1;
			terrainVertices[counter++] = h11;
			terrainVertices[counter++] = z + 1;

		}
		
	}

}

void Terrain::createNormalsFromBitmap() {

	int size = (map.getHeight() - 1) * (map.getWidth() - 1) * 18;
	terrainNormals = new float[size];

	int counter = 0;

	for (int z = 0; z < map.getHeight() - 1; z++) {
		
		for (int x = 0; x < map.getWidth() - 1; x++) {
			
			

		}
		
	}

}