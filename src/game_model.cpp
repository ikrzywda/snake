#include "game_model.hpp"

GameModel::GameModel(unsigned int board_width, unsigned int board_height)
    : board(board_width, board_height),
      snake(),
      score(0),
      time_seconds(0),
      has_lost(false) {
  board.spawn_food();
  start_time = std::chrono::system_clock::now();
}

void GameModel::update() {
  if (has_lost) {
    return;
  }
  board.update();
  if (board.is_snake_colliding_with_food()) {
    score++;
  }
  if (board.is_snake_colliding_with_itself() ||
      board.is_snake_colliding_with_walls()) {
    has_lost = true;
  }
  auto now = std::chrono::system_clock::now();
  auto elapsed_seconds =
      std::chrono::duration_cast<std::chrono::seconds>(now - start_time);
  time_seconds = elapsed_seconds.count();
}

void GameModel::spawn_food() {
  std::vector<m_game_coordinates> available_positions;
  int available_index;

  for (unsigned int i = 0; i < board.width * board.height; i++) {
    unsigned int row = i / board.width;
    unsigned int col = i % board.width;
    if (std::find(snake.body.begin(), snake.body.end(),
                  std::make_pair(row, col)) == snake.body.end()) {
      available_positions.push_back(std::make_pair(row, col));
    }
  }
  available_index = rand() % available_positions.size();
  board.food_position = available_positions[available_index];
}
