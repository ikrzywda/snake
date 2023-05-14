#ifndef SNAKE_SERVICE_HPP
#define SNAKE_SERVICE_HPP

#include "types.hpp"

struct SnakeService {
  static m_game_coordinates direction_to_2d_vector(Direction direction);
};

#endif
