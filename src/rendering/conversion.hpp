#pragma once

constexpr auto k_graphicsScale = 0.001f;

template<typename T>
T gameToGraphics(T scale) {
	return scale * k_graphicsScale;
}

template<typename T>
T graphicsToGame(T scale) {
	return scale / k_graphicsScale;
}
