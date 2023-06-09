#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <utility>

enum class Direction { UP, DOWN, LEFT, RIGHT };
enum class GameState { MENU, PLAYING, GAME_OVER };

using m_game_coordinates = std::pair<int, int>;

// generated with gpt 3.5
m_game_coordinates operator+(const m_game_coordinates& lhs,
                             const m_game_coordinates& rhs);

m_game_coordinates operator-(const m_game_coordinates& lhs,
                             const m_game_coordinates& rhs);

bool operator==(const m_game_coordinates& lhs, const m_game_coordinates& rhs);

struct ScoreModel {
  unsigned int score{0};
  std::string score_time_string{""};

  std::string serialize_to_string();
  ScoreModel() = default;
};

#endif
