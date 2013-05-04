#include "Terrain.hpp"

Terrain::Terrain(Bitmap b) {
	createVerticesFromBitmap(b);
}

void Terrain::createVerticesFromBitmap(Bitmap b) {

	int size = (b.getHeight() - 1) * (b.getWidth() - 1) * 18;
	terrainVertices = new float[size];

	int counter = 0;

	for (int z = 0; z < b.getHeight() - 1; z++) {
		
		for (int x = 0; x < b.getWidth() - 1; x++) {
			
			float h00 = b.getData()[3 * (z * b.getWidth() + x)];
			float h01 = b.getData()[3 * (z * (b.getWidth() + 1) + x)];
			float h10 = b.getData()[3 * (z * b.getWidth() + x + 1)];
			float h11 = b.getData()[3 * (z * (b.getWidth() + 1) + x + 1)];

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