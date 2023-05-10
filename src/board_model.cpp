#include "board_model.hpp"

Board::Board(unsigned int width, unsigned int height)
    : width(width), height(height), snake() {
  spawn_food();
}

bool Board::is_snake_colliding_with_food() {
  return snake.body.front() == food_position;
}

bool Board::is_snake_colliding_with_itself() {
  return snake.is_colliding_with_itself();
}

bool Board::is_snake_colliding_with_walls() {
  auto head = snake.body.front();
  return head.first < 0 || head.first >= width || head.second < 0 ||
         head.second >= height;
}

void Board::update() {
  snake.move();
  if (is_snake_colliding_with_food()) {
    snake.grow();
    spawn_food();
  }
}

void Board::spawn_food() {
  std::vector<m_game_coordinates> available_positions;
  int available_index;

  for (unsigned int i = 0; i < width * height; i++) {
    unsigned int row = i / width;
    unsigned int col = i % width;
    if (std::find(snake.body.begin(), snake.body.end(),
                  std::make_pair(row, col)) == snake.body.end()) {
      available_positions.push_back(std::make_pair(row, col));
    }
  }
  available_index = rand() % available_positions.size();
  food_position = available_positions[available_index];
}
