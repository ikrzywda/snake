#include "snake_model.hpp"

Snake::Snake(m_game_coordinates head, Direction direction) {
  body.push_back(head);
  this->direction = direction;
}

m_game_coordinates direction_to_2d_vector(Direction direction) {
  switch (direction) {
    case Direction::UP:
      return std::make_pair(0, -1);
    case Direction::DOWN:
      return std::make_pair(0, 1);
    case Direction::LEFT:
      return std::make_pair(-1, 0);
    case Direction::RIGHT:
      return std::make_pair(1, 0);
  }
}

void Snake::move(Direction direction) {
  m_game_coordinates head = body.front();
  m_game_coordinates direction_vector = direction_to_2d_vector(direction);
  head = head + direction_vector;
  std::rotate(body.rbegin(), body.rbegin() + 1, body.rend());
  body.front() = head;
}

void Snake::grow() {
  m_game_coordinates tail = body.back();
  m_game_coordinates direction_vector = direction_to_2d_vector(direction);
  tail = tail - direction_vector;
  body.push_back(tail);
}

bool Snake::is_colliding_with_itself() {
  auto head = body.front();
  for (auto it = body.begin() + 1; it != body.end(); it++) {
    if (*it == head) {
      return true;
    }
  }
  return false;
}
