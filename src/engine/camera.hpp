#ifndef _CAMERA_
#define _CAMERA_

#include "glmincludes.hpp"
#include "debug.hpp"

class Camera {

	public:

		Camera(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float, unsigned int, unsigned int, float);
		// Camera(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, float, float, float, float);
		Camera(const Camera &) = default;
		Camera(Camera &&) = default;
		Camera & operator=(Camera &&) = default;

		const glm::mat4 & getViewMat() const { return m_view; }
		const glm::mat4 & getProjMat() const { return m_proj; }

		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }

		const glm::vec3 & getPos() const { return m_pos; }
		const glm::vec3 & getDir() const { return m_dir; }
		const glm::vec3 & getUp() const { return m_up; }

		void resize(unsigned int, unsigned int);
		void calculateView();
		void calculateProj();

		void reset();
		void move(const glm::vec3 &);
		void moveTo(const glm::vec3 &);
		void rotate(float, const glm::vec3 &);
		void rotateAround(float, const glm::vec3 &, const glm::vec3 &);

	private:

		unsigned int m_width;
		unsigned int m_height;

		float m_fov;
		float m_near;

		glm::mat4 m_view;
		glm::mat4 m_proj;

		glm::vec3 m_pos;
		glm::vec3 m_dir;
		glm::vec3 m_up;

		glm::vec3 m_initPos;
		glm::vec3 m_initDir;
		glm::vec3 m_initUp;

};

#endif