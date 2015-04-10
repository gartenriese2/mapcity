#pragma once

#include "../object.hpp"
#include "../../network/path.hpp"
#include "laneconfig.hpp"

#include <glm/glm.hpp>

class Street : public Object {
	public:
		Street(const std::string &, const glm::vec3 &, const glm::vec3 &);

		virtual std::string getType() const override;
		virtual bool isDrawable() const { return true; }

		std::vector<std::shared_ptr<Path>> & getPaths();
		const LaneConfig & getConfig() const;
		const glm::vec3 & getStart() const { return m_start; }
		glm::vec2 getStartXY() const { return glm::vec2(m_start.x, m_start.y); }
		const glm::vec3 & getEnd() const { return m_end; }
		glm::vec2 getEndXY() const { return glm::vec2(m_end.x, m_end.y); }
		const glm::vec3 & getStartTangent() const { return m_startTangent; }
		const glm::vec3 & getEndTangent() const { return m_endTangent; }

		virtual float getLength() const = 0;
		virtual void moveStart(float) = 0;
		virtual void moveEnd(float) = 0;
	protected:
		std::vector<std::shared_ptr<Path>> m_paths;
		LaneConfig m_config;
		std::string m_type;
		glm::vec3 m_start, m_end;
		glm::vec3 m_startTangent, m_endTangent;
};

class StraightStreet : public Street {
	public:
		StraightStreet(const glm::vec3 &, const glm::vec3 &, const std::string &);
		virtual float getLength() const override;
		virtual void moveStart(float) override;
		virtual void moveEnd(float) override;
	protected:
		void initPaths();
	private:
		void initDrawables();
};
