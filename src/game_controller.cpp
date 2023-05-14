#include "game_controller.hpp"

GameController::GameController(sf::RenderWindow &window) : window(window) {
  last_tick = std::chrono::system_clock::now();
}

void GameController::handle_input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
    update_direction(Direction::LEFT);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    update_direction(Direction::RIGHT);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
    update_direction(Direction::UP);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
    update_direction(Direction::DOWN);
  }
}

void GameController::update_direction(Direction new_direction) {
  m_game_coordinates current_direction_vector =
      SnakeService::direction_to_2d_vector(direction);
  m_game_coordinates new_direction_vector =
      SnakeService::direction_to_2d_vector(new_direction);
  if (current_direction_vector + new_direction_vector != std::make_pair(0, 0)) {
    direction = new_direction;
  }
}

void GameController::start_game() {
  game_model = std::make_unique<GameModel>(20, 20);
  game_drawing_buffer =
      std::make_unique<GameDrawingBuffer>(m_game_coordinates(20, 20));
  game_model->spawn_food();
  state = GameState::PLAYING;
}

void GameController::update() {
  switch (state) {
    case GameState::MENU:
      break;
    case GameState::PLAYING:
      game_model->snake.move(direction);
      game_model->update();

      if (game_model->has_lost) {
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
  auto elapsed_input = std::chrono::duration_cast<std::chrono::milliseconds>(
      now - last_input_tick);
  if (elapsed.count() > 300) {
    last_tick = now;
    update();
    DrawingService::update_drawing_buffer(game_drawing_buffer.get(),
                                          game_model.get());
    DrawingService::draw_game(window, game_drawing_buffer.get());
  }
  if (elapsed_input.count() > 20) {
    last_input_tick = now;
    handle_input();
  }
}
