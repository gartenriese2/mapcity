#include <stdlib.h>

#include "mapcity/game.hpp"

int main() {

	Game game;
	game.initGraphics();

	while(1) {

		if (game.graphicsShouldClose()) {
			
			game.terminateGraphics();

			break;

		}

	}

	return EXIT_SUCCESS;

}