#ifndef BOARD_HPP
#define BOARD_HPP

#include <utility>

#include "snake_model.hpp"

struct Board {
  Board(unsigned int width, unsigned int height);

  unsigned int width, height;
  m_game_coordinates food_position;
  Snake snake;

  bool is_snake_colliding_with_food();
  bool is_snake_colliding_with_itself();
  bool is_snake_colliding_with_walls();

  void update();
  void spawn_food();
};

#endif
