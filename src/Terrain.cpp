#include "Terrain.hpp"

Terrain::Terrain() {

}

void Terrain::createVerticesFromBitmap(Bitmap b) {

	std::vector<std::vector<float> > vertexVector;
	for (int z = 0; z < b.getHeight() - 1; z++) {
		std::vector<float> rowVector;
		for (int x = 0; x < b.getWidth() - 1; x++) {
			float h00 = b.getData()[z * b.getWidth() + x];
		}
	}

}