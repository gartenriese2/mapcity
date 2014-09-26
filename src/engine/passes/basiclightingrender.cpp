#include "basiclightingrender.hpp"

void BasicLightingRender::draw() {

	m_basicLightingPass.draw(m_cam, m_lights);

}
