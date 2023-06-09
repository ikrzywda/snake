#include "game_controller.hpp"

GameController::GameController(sf::RenderWindow &window) : window(window) {
  last_tick = std::chrono::system_clock::now();
}

void GameController::hanle_menu_input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
    difficulty = Difficulty::EASY;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
    difficulty = Difficulty::MEDIUM;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
    difficulty = Difficulty::HARD;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
    start_game(difficulty);
  }
}

void GameController::handle_game_input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
    game_model->update_direction(Direction::LEFT);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
    game_model->update_direction(Direction::RIGHT);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
    game_model->update_direction(Direction::UP);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
    game_model->update_direction(Direction::DOWN);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    finish_game();
  }
}

void GameController::handle_game_over_input() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
    state = GameState::MENU;
  }
}

void GameController::handle_input() {
  switch (state) {
    case GameState::MENU:
      hanle_menu_input();
      break;
    case GameState::PLAYING:
      handle_game_input();
      break;
    case GameState::GAME_OVER:
      handle_game_over_input();
      break;
  }
}

void GameController::start_game(Difficulty selected_difficulty) {
  difficulty = selected_difficulty;
  DifficultyModel difficulty_model = DifficultySettingsMap[difficulty];

  game_model = std::make_unique<GameModel>(difficulty_model.board_dimensions);
  game_drawing_buffer =
      std::make_unique<GameDrawingBuffer>(difficulty_model.board_dimensions);
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
      DrawingService::draw_menu(window,
                                DifficultySettingsMap[difficulty].description);
      break;
    case GameState::PLAYING:
      game_model->update();
      tick_duration_ms =
          tick_duration_ms >
                  DifficultySettingsMap[difficulty].min_tick_duration_ms
              ? 300 -
                    game_model.get()->score * DifficultySettingsMap[difficulty]
                                                  .speed_increment_per_food
              : DifficultySettingsMap[difficulty].min_tick_duration_ms;

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
  if (elapsed.count() > tick_duration_ms) {
    last_tick = now;
    update();
  }
  if (elapsed_input.count() > 33) {
    last_input_tick = now;
    handle_input();
  }
}
