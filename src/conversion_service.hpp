#ifndef CONVERSION_SERVICE_HPP
#define CONVERSION_SERVICE_HPP

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

#include "types.hpp"

namespace ConversionService {
m_game_coordinates direction_to_2d_vector(Direction direction);
std::string chrono_timestamp_to_string(
    std::chrono::time_point<std::chrono::system_clock> timestamp);
};  // namespace ConversionService

#endif
