#include "conversion_service.hpp"

namespace ConversionService {

m_game_coordinates direction_to_2d_vector(Direction direction) {
  switch (direction) {
    case Direction::UP:
      return std::make_pair(0, 1);
    case Direction::DOWN:
      return std::make_pair(0, -1);
    case Direction::LEFT:
      return std::make_pair(-1, 0);
    case Direction::RIGHT:
      return std::make_pair(1, 0);
  }
}

// OP:
// https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
std::string chrono_timestamp_to_string(
    std::chrono::time_point<std::chrono::system_clock> timestamp) {
  std::time_t in_time_t = std::chrono::system_clock::to_time_t(timestamp);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  return ss.str();
}

}  // namespace ConversionService
