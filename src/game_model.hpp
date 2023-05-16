#ifndef GAME_MODEL_HPP
#define GAME_MODEL_HPP

#include <chrono>
#include <map>

#include "snake_model.hpp"

enum class Difficulty { EASY, MEDIUM, HARD };

struct DifficultyModel {
  unsigned int start_speed;
  unsigned int speed_increment;
  m_game_coordinates board_dimensions;
  DifficultyModel(unsigned int start_speed_in, unsigned int speed_increment_in,
                  m_game_coordinates board_dimensions_in);

  void increase_speed();
};

static std::map<Difficulty, DifficultyModel> DifficultyMap{
    {Difficulty::EASY, DifficultyModel{100, 10, {20, 20}}},
    {Difficulty::MEDIUM, DifficultyModel{150, 15, {30, 30}}},
    {Difficulty::HARD, DifficultyModel{200, 20, {40, 40}}}};

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
