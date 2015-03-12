#pragma once

#include <MonoEngine/engine.hpp>
#include <MonoEngine/core/camera.hpp>
#include <MonoEngine/gl/program.hpp>
#include <MonoEngine/gl/buffer.hpp>
#include <MonoEngine/gl/vertexarray.hpp>
#include <MonoEngine/gl/timer.hpp>
#include <MonoEngine/object.hpp>
#include <MonoEngine/gl/framebuffer.hpp>

#include <deque>
#include <vector>

class Demo {

	public:

		Demo(const glm::uvec2 &);

		bool render();

	private:

		void init(const glm::uvec2 &);
		void orderModels();
		void setModelMatrices();
		double getAverageMs(const std::deque<GLuint64> &);
		double getAverageMs(const std::deque<double> &);

		engine::Engine m_engine;
		core::Camera m_cam;

		gl::Program m_prog;

		gl::Framebuffer m_fbo;
		gl::Texture m_colorTex;
		gl::Texture m_depthTex;

		gl::Buffer m_vbo;
		gl::Buffer m_ibo;
		gl::Buffer m_modelMatrixBuffer;
		std::vector<engine::Object> m_objects;

		gl::VertexArray m_vao;

		gl::Timer m_timer;
		std::deque<GLuint64> m_timeDeque;
		std::deque<double> m_cpuTimeDeque;

		unsigned int m_numObjects;

};
