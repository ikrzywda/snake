#include "score_service.hpp"

std::string ScoreModel::serialize_to_string() {
  return std::to_string(score) + " " + score_time_string + " ";
}

std::optional<ScoreModel> ScoreService::deserialize_score(
    std::string score_string) {
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

std::vector<ScoreModel> ScoreService::get_scores() {
  std::ifstream score_file{ScoreService::SCORE_FILE_PATH};
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

bool ScoreService::write_scores(std::vector<ScoreModel> scores) {
  std::ofstream score_file{ScoreService::SCORE_FILE_PATH};
  if (!score_file.is_open()) {
    return false;
  }

  for (auto score : scores) {
    score_file << score.serialize_to_string() << '\n';
  }
  score_file.close();
  return true;
}

bool ScoreService::insert_score(ScoreModel new_score) {
  std::vector<ScoreModel> scores;
  auto scores_opt = get_scores();
  if (scores_opt.empty()) {
    return false;
  }

  scores.push_back(new_score);
  std::sort(scores.begin(), scores.end(),
            [](ScoreModel a, ScoreModel b) { return a.score > b.score; });
  if (scores.size() > ScoreService::MAX_SCORES) {
    scores.pop_back();
  }

  return write_scores(scores);
}
