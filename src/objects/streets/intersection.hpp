#pragma once

#include <vector>
#include "../../network/path.hpp"

class Intersection {
	protected:
		std::vector<std::shared_ptr<Path>> m_paths;
};
