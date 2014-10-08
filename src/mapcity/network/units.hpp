#ifndef _UNITS_
#define _UNITS_

struct Speed {
	float m_val;
	constexpr Speed(float val) : m_val{val} {}
	operator float() const { return m_val; }
};

constexpr Speed operator "" _ms(long double val) {
	return Speed {static_cast<float>(val)};
}
constexpr Speed operator "" _ms(unsigned long long val) {
	return Speed {static_cast<float>(val)};
}
constexpr Speed operator "" _kmh(long double val) {
	return Speed {static_cast<float>(val) / 3.6f};
}
constexpr Speed operator "" _kmh(unsigned long long val) {
	return Speed {static_cast<float>(val) / 3.6f};
}

struct Time {
	float m_val;
	constexpr Time(float val) : m_val{val} {}
	operator float() const { return m_val; }
};

constexpr Time operator "" _s(long double val) {
	return Time {static_cast<float>(val)};
}
constexpr Time operator "" _s(unsigned long long val) {
	return Time {static_cast<float>(val)};
}
constexpr Time operator "" _min(long double val) {
	return Time {static_cast<float>(val) * 60.f};
}
constexpr Time operator "" _min(unsigned long long val) {
	return Time {static_cast<float>(val) * 60.f};
}
constexpr Time operator "" _h(long double val) {
	return Time {static_cast<float>(val) * 3600.f};
}
constexpr Time operator "" _h(unsigned long long val) {
	return Time {static_cast<float>(val) * 3600.f};
}

struct Length {
	float m_val;
	constexpr Length(float val) : m_val{val} {}
	operator float() const { return m_val; }
};

constexpr Length operator "" _m(long double val) {
	return Length {static_cast<float>(val)};
}
constexpr Length operator "" _m(unsigned long long val) {
	return Length {static_cast<float>(val)};
}
constexpr Length operator "" _km(long double val) {
	return Length {static_cast<float>(val) * 1000.f};
}
constexpr Length operator "" _km(unsigned long long val) {
	return Length {static_cast<float>(val) * 1000.f};
}

#endif // _UNITS_
