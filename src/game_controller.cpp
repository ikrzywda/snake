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
  switch (state) {
    case GameState::MENU:
      break;
    case GameState::PLAYING:
      handle_input();
      game_model->snake.move(direction);
      if (game_model->is_snake_colliding_with_food()) {
        game_model->snake.grow();
        game_model->spawn_food();
        game_model->score++;
      }
      if (game_model->is_snake_colliding_with_walls() ||
          game_model->snake.is_colliding_with_itself()) {
        state = GameState::GAME_OVER;
      }
      break;
    case GameState::GAME_OVER:
      break;
  }
}

void GameController::tick() {
  auto now = std::chrono::system_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tick);
  if (elapsed.count() > 100) {
    last_tick = now;
    update();
    GameView::draw_game(window, game_model.get());
  }
}