#include "random.hpp"

const auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine Random::generator = std::default_random_engine(static_cast<unsigned long>(seed));


