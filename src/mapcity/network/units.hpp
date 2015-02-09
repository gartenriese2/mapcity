#ifndef _UNITS_
#define _UNITS_

namespace unit {

struct speed {
	float m_val;
	constexpr speed(float val) : m_val{val} {}
	operator float() const { return m_val; }
	void kmhToMs() { m_val /= 3.6f; }
};

struct time {
	float m_val;
	constexpr time(float val) : m_val{val} {}
	operator float() const { return m_val; }
};

struct length {
	float m_val;
	constexpr length(float val) : m_val{val} {}
	operator float() const { return m_val; }
};

} // namespace unit

constexpr unit::speed operator "" _ms(long double val) {
	return unit::speed {static_cast<float>(val)};
}
constexpr unit::speed operator "" _ms(unsigned long long val) {
	return unit::speed {static_cast<float>(val)};
}
constexpr unit::speed operator "" _kmh(long double val) {
	return unit::speed {static_cast<float>(val) / 3.6f};
}
constexpr unit::speed operator "" _kmh(unsigned long long val) {
	return unit::speed {static_cast<float>(val) / 3.6f};
}

constexpr unit::time operator "" _s(long double val) {
	return unit::time {static_cast<float>(val)};
}
constexpr unit::time operator "" _s(unsigned long long val) {
	return unit::time {static_cast<float>(val)};
}
constexpr unit::time operator "" _min(long double val) {
	return unit::time {static_cast<float>(val) * 60.f};
}
constexpr unit::time operator "" _min(unsigned long long val) {
	return unit::time {static_cast<float>(val) * 60.f};
}
constexpr unit::time operator "" _h(long double val) {
	return unit::time {static_cast<float>(val) * 3600.f};
}
constexpr unit::time operator "" _h(unsigned long long val) {
	return unit::time {static_cast<float>(val) * 3600.f};
}

constexpr unit::length operator "" _m(long double val) {
	return unit::length {static_cast<float>(val)};
}
constexpr unit::length operator "" _m(unsigned long long val) {
	return unit::length {static_cast<float>(val)};
}
constexpr unit::length operator "" _km(long double val) {
	return unit::length {static_cast<float>(val) * 1000.f};
}
constexpr unit::length operator "" _km(unsigned long long val) {
	return unit::length {static_cast<float>(val) * 1000.f};
}

#endif // _UNITS_
