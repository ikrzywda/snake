#include "snake_service.hpp"

m_game_coordinates SnakeService::direction_to_2d_vector(Direction direction) {
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
