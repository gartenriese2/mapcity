#ifndef _VECTOR_
#define _VECTOR_

#include "../../engine/glmincludes.hpp"

#include <ostream>

namespace geom {

template <typename T>
class TVec2 {

	public:

		TVec2() : m_vec{static_cast<T>(0), static_cast<T>(0)} {}
		TVec2(const T & a, const T & b) : m_vec{a, b} {}

		operator const glm::tvec2<T>() const { return m_vec; }

		T & operator[](int idx) {
			assert(idx == 0 || idx == 1);
			return m_vec[idx];
		}
		const T & operator[](int idx) const {
			assert(idx == 0 || idx == 1);
			return m_vec[idx];
		}

	protected:

		glm::tvec2<T> m_vec;

};

template <typename T>
std::ostream & operator<<(std::ostream & os, const TVec2<T> & v) {

	os << "[" << std::to_string(v[0]) << "; " << std::to_string(v[1]) << "]";
	return os;

}

template <typename T>
class TVec3 {

	public:

		TVec3() : m_vec{static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)} {}
		TVec3(const T & a, const T & b, const T & c) : m_vec{a, b, c} {}

		operator const glm::tvec3<T>() const { return m_vec; }

		T & operator[](int idx) {
			assert(idx == 0 || idx == 1 || idx == 2);
			return m_vec[idx];
		}
		const T & operator[](int idx) const {
			assert(idx == 0 || idx == 1 || idx == 2);
			return m_vec[idx];
		}

	protected:

		glm::tvec3<T> m_vec;

};

template <typename T>
std::ostream & operator<<(std::ostream & os, const TVec3<T> & v) {

	os << "[" << std::to_string(v[0]) << "; " << std::to_string(v[1]) << "; "
		<< std::to_string(v[2]) << "]";
	return os;

}

using Vec = TVec3<float>;
using Vec_d = TVec3<double>;

} // namespace geom

#endif // _VECTOR_
