#include "game_controller.hpp"

DifficultyModel::DifficultyModel(unsigned int start_speed_in,
                                 unsigned int speed_increment_in,
                                 m_game_coordinates board_dimensions_in) {
  start_speed = start_speed_in;
  speed_increment = speed_increment_in;
  board_dimensions = board_dimensions_in;
}

void DifficultyModel::increase_speed() { start_speed += speed_increment; }

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
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
    if (state == GameState::MENU) {
      start_game();
    } else if (state == GameState::GAME_OVER) {
      state = GameState::MENU;
    }
  }
}

void GameController::update_direction(Direction new_direction) {
  m_game_coordinates current_direction_vector =
      ConversionService::direction_to_2d_vector(direction);
  m_game_coordinates new_direction_vector =
      ConversionService::direction_to_2d_vector(new_direction);
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

void GameController::finish_game() {
  state = GameState::GAME_OVER;
  std::vector<ScoreModel> current_scoreboard = ScoreService::get_scores();
  ScoreService::update_scoreboard(
      current_scoreboard,
      ScoreModel{game_model->score,
                 ConversionService::chrono_timestamp_to_string(
                     std::chrono::system_clock::now())});
  DrawingService::draw_game_over(
      window, ScoreService::scores_to_string(current_scoreboard));
}

void GameController::update() {
  switch (state) {
    case GameState::MENU:
      DrawingService::draw_menu(window);
      break;
    case GameState::PLAYING:
      game_model->snake.move(direction);
      game_model->update();

      if (game_model->has_lost) {
        finish_game();
        break;
      }
      DrawingService::update_drawing_buffer(game_drawing_buffer.get(),
                                            game_model.get());
      DrawingService::draw_game(window, game_drawing_buffer.get());
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
  }
  if (elapsed_input.count() > 20) {
    last_input_tick = now;
    handle_input();
  }
}
