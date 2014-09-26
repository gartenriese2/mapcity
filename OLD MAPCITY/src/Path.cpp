#include "Path.hpp"

Path::Path() {

}

Path::~Path() {
	m_pts.clear();
}

void Path::createObject() {
	m_ID = ObjectContainer::instance().addPath(m_pts, m_width, m_color);
}