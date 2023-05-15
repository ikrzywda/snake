#include "types.hpp"

m_game_coordinates operator+(const m_game_coordinates& lhs,
                             const m_game_coordinates& rhs) {
  return {lhs.first + rhs.first, lhs.second + rhs.second};
}

m_game_coordinates operator-(const m_game_coordinates& lhs,
                             const m_game_coordinates& rhs) {
  return {lhs.first - rhs.first, lhs.second - rhs.second};
}

bool operator==(const m_game_coordinates& lhs, const m_game_coordinates& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

std::string ScoreModel::serialize_to_string() {
  return std::to_string(score) + " " + score_time_string + " ";
}
