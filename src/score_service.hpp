#ifndef SCORE_SERVICE_HPP
#define SCORE_SERVICE_HPP

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "types.hpp"

namespace ScoreService {

const std::string SCORE_FILE_PATH{".game-data/scores.txt"};
const int MAX_SCORES{10};
bool init();
std::vector<ScoreModel> get_scores();
bool update_scoreboard(std::vector<ScoreModel> &score_board,
                       ScoreModel new_score);
std::vector<std::string> scores_to_string(std::vector<ScoreModel> scores);

std::optional<ScoreModel> deserialize_score(std::string score_string);
bool write_scores(std::vector<ScoreModel> scores);

};  // namespace ScoreService

#endif
