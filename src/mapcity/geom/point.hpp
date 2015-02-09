#ifndef _POINT_
#define _POINT_

#include "../../engine/glmincludes.hpp"
#include "vector.hpp"

#include <ostream>
#include <cassert>

namespace geom {

template <typename T>
class TPoint2 {

	public:

		TPoint2() : m_point{static_cast<T>(0), static_cast<T>(0)} {}
		TPoint2(const T & a, const T & b) : m_point{a, b} {}

		operator const glm::tvec2<T>() const { return m_point; }

		const glm::tvec2<T> & get() const { return m_point; }

		T & operator[](int idx) {
			assert(idx == 0 || idx == 1);
			return m_point[idx];
		}
		const T & operator[](int idx) const {
			assert(idx == 0 || idx == 1);
			return m_point[idx];
		}

	protected:

		glm::tvec2<T> m_point;

};

template <typename T>
auto & operator<<(std::ostream & os, const TPoint2<T> & p) {

	os << "[" << std::to_string(p[0]) << "; " << std::to_string(p[1]) << "]";
	return os;

}

template <typename T>
class TPoint3 {

	public:

		TPoint3() : m_point{static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)} {}
		TPoint3(const T & a, const T & b, const T & c) : m_point{a, b, c} {}

		operator const glm::tvec3<T>() const { return m_point; }

		const glm::tvec3<T> & get() const { return m_point; }

		T & operator[](int idx) {
			assert(idx == 0 || idx == 1 || idx == 2);
			return m_point[idx];
		}
		const T & operator[](int idx) const {
			assert(idx == 0 || idx == 1 || idx == 2);
			return m_point[idx];
		}

	protected:

		glm::tvec3<T> m_point;

};

template <typename T>
auto & operator<<(std::ostream & os, const TPoint3<T> & p) {

	os << "[" << std::to_string(p[0]) << "; " << std::to_string(p[1]) << "; "
		<< std::to_string(p[2]) << "]";
	return os;

}

using Point = TPoint3<float>;
using Point_d = TPoint3<double>;

} // namespace geom

#endif // _POINT_
