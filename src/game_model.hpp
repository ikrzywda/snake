#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include <chrono>
#include <map>

#include "snake_model.hpp"

struct GameModel {
  GameModel(int board_width, int board_height);

  m_game_coordinates board_dimensions;
  m_game_coordinates food_position;
  Snake snake;

  bool is_snake_colliding_with_food();
  bool is_snake_colliding_with_walls();
  unsigned int score{0};
  unsigned int time_seconds{0};
  bool has_lost{false};

  std::chrono::time_point<std::chrono::system_clock> start_time;
  void update();
  void spawn_food();
};

#endif
