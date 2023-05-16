#include "drawing_service.hpp"

GameDrawingBuffer::GameDrawingBuffer(m_game_coordinates board_dimensions_in) {
  board_dimensions = board_dimensions_in;
  tiles = std::vector<TileDescriptors>(board_dimensions_in.first *
                                       board_dimensions_in.second);
}

namespace DrawingService {

bool update_drawing_buffer(GameDrawingBuffer *draw_game_in,
                           GameModel *game_model_in) {
  draw_game_in->board_dimensions = game_model_in->board_dimensions;
  draw_game_in->time_string =
      "Time: " + std::to_string(game_model_in->time_seconds);
  draw_game_in->score_string = "Score: " + std::to_string(game_model_in->score);
  draw_game_in->tiles.assign(game_model_in->board_dimensions.first *
                                 game_model_in->board_dimensions.second,
                             TileDescriptors::BOARD_TILE);

  auto [food_x, food_y] = game_model_in->food_position;
  draw_game_in->tiles[food_y * game_model_in->board_dimensions.first + food_x] =
      TileDescriptors::FRUIT;

  for (auto snake_part : game_model_in->snake.body) {
    auto [snake_part_x, snake_part_y] = snake_part;
    draw_game_in->tiles[snake_part_y * game_model_in->board_dimensions.first +
                        snake_part_x] = TileDescriptors::SNAKE_BODY;
  }

  return true;
}

void draw_header(sf::RenderWindow &window, std::string time_string,
                 std::string score_string) {
  sf::RectangleShape header(sf::Vector2f(
      window.getSize().x, window.getSize().y * HEADER_HEIGHT_PERCENTAGE));
  header.setFillColor(sf::Color::Black);

  sf::Font font = SnakeAssets::get_font();

  sf::Text time_text(time_string, font, 24);
  time_text.setFillColor(sf::Color::White);
  time_text.setPosition(sf::Vector2f(
      10, header.getSize().y / 2 - time_text.getLocalBounds().height / 2));

  sf::Text score_text(score_string, font, 24);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(sf::Vector2f(
      header.getSize().x - score_text.getLocalBounds().width - 10,
      header.getSize().y / 2 - score_text.getLocalBounds().height / 2));

  window.draw(header);
  window.draw(time_text);
  window.draw(score_text);
}

void draw_board(sf::RenderWindow &window, m_game_coordinates board_dimensions,
                std::vector<TileDescriptors> tiles) {
  float max_board_height = window.getSize().y * BOARD_HEIGHT_PERCENTAGE;
  float max_board_width =
      max_board_height * board_dimensions.first / board_dimensions.second;
  float board_left = (window.getSize().x - max_board_width) / 2.0f;
  sf::RectangleShape board(sf::Vector2f(max_board_width, max_board_height));
  board.setPosition(
      sf::Vector2f(board_left, window.getSize().y * HEADER_HEIGHT_PERCENTAGE));
  board.setFillColor(sf::Color::White);
  window.draw(board);

  float tile_size = std::min(max_board_width / board_dimensions.first,
                             max_board_height / board_dimensions.second);
  sf::Vector2f tile_dimensions(tile_size, tile_size);
  sf::Vector2f tile_position(
      board_left,
      window.getSize().y * HEADER_HEIGHT_PERCENTAGE +
          (max_board_height - tile_size * board_dimensions.second) / 2.0f);

  for (auto tile : tiles) {
    auto board_tile = SnakeAssets::shape_factory(
        TileDescriptors::BOARD_TILE, tile_position, tile_dimensions);
    auto shape =
        SnakeAssets::shape_factory(tile, tile_position, tile_dimensions);
    tile_position.x += tile_size;
    if (tile_position.x >= board_left + max_board_width) {
      tile_position.x = board_left;
      tile_position.y += tile_size;
    }
    window.draw(*board_tile);
    if (shape != nullptr || tile != TileDescriptors::BOARD_TILE) {
      window.draw(*shape);
    }
  }
}

void draw_game(sf::RenderWindow &window, GameDrawingBuffer *draw_game_in) {
  window.clear();
  draw_header(window, draw_game_in->time_string, draw_game_in->score_string);
  draw_board(window, draw_game_in->board_dimensions, draw_game_in->tiles);
  window.display();
}

// generated with gpt-3.5
void draw_menu(sf::RenderWindow &window) {
  sf::Font font = SnakeAssets::get_font();

  sf::Text title("Snake", font, 48);
  title.setFillColor(sf::Color::White);
  title.setStyle(sf::Text::Bold);
  title.setPosition(sf::Vector2f(
      window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100));

  sf::Text instructions(
      "Press Enter to start game\n\nUse HJKL for movement\n\nPress Esc to quit",
      font, 32);
  instructions.setFillColor(sf::Color::White);
  instructions.setPosition(sf::Vector2f(
      window.getSize().x / 2 - instructions.getGlobalBounds().width / 2, 300));

  instructions.setLineSpacing(1.5);
  instructions.setFillColor(sf::Color::White);
  instructions.setOutlineColor(sf::Color::Black);
  instructions.setOutlineThickness(2);
  instructions.setCharacterSize(32);
  instructions.setStyle(sf::Text::Regular);
  instructions.setOrigin(
      sf::Vector2f(instructions.getLocalBounds().width / 2.f, 0));
  instructions.setPosition(
      sf::Vector2f(sf::Vector2f(window.getSize().x / 2.f, 400)));

  window.clear(sf::Color::Black);
  window.draw(title);
  window.draw(instructions);
  window.display();
}

void draw_game_over(sf::RenderWindow &window,
                    std::vector<std::string> scores_string) {
  window.clear();

  draw_game_over_header(window);
  draw_game_over_scoreboard(window, scores_string);
  draw_game_over_prompt(window);

  window.display();
}

void draw_game_over_header(sf::RenderWindow &window) {
  sf::RectangleShape header(sf::Vector2f(
      window.getSize().x, window.getSize().y * HEADER_HEIGHT_PERCENTAGE));
  header.setFillColor(sf::Color::Black);

  sf::Font font = SnakeAssets::get_font();

  sf::Text header_text("Game Over", font, 24);
  header_text.setFillColor(sf::Color::White);

  float text_pos_x =
      (window.getSize().x - header_text.getLocalBounds().width) / 2.0f;
  header_text.setPosition(sf::Vector2f(
      text_pos_x,
      header.getSize().y / 2 - header_text.getLocalBounds().height / 2));

  window.draw(header);
  window.draw(header_text);
}

void draw_game_over_scoreboard(sf::RenderWindow &window,
                               std::vector<std::string> scores_string) {
  float max_board_height = window.getSize().y * BOARD_HEIGHT_PERCENTAGE;
  float max_board_width = max_board_height;
  float board_left = (window.getSize().x - max_board_width) / 2.0f;
  sf::RectangleShape scoreboard(
      sf::Vector2f(max_board_width, max_board_height));
  scoreboard.setPosition(
      sf::Vector2f(board_left, window.getSize().y * HEADER_HEIGHT_PERCENTAGE));
  scoreboard.setFillColor(sf::Color::Black);

  sf::Font font = SnakeAssets::get_font();

  sf::Text scoresText;
  scoresText.setFont(font);
  scoresText.setCharacterSize(24);
  scoresText.setFillColor(sf::Color::White);
  scoresText.setPosition(sf::Vector2f(
      board_left + 10, window.getSize().y * HEADER_HEIGHT_PERCENTAGE + 10));

  std::string scoresDisplay;
  for (const auto &score : scores_string) {
    scoresDisplay += score + "\n";
  }

  scoresText.setString(scoresDisplay);

  window.draw(scoreboard);
  window.draw(scoresText);
}

void draw_game_over_prompt(sf::RenderWindow &window) {
  sf::Font font = SnakeAssets::get_font();

  sf::Text promptText;
  promptText.setFont(font);
  promptText.setCharacterSize(24);
  promptText.setFillColor(sf::Color::Black);
  promptText.setString("Press Space to continue");
  sf::FloatRect promptBounds = promptText.getLocalBounds();
  promptText.setOrigin(
      sf::Vector2f(promptBounds.left + promptBounds.width / 2.0f,
                   promptBounds.top + promptBounds.height / 2.0f));
  promptText.setPosition(sf::Vector2f(
      window.getSize().x / 2.0f,
      window.getSize().y *
              (HEADER_HEIGHT_PERCENTAGE + BOARD_HEIGHT_PERCENTAGE) -
          promptBounds.height - 10));

  window.draw(promptText);
}

}  // namespace DrawingService
