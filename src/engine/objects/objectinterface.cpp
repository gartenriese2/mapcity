#include "objectinterface.hpp"

#include "triangle.hpp"
#include "quadrilateral.hpp"
#include "circle.hpp"
#include "cuboid.hpp"
#include "sphere.hpp"
#include "cone.hpp"
#include "spline.hpp"
#include "../debug.hpp"

#include <algorithm>
#include <mutex>

static std::mutex s_mutex;

void ObjectInterface::checkID(unsigned long id) const {
	
	if (m_objects.count(id) == 0) {
		Debug::log("No Object with ID " + std::to_string(id));
		Debug::log("Only the following IDs are there:");
		for (auto & i : m_objects) {
			Debug::log(std::to_string(i.first));
		}
		exit(0);
	}

}

void ObjectInterface::addObject(unsigned long id, const std::shared_ptr<Object> ptr) {
	
	instance().m_objects.emplace(id, ptr);

}

void ObjectInterface::createTriangle(unsigned long id, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const glm::vec3 & col) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Triangle(a, b, c, col)));

}

void ObjectInterface::createTriangle(unsigned long id, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const std::initializer_list<glm::vec3> & colors) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Triangle(a, b, c, colors)));

}

void ObjectInterface::createQuadrilateral(unsigned long id, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const glm::vec3 & d, const glm::vec3 & col) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Quadrilateral(a, b, c, d, col)));

}

void ObjectInterface::createQuadrilateral(unsigned long id, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const glm::vec3 & d, const std::initializer_list<glm::vec3> & colors) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Quadrilateral(a, b, c, d, colors)));

}

void ObjectInterface::createCircle(unsigned long id, const glm::vec3 & center, const glm::vec3 & axis, float radius,
	unsigned int edges, const glm::vec3 & color) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Circle(center, axis, radius, edges, color)));

}

void ObjectInterface::createCircle(unsigned long id, const glm::vec3 & center, const glm::vec3 & axis, float radius,
	unsigned int edges,	const std::initializer_list<glm::vec3> & colors) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Circle(center, axis, radius, edges, colors)));

}

void ObjectInterface::createCuboid(unsigned long id, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const glm::vec3 & d, const glm::vec3 & col) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Cuboid(a, b, c, d, col)));

}

void ObjectInterface::createCuboid(unsigned long id, const glm::vec3 & a, const glm::vec3 & b, const glm::vec3 & c,
			const glm::vec3 & d, const std::initializer_list<glm::vec3> & colors) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Cuboid(a, b, c, d, colors)));

}

void ObjectInterface::createCone(unsigned long id, const glm::vec3 & base, const glm::vec3 & axis, float length,
			float lowerRadius, float upperRadius, unsigned int sections, const glm::vec3 & col) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Cone(base, axis, length, lowerRadius, upperRadius, sections, col)));

}

void ObjectInterface::createCone(unsigned long id, const glm::vec3 & base, const glm::vec3 & axis, float length,
			float lowerRadius, float upperRadius, unsigned int sections, const std::initializer_list<glm::vec3> & colors) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Cone(base, axis, length, lowerRadius, upperRadius, sections, colors)));

}

void ObjectInterface::createSphere(unsigned long id, const glm::vec3 & center, float radius, unsigned int rings,
	unsigned int sectors, const glm::vec3 & color) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Sphere(center, radius, rings, sectors, color)));

}

void ObjectInterface::createSphere(unsigned long id, const glm::vec3 & center, float radius, unsigned int rings,
	unsigned int sectors, const std::initializer_list<glm::vec3> & colors) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Sphere(center, radius, rings, sectors, colors)));

}

void ObjectInterface::createSpline(unsigned long id, const glm::vec3 & start, const glm::vec3 & dirStart,
	const glm::vec3 & end, const glm::vec3 & dirEnd, const glm::vec3 & up, float widthStart, float widthEnd,
	unsigned int steps,	float smooth, const glm::vec3 & color) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Spline(start, dirStart, end, dirEnd, up,
		widthStart, widthEnd, steps, smooth, color)));

}

void ObjectInterface::createSpline(unsigned long id, const std::vector<glm::vec3> & path, const glm::vec3 & up,
	float width, const glm::vec3 & color) {

	std::lock_guard<std::mutex> lock(s_mutex);

	addObject(id, std::shared_ptr<Object>(new Spline(path, up, width, color)));

}

void ObjectInterface::copyObject(unsigned long orig, unsigned long copy) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(orig);
	addObject(copy, instance().m_objects.at(orig)->getCopy());

}

template<class T>
void ObjectInterface::createInstance(unsigned long id) {
			
	std::lock_guard<std::mutex> lock(s_mutex);

	T tmp;

	addObject(id, tmp.getInstance());

}

template void ObjectInterface::createInstance<Triangle>(unsigned long);
template void ObjectInterface::createInstance<Quadrilateral>(unsigned long);
template void ObjectInterface::createInstance<Circle>(unsigned long);
template void ObjectInterface::createInstance<Cuboid>(unsigned long);
template void ObjectInterface::createInstance<Cone>(unsigned long);
template void ObjectInterface::createInstance<Sphere>(unsigned long);
template void ObjectInterface::createInstance<Spline>(unsigned long);

void ObjectInterface::draw(unsigned long id) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);
	instance().m_objects.at(id)->draw();

}

const glm::mat4 & ObjectInterface::getModelMatrix(unsigned long id) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);
	return instance().m_objects.at(id)->getModelMatrix();

}

void ObjectInterface::rotate(unsigned long id, float rad, const glm::vec3 & axis) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	obj->rotate(rad, axis);

	if (obj->hasAttachments()) {
		for (auto ob : obj->m_attachedObjects) {
			instance().m_objects.at(ob)->rotateAround(rad, axis, obj->m_actualPosition);
		}
	}

}

void ObjectInterface::rotateAround(unsigned long id, float rad, const glm::vec3 & axis, const glm::vec3 & point) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	obj->rotateAround(rad, axis, point);

	if (obj->hasAttachments()) {
		for (auto ob : obj->m_attachedObjects) {
			instance().m_objects.at(ob)->rotateAround(rad, axis, point);
		}
	}

}

void ObjectInterface::rotateAround(unsigned long id, float rad, const glm::vec3 & axis, unsigned long around) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);
	instance().checkID(around);

	auto & obj = instance().m_objects.at(id);
	auto & aroundObj = instance().m_objects.at(around);
	obj->rotateAround(rad, axis, aroundObj->m_actualPosition);

	if (obj->hasAttachments()) {
		for (auto ob : obj->m_attachedObjects) {
			instance().m_objects.at(ob)->rotateAround(rad, axis, aroundObj->m_actualPosition);
		}
	}

}

void ObjectInterface::move(unsigned long id, float val, const glm::vec3 & dir) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	obj->move(val, dir);

	if (obj->hasAttachments()) {
		for (auto o : obj->m_attachedObjects) {
			instance().m_objects.at(o)->move(val, dir);
		}
	}

}

void ObjectInterface::moveTo(unsigned long id, const glm::vec3 & to) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	auto old = obj->m_actualPosition;
	obj->moveTo(to);

	if (obj->hasAttachments()) {
		auto diff = obj->m_actualPosition - old;
		for (auto ob : obj->m_attachedObjects) {
			auto & o = instance().m_objects.at(ob);
			o->moveTo(o->m_actualPosition + diff);
		}
	}
	

}

void ObjectInterface::scale(unsigned long id, const glm::vec3 & val) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	auto & obj = instance().m_objects.at(id);
	obj->scale(val);

	if (obj->hasAttachments()) {
		
		for (auto ob : obj->m_attachedObjects) {
			auto & o = instance().m_objects.at(ob);

			o->scale(val);
			o->moveTo(obj->m_actualPosition + val * (o->m_actualPosition - obj->m_actualPosition));
			
		}
	}

}

void ObjectInterface::scaleColor(unsigned long id, float scale) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	instance().m_objects.at(id)->scaleColor(scale);

}

void ObjectInterface::setColor(unsigned long id, const std::initializer_list<glm::vec3> & colors) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	instance().m_objects.at(id)->setColor(colors);

}

void ObjectInterface::setColor(unsigned long id, const glm::vec3 & color) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	instance().m_objects.at(id)->setColor(color);

}

void ObjectInterface::attach(unsigned long id, unsigned long attachment) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);
	instance().checkID(attachment);
	auto & v = instance().m_objects.at(id)->m_attachedObjects;
	auto it = std::find(v.cbegin(), v.cend(), attachment);
	if (it == v.cend()) {
		v.emplace_back(attachment);
	}

}

const std::vector<glm::vec4> & ObjectInterface::getObjectData(unsigned long id) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	return instance().m_objects.at(id)->getData();

}

const std::vector<Tri> & ObjectInterface::getObjectTriangles(unsigned long id) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	return instance().m_objects.at(id)->getTriangles();

}

unsigned int ObjectInterface::getObjectType(unsigned long id) {

	std::lock_guard<std::mutex> lock(s_mutex);

	instance().checkID(id);

	return instance().m_objects.at(id)->getType();

}
