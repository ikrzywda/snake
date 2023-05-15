#ifndef SCORE_SERVICE_HPP
#define SCORE_SERVICE_HPP

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "types.hpp"

struct ScoreService {
  inline static const std::string SCORE_FILE_PATH{".game-data/scores.txt"};
  inline static const int MAX_SCORES{10};
  static bool init();
  static std::vector<ScoreModel> get_scores();
  static bool update_scoreboard(std::vector<ScoreModel> &score_board,
                                ScoreModel new_score);
  static std::string scores_to_string(std::vector<ScoreModel> scores);

 private:
  static std::optional<ScoreModel> deserialize_score(std::string score_string);
  static bool write_scores(std::vector<ScoreModel> scores);
};

#endif
