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
  inline static const std::string SCORE_FILE_PATH{".snake/scores.txt"};
  inline static const int MAX_SCORES{10};
  // TODO break down to get(), update([Scores], new_score) and
  // scores_to_string()
  static std::vector<ScoreModel> update_scoreboard(ScoreModel new_score);

 private:
  static std::optional<ScoreModel> deserialize_score(std::string score_string);
  static std::vector<ScoreModel> get_scores();
  static bool write_scores(std::vector<ScoreModel> scores);
};

#endif
