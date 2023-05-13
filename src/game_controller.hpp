#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <chrono>
#include <memory>
#include <optional>

#include "game_view.hpp"
#include "types.hpp"

struct GameController {
  std::unique_ptr<GameModel> game_model;
  std::unique_ptr<GameDrawingBuffer> game_drawing_buffer;
  sf::RenderWindow &window;
  GameState state{GameState::MENU};
  Direction direction{Direction::RIGHT};

  std::chrono::time_point<std::chrono::system_clock> last_tick;

  GameController(sf::RenderWindow &window);
  void start_game();
  void handle_input();
  void update();
  void tick();
  void run();
};

#endif
