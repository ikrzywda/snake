#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include <chrono>

#include "board_model.hpp"
#include "snake_model.hpp"

struct GameModel {
  GameModel(unsigned int board_width, unsigned int board_height);

  Board board;
  Snake snake;
  unsigned int score;
  unsigned int time_seconds;
  bool has_lost;

  std::chrono::time_point<std::chrono::system_clock> start_time;
  void update();
  void spawn_food();
};

#endif
