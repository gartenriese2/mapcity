#pragma once

#include "../../rendering/drawable.hpp"
#include "../../network/path.hpp"
#include "laneconfig.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Street : public Drawable {
	public:
		Street(const std::string &);

		virtual std::string getType() const override;
		virtual glm::vec4 getColor() const override;
		virtual RenderTypeName getRenderType() const = 0;
		virtual bool isDynamic() const override;

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

		virtual RenderTypeName getRenderType() const override { return RenderTypeName::QUAD; }
	protected:
		void initModelMatrix();
		void initPaths();
	private:
		glm::vec3 m_start, m_end;
};
