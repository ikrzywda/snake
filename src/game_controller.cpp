#include "game_controller.hpp"

GameController::GameController(sf::RenderWindow &window) : window(window) {
  last_tick = std::chrono::system_clock::now();
}

void GameController::handle_input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
    direction = Direction::LEFT;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    direction = Direction::RIGHT;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
    direction = Direction::UP;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
    direction = Direction::DOWN;
  }
}

void GameController::start_game() {
  game_model = std::make_unique<GameModel>(20, 20);
  game_model->spawn_food();
  state = GameState::PLAYING;
}

void GameController::update() {
  game_model->update();

  window.display();
}
