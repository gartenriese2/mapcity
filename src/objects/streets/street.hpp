#pragma once

#include "../object.hpp"
#include "../../network/path.hpp"
#include "laneconfig.hpp"

#include <glm/glm.hpp>

class Street : public Object {
	public:
		Street(const std::string &);

		virtual std::string getType() const override;
		virtual bool isDrawable() const { return true; }

		std::vector<std::shared_ptr<Path>> & getPaths();
		const LaneConfig & getConfig() const;
	protected:
		std::vector<std::shared_ptr<Path>> m_paths;
		LaneConfig m_config;
		std::string m_type;
};

class StraightStreet : public Street {
	public:
		StraightStreet(const glm::vec3 &, const glm::vec3 &, const std::string &);
	protected:
		void initPaths();
	private:
		void initDrawables();
		glm::vec3 m_start, m_end;
};
