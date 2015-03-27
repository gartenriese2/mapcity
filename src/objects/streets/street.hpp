#pragma once

#include "../../rendering/drawable.hpp"
#include "../../network/path.hpp"

#include <glm/glm.hpp>
#include <memory>
#include <vector>

class Street {
	public:
		Street() = default;
		void addPaths(const std::vector<std::shared_ptr<Path>> &);
		std::vector<std::shared_ptr<Path>> & getPaths();
	protected:
		std::vector<std::shared_ptr<Path>> m_paths;
};

class StraightStreet : public Street, public Drawable {
	public:
		StraightStreet(const glm::vec3 &, const glm::vec3 &);
		virtual std::string getType() const = 0;
		virtual glm::vec3 getColor() const = 0;
		virtual RenderTypeName getRenderType() const override { return RenderTypeName::QUAD; }
		virtual bool isDynamic() const override { return false; }
	protected:
		void initModelMatrix(float);
	private:
		glm::vec3 m_start, m_end;
};

class StraightSmallStreet : public StraightStreet {
	public:
		StraightSmallStreet(const glm::vec3 &, const glm::vec3 &);
		virtual std::string getType() const override { return "StraightSmallStreet"; }
		virtual glm::vec3 getColor() const override { return {1.f, 1.f, 0.f}; }
	private:
		const float k_width = 6.f;
};

class StraightMediumStreet : public StraightStreet {
	public:
		StraightMediumStreet(const glm::vec3 &, const glm::vec3 &);
		virtual std::string getType() const override { return "StraightMediumStreet"; }
		virtual glm::vec3 getColor() const override { return {1.f, 0.f, 0.f}; }
	private:
		const float k_width = 10.f;
};
