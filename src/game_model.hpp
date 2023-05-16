#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include <chrono>
#include <map>

#include "conversion_service.hpp"
#include "snake_model.hpp"

struct GameModel {
  GameModel(m_game_coordinates board_dimensions_in);

  Direction direction{Direction::RIGHT};
  m_game_coordinates board_dimensions;
  m_game_coordinates food_position;
  Snake snake;

  bool is_snake_colliding_with_walls();
  bool is_snake_colliding_with_food();
  unsigned int score{0};
  unsigned int time_seconds{0};
  bool has_lost{false};

  std::chrono::time_point<std::chrono::system_clock> start_time;
  void update_direction(Direction new_direction);
  void update();
  void spawn_food();
};

#endif
