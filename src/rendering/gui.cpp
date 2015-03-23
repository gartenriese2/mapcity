#include "gui.hpp"

#include <MonoEngine/extern/imgui.h>

/**************************************************************************************************/

Gui::Gui(std::unique_ptr<engine::Gui> & guiPtr)
  : m_engineGuiPtr{guiPtr}
{

}

/**************************************************************************************************/

void Gui::render() {
	m_engineGuiPtr->newFrame();
	ImGui::Begin("Main Menu");
	ImGui::Text("wPos: (%.2f|%.2f|%.2f)", m_wPos.x, m_wPos.y, m_wPos.z);
	ImGui::End();
}

/**************************************************************************************************/

void Gui::setWorldPosition(const glm::vec3 & pos) {
	m_wPos = pos;
}

/**************************************************************************************************/
