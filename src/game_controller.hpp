#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <chrono>
#include <memory>
#include <optional>

#include "conversion_service.hpp"
#include "drawing_service.hpp"
#include "score_service.hpp"
#include "types.hpp"

enum class Difficulty { EASY, MEDIUM, HARD };

struct DifficultyModel {
  unsigned int start_speed;
  unsigned int speed_increment;
  unsigned int max_speed;
  m_game_coordinates board_dimensions;
  DifficultyModel(unsigned int start_speed_in, unsigned int speed_increment_in,
                  m_game_coordinates board_dimensions_in);

  void increase_speed();
};

static std::map<Difficulty, DifficultyModel> DifficultySettingsMap{
    {Difficulty::EASY, DifficultyModel{100, 10, {20, 20}}},
    {Difficulty::MEDIUM, DifficultyModel{150, 15, {30, 30}}},
    {Difficulty::HARD, DifficultyModel{200, 20, {40, 40}}}};

struct GameController {
  Difficulty difficulty{Difficulty::MEDIUM};
  sf::RenderWindow &window;
  std::unique_ptr<GameModel> game_model;
  std::unique_ptr<GameDrawingBuffer> game_drawing_buffer;
  GameState state{GameState::MENU};
  Direction direction{Direction::RIGHT};

  std::chrono::time_point<std::chrono::system_clock> last_tick;
  std::chrono::time_point<std::chrono::system_clock> last_input_tick;

  GameController(sf::RenderWindow &window);
  void update_direction(Direction direction);
  void start_game();
  void finish_game();
  void handle_input();
  void update();
  void tick();
};

#endif
