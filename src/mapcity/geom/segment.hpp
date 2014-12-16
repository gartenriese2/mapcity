#ifndef _SEGMENT_
#define _SEGMENT_

#include "point.hpp"

#include <ostream>

namespace geom {

template <typename T>
class TSegment2 {

	public:

		TSegment2(const TPoint2<T> & a, const TPoint2<T> & b) : m_a{a}, m_b{b} {}

		TPoint2<T> & operator[](unsigned int idx) {
			assert(idx == 0 || idx == 1);
			return idx == 0 ? m_a : m_b;
		}
		const TPoint2<T> & operator[](unsigned int idx) const {
			assert(idx == 0 || idx == 1);
			return idx == 0 ? m_a : m_b;
		}

	protected:

		TPoint2<T> m_a;
		TPoint2<T> m_b;

};

template <typename T>
std::ostream & operator<<(std::ostream & os, const TSegment2<T> & s) {

	os << s[0] << " <-> " << s[1];
	return os;

}

template <typename T>
class TSegment3 {

	public:

		TSegment3(const TPoint3<T> & a, const TPoint3<T> & b) : m_a{a}, m_b{b} {}

		TPoint3<T> & operator[](unsigned int idx) {
			assert(idx == 0 || idx == 1);
			return idx == 0 ? m_a : m_b;
		}
		const TPoint3<T> & operator[](unsigned int idx) const {
			assert(idx == 0 || idx == 1);
			return idx == 0 ? m_a : m_b;
		}

	protected:

		TPoint3<T> m_a;
		TPoint3<T> m_b;

};

template <typename T>
std::ostream & operator<<(std::ostream & os, const TSegment3<T> & s) {

	os << s[0] << " <-> " << s[1];
	return os;

}

using Segment = TSegment3<float>;
using Segment_d = TSegment3<double>;
using Segment2 = TSegment2<float>;
using Segment2_d = TSegment2<double>;

} // namespace geom

#endif // _SEGMENT_
