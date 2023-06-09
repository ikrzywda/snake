#include "game_model.hpp"

GameModel::GameModel(m_game_coordinates board_dimensions_in)
    : snake(std::make_pair(board_dimensions_in.first / 2,
                           board_dimensions_in.second / 2),
            Direction::UP) {
  board_dimensions = board_dimensions_in;
  spawn_food();
  start_time = std::chrono::system_clock::now();
}

void GameModel::update_direction(Direction new_direction) {
  m_game_coordinates current_direction_vector =
      ConversionService::direction_to_2d_vector(direction);
  m_game_coordinates new_direction_vector =
      ConversionService::direction_to_2d_vector(new_direction);
  if (current_direction_vector + new_direction_vector != std::make_pair(0, 0)) {
    direction = new_direction;
  }
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
  snake.move(direction);
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
