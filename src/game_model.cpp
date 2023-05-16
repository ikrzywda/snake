#include "game_model.hpp"

DifficultyModel::DifficultyModel(unsigned int start_speed_in,
                                 unsigned int speed_increment_in,
                                 m_game_coordinates board_dimensions_in) {
  start_speed = start_speed_in;
  speed_increment = speed_increment_in;
  board_dimensions = board_dimensions_in;
}

void DifficultyModel::increase_speed() { start_speed += speed_increment; }

GameModel::GameModel(int board_width, int board_height)
    : snake(std::make_pair(board_width / 2, board_height / 2), Direction::UP) {
  board_dimensions = std::make_pair(board_width, board_height);
  spawn_food();
  start_time = std::chrono::system_clock::now();
}

void GameModel::update() {
  if (has_lost) {
    return;
  }
  if (is_snake_colliding_with_food()) {
    score++;
    snake.grow();
    spawn_food();
  }

  has_lost =
      snake.is_colliding_with_itself() || is_snake_colliding_with_walls();

  auto now = std::chrono::system_clock::now();
  auto elapsed_seconds =
      std::chrono::duration_cast<std::chrono::seconds>(now - start_time);
  time_seconds = elapsed_seconds.count();
}

void GameModel::spawn_food() {
  std::vector<m_game_coordinates> available_positions;
  int available_index;
  int board_width = board_dimensions.first;
  int board_height = board_dimensions.second;

  for (int i = 0; i < board_width * board_height; i++) {
    int row = i / board_width;
    int col = i % board_width;
    if (std::find(snake.body.begin(), snake.body.end(),
                  std::make_pair(row, col)) == snake.body.end()) {
      available_positions.push_back(std::make_pair(row, col));
    }
  }

  if (available_positions.empty()) {
    return;
  }

  available_index = rand() % available_positions.size();
  food_position = available_positions[available_index];
}

bool GameModel::is_snake_colliding_with_food() {
  return snake.body.front() == food_position;
}

bool GameModel::is_snake_colliding_with_walls() {
  auto head = snake.body.front();
  return head.first < 0 || head.first >= board_dimensions.first ||
         head.second < 0 || head.second >= board_dimensions.second;
}
