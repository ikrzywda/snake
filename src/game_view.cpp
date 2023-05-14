#include "game_view.hpp"

GameDrawingBuffer::GameDrawingBuffer(m_game_coordinates board_dimensions_in) {
  board_dimensions = board_dimensions_in;
  tiles = std::vector<TileDescriptors>(board_dimensions_in.first *
                                       board_dimensions_in.second);
}

bool DrawingService::update_drawing_buffer(GameDrawingBuffer *draw_game_in,
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

void DrawingService::draw_header(sf::RenderWindow &window,
                                 std::string time_string,
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

void DrawingService::draw_board(sf::RenderWindow &window,
                                m_game_coordinates board_dimensions,
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
    auto shape =
        SnakeAssets::shape_factory(tile, tile_position, tile_dimensions);
    if (shape != nullptr) {
      window.draw(*shape);
    }
    tile_position.x += tile_size;
    if (tile_position.x >= board_left + max_board_width) {
      tile_position.x = board_left;
      tile_position.y += tile_size;
    }
  }
}

void DrawingService::draw_game(sf::RenderWindow &window,
                               GameDrawingBuffer *draw_game_in) {
  window.clear();
  draw_header(window, draw_game_in->time_string, draw_game_in->score_string);
  draw_board(window, draw_game_in->board_dimensions, draw_game_in->tiles);
  window.display();
}

// generated with gpt-3.5
void DrawingService::draw_menu(sf::RenderWindow &window) {
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
