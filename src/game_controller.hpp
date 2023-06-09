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
  unsigned int speed_increment_per_food{1};
  m_game_coordinates board_dimensions;
  unsigned int min_tick_duration_ms;
  std::string description;
};

static std::map<Difficulty, DifficultyModel> DifficultySettingsMap{
    {Difficulty::EASY, DifficultyModel{5, {20, 20}, 150, "Easy"}},
    {Difficulty::MEDIUM, DifficultyModel{10, {30, 30}, 100, "Medium"}},
    {Difficulty::HARD, DifficultyModel{10, {40, 40}, 75, "Hard"}}};

struct GameController {
  unsigned int tick_duration_ms{1 / 3};
  Difficulty difficulty{Difficulty::MEDIUM};
  sf::RenderWindow &window;
  std::unique_ptr<GameModel> game_model;
  std::unique_ptr<GameDrawingBuffer> game_drawing_buffer;
  GameState state{GameState::MENU};
  Direction direction{Direction::RIGHT};

  std::chrono::time_point<std::chrono::system_clock> last_tick;
  std::chrono::time_point<std::chrono::system_clock> last_input_tick;

  GameController(sf::RenderWindow &window);
  void start_game(Difficulty selected_difficulty);
  void finish_game();
  void hanle_menu_input();
  void handle_game_over_input();
  void handle_game_input();
  void handle_input();
  void update();
  void tick();
};

#endif
