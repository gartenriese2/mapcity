#ifndef _RANDOM_
#define _RANDOM_

#include <chrono>
#include <random>
#include <type_traits>

class Random {

	public:

		template<class T>
		static const T get(const T from, const T to) {

			if (std::is_floating_point<T>::value) {
				std::uniform_real_distribution<T> distribution(from, to);
				return distribution(generator);
			}
			if (std::is_integral<T>::value) {
				std::uniform_int_distribution<T> distribution(from, to);
				return distribution(generator);
			}

			return from;

		}

	private:

		static std::default_random_engine generator;

};

#endif // _RANDOM_
