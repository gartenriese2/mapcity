#ifndef _HANDLER_
#define _HANDLER_

#include "glmincludes.hpp"
#include "window.hpp"

#include <memory>
#include <initializer_list>
#include <vector>

struct Material {
	glm::vec3 emission;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

class WindowID;

class ObjectID {

	public:

		static std::shared_ptr<ObjectID> create(WindowID &);

		bool operator==(const ObjectID & other) const { return this->m_id == other.m_id; }
		bool operator<(const ObjectID & other) const { return this->m_id < other.m_id; }
		unsigned long operator()() const { return m_id; }
		
		void rotate(float, const glm::vec3 &);
		void rotateAround(float, const glm::vec3 &, const glm::vec3 &);
		void rotateAround(float, const glm::vec3 &, const ObjectID &);
		void move(float, const glm::vec3 &);
		void moveTo(const glm::vec3 &);
		void scale(const glm::vec3 &);
		void scaleColor(float);
		void setColor(const std::initializer_list<glm::vec3> & = {});
		void setColor(const glm::vec3 &);
		void attachTo(const ObjectID &);

		const glm::vec3 & getEmission() const { return m_material->emission; }
		const glm::vec3 & getAmbient() const { return m_material->ambient; }
		const glm::vec3 & getDiffuse() const { return m_material->diffuse; }
		const glm::vec3 & getSpecular() const { return m_material->specular; }
		float getShininess() const { return m_material->shininess; }

		void setEmission(const glm::vec3 & val) { m_material->emission = val; }
		void setAmbient(const glm::vec3 & val) { m_material->ambient = val; }
		void setDiffuse(const glm::vec3 & val) { m_material->diffuse = val; }
		void setSpecular(const glm::vec3 & val) { m_material->specular = val; }
		void setShininess(const float val) { m_material->shininess = val; }

		static const std::shared_ptr<ObjectID> getID(unsigned long);

	private:

		ObjectID(WindowID &);

		unsigned long m_id;
		WindowID & m_window;

		std::shared_ptr<Material> m_material;

		static std::vector<std::shared_ptr<ObjectID>> s_ids;

};

class CameraID;
class RenderID;
class LightID;

class WindowID {

	public:

		WindowID(std::shared_ptr<Window>);
		WindowID(const WindowID & other) { m_id = other.m_id; }
		WindowID(WindowID && other) { m_id = other.m_id; }
		WindowID & operator=(const WindowID &) = delete;
		WindowID & operator=(WindowID &&) = delete;
		~WindowID();

		bool operator==(const WindowID & other) const { return this->m_id == other.m_id; }
		bool operator<(const WindowID & other) const { return this->m_id < other.m_id; }
		unsigned long operator()() const { return m_id; }

		Loop & getLoop() { return m_window->getLoop(); }
		bool hasObject(const ObjectID &) const;

		void close() { glfwSetWindowShouldClose(m_window->getGLFWWindow(), GL_TRUE); }

		const ObjectID & createTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &);
		const ObjectID & createTriangle(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const std::initializer_list<glm::vec3> & = {});
		const ObjectID & createTriangleInstance();

		const ObjectID & createQuadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		const ObjectID & createQuadrilateral(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const std::initializer_list<glm::vec3> & = {});
		const ObjectID & createQuadrilateralInstance();

		const ObjectID & createCircle(const glm::vec3 &, const glm::vec3 &, float, unsigned int,
			const glm::vec3 &);
		const ObjectID & createCircle(const glm::vec3 &, const glm::vec3 &, float, unsigned int,
			const std::initializer_list<glm::vec3> & = {});
		const ObjectID & createCircleInstance();

		const ObjectID & createCuboid(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const glm::vec3 &);
		const ObjectID & createCuboid(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, const std::initializer_list<glm::vec3> & = {});
		const ObjectID & createCuboidInstance();

		const ObjectID & createCone(const glm::vec3 &, const glm::vec3 &, float, float, float,
			unsigned int, const glm::vec3 &);
		const ObjectID & createCone(const glm::vec3 &, const glm::vec3 &, float, float, float,
			unsigned int, const std::initializer_list<glm::vec3> & = {});
		const ObjectID & createConeInstance();

		const ObjectID & createSphere(const glm::vec3 &, float, unsigned int, unsigned int,
			const glm::vec3 &);
		const ObjectID & createSphere(const glm::vec3 &, float, unsigned int, unsigned int,
			const std::initializer_list<glm::vec3> & = {});
		const ObjectID & createSphereInstance();

		const ObjectID & createSpline(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &, const glm::vec3 &,
			const glm::vec3 &, float, float, unsigned int, float, const glm::vec3 &);
		const ObjectID & createSpline(const std::vector<glm::vec3> &, const glm::vec3 &, float, const glm::vec3 &);
		const ObjectID & createSplineInstance();

		const ObjectID & createCopy(const ObjectID &);

		const RenderID & createBasicRendering(CameraID &);
		const RenderID & createNormalRendering(CameraID &);
		const RenderID & createBasicLightingRendering(CameraID &, const std::vector<LightID>);
		const RenderID & createGBufferRendering(CameraID &);
		const RenderID & createRaytracingRendering(CameraID &, const std::vector<LightID>);

		const CameraID & createCamera(const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);

		const LightID & createLight(const glm::vec3 &, const glm::vec3 &, const glm::vec3 & = {1.f, 1.f, 1.f});

		void addKeyEvent(int key, std::function<void()> f) { getLoop().addKeyEvent(key, f); }
		void removeKeyEvent(int key) { getLoop().removeKeyEvent(key); }
		bool isKeyPressed(int key) { return GLFW_PRESS == glfwGetKey(m_window->getGLFWWindow(), key); }

		void addMouseClickEvent(int key, std::function<void()> f) { getLoop().addMouseClickEvent(key, f); }
		void removeMouseClickEvent(int key) { getLoop().removeMouseClickEvent(key); }
		void setMouseMoveEvent(std::function<void(double, double)> f) { getLoop().setMouseMoveEvent(f); }
		void setScrollEvent(std::function<void(double, double)> f) { getLoop().setScrollEvent(f); }
		bool isMouseButtonPressed(int key) { return GLFW_PRESS == glfwGetMouseButton(m_window->getGLFWWindow(), key); }
		
		bool isLeftMouseButtonPressed() { return isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT); }
		bool isRightMouseButtonPressed() { return isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT); }
		bool isEscapePressed() { return isKeyPressed(GLFW_KEY_ESCAPE); }
		bool isShiftPressed() { return isKeyPressed(GLFW_KEY_LEFT_SHIFT) || isKeyPressed(GLFW_KEY_RIGHT_SHIFT); }

	private:

		unsigned long m_id;
		std::shared_ptr<Window> m_window;
		std::vector<std::shared_ptr<ObjectID>> m_objects;
		std::vector<RenderID> m_renders;
		std::vector<CameraID> m_cameras;
		std::vector<LightID> m_lights;

};

class RenderID {

	public:

		RenderID(WindowID &);

		bool operator==(const RenderID & other) const { return this->m_id == other.m_id; }
		bool operator<(const RenderID & other) const { return this->m_id < other.m_id; }
		unsigned long operator()() const { return m_id; }

		void set();
		void addObjects(const std::set<ObjectID> &);
		void removeObject(const ObjectID &);

	private:

		unsigned long m_id;
		WindowID & m_window;

};

#include "camera.hpp"

class CameraID {

	public:

		CameraID(const Camera &);

		unsigned long operator()() const { return m_id; }

		Camera & getCam() { return m_cam; }

		const glm::vec3 & getPos() const { return m_cam.getPos(); }
		const glm::vec3 & getDir() const { return m_cam.getDir(); }
		const glm::vec3 & getUp() const { return m_cam.getUp(); }

		void reset() { m_cam.reset(); }
		void move(const glm::vec3 & change) { m_cam.move(change); }
		void moveTo(const glm::vec3 & to) { m_cam.moveTo(to); }
		void rotate(float radians, const glm::vec3 & axis) { m_cam.rotate(radians, axis); }
		void rotateAround(float radians, const glm::vec3 & axis, const glm::vec3 & point)
			{ m_cam.rotateAround(radians, axis, point); }
		void yaw(float radians) { m_cam.rotate(radians, getUp()); }
		void pitch(float radians) { m_cam.rotate(radians, glm::cross(getUp(), getDir())); }

	private:

		unsigned long m_id;
		Camera m_cam;

};

#include "light.hpp"

class LightID {

	public:

		LightID(const std::shared_ptr<Light>);

		unsigned long operator()() const { return m_id; }

		const std::shared_ptr<Light> getLight() const { return m_light; }

		void enable() { m_light->enable(); }
		void disable() { m_light->disable(); }

		void setAsDirectionalLight() { m_light->setAsDirectionalLight(); }
		void setAsLocalLight() { m_light->setAsLocalLight(); }
		void setAsSpotLight() { m_light->setAsSpotLight(); }

		const glm::vec3 getPosition() const { return m_light->getPosition(); }
		void moveTo(const glm::vec3 & to) { m_light->setPosition(to); }
		void move(const glm::vec3 & dis) { m_light->setPosition(m_light->getPosition() + dis); }

		const glm::vec3 getDirection() const { return m_light->getDirection(); }
		void setDirection(const glm::vec3 & dir) { m_light->setDirection(dir); }
		void rotate(float radians, const glm::vec3 & axis) { m_light->rotate(radians, axis); }

		const glm::vec3 getColor() const { return m_light->getColor(); }
		void setColor(const glm::vec3 & color) { m_light->setColor(color); }

		float getAmbientTerm() const { return m_light->getAmbientTerm(); }
		void setAmbientTerm(float f) { m_light->setAmbientTerm(f); }

		const glm::vec3 getAttenuations() const { return m_light->getAttenuations(); }
		void setConstantAttenuation(float f) { m_light->setConstantAttenuation(f); }
		void setLinearAttenuation(float f) { m_light->setLinearAttenuation(f); }
		void setQuadraticAttenuation(float f) { m_light->setQuadraticAttenuation(f); }

		float getSpotCutoff() const { return m_light->getSpotCutoff(); }
		float getSpotExponent() const { return m_light->getSpotExponent(); }
		void setSpotCutoff(float f) { m_light->setSpotCutoff(f); }
		void setSpotExponent(float f) { m_light->setSpotExponent(f); }

	private:

		unsigned long m_id;
		std::shared_ptr<Light> m_light;

};

#endif // _HANDLER_