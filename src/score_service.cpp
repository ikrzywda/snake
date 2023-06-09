#include "score_service.hpp"

namespace ScoreService {

std::optional<ScoreModel> deserialize_score(std::string score_string) {
  try {
    std::istringstream iss{score_string};
    ScoreModel score;
    iss >> score.score >> score.score_time_string;
    return std::make_optional(score);
  } catch (const std::invalid_argument &e) {
    std::cerr << "Invalid argument: " << e.what() << '\n';
    return std::nullopt;
  } catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return std::nullopt;
  }
}

bool init() {
  std::ofstream score_file{SCORE_FILE_PATH, std::ios::out | std::ios::app};
  if (!score_file.is_open()) {
    return false;
  }
  score_file.close();
  return true;
}

std::vector<ScoreModel> get_scores() {
  std::ifstream score_file{SCORE_FILE_PATH};
  std::string line;
  std::vector<ScoreModel> scores = {};

  if (!score_file.is_open()) {
    return scores;
  }

  while (std::getline(score_file, line)) {
    auto score_opt = deserialize_score(line);
    if (!score_opt.has_value()) {
      continue;
    }
    scores.push_back(score_opt.value());
  }
  score_file.close();
  return scores;
}

bool write_scores(std::vector<ScoreModel> scores) {
  std::ofstream score_file{SCORE_FILE_PATH};
  if (!score_file.is_open()) {
    return false;
  }

  for (auto score : scores) {
    score_file << score.serialize_to_string() << '\n';
  }
  score_file.close();
  return true;
}

bool update_scoreboard(std::vector<ScoreModel> &scores, ScoreModel new_score) {
  scores.push_back(new_score);
  std::sort(scores.begin(), scores.end(),
            [](ScoreModel a, ScoreModel b) { return a.score > b.score; });
  if (scores.size() > MAX_SCORES) {
    scores.pop_back();
  }
  return write_scores(scores);
}

std::vector<std::string> scores_to_string(std::vector<ScoreModel> scores) {
  std::vector<std::string> scores_str = {};
  for (auto score : scores) {
    scores_str.push_back(score.serialize_to_string());
  }
  return scores_str;
}

}  // namespace ScoreService
