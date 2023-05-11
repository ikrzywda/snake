#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>

#include "types.hpp"

std::pair<int, int> direction_to_2d_vector(Direction direction);

struct Snake {
  Snake(m_game_coordinates head, Direction direction);

  std::vector<m_game_coordinates> body;
  Direction direction;

  void move(Direction direction);
  void grow();
  bool is_colliding_with_itself();
};

#endif
