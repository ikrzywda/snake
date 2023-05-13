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
  // add text to header for time and score
  sf::Font font = SnakeAssets::get_font();
  sf::Text time_text(time_string, font);
  time_text.setCharacterSize(24);
  time_text.setFillColor(sf::Color::White);
  time_text.setPosition(sf::Vector2f(0, 0));
  sf::Text score_text(score_string, font);
  score_text.setCharacterSize(24);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(sf::Vector2f(0, 24));
  window.draw(time_text);
  window.draw(score_text);

  window.draw(header);
}

void DrawingService::draw_board(sf::RenderWindow &window,
                                m_game_coordinates board_dimensions,
                                std::vector<TileDescriptors> tiles) {
  sf::RectangleShape board(sf::Vector2f(
      window.getSize().x, window.getSize().y * BOARD_HEIGHT_PERCENTAGE));
  board.setPosition(
      sf::Vector2f(0, window.getSize().y * HEADER_HEIGHT_PERCENTAGE));
  board.setFillColor(sf::Color::White);
  window.draw(board);

  auto [board_width, board_height] = board_dimensions;
  sf::Vector2f tile_size(board.getSize().x / board_width,
                         board.getSize().y / board_height);
  sf::Vector2f tile_position(0, window.getSize().y * HEADER_HEIGHT_PERCENTAGE);

  for (auto tile : tiles) {
    auto shape = SnakeAssets::shape_factory(tile, tile_position, tile_size);
    if (shape != nullptr) {
      window.draw(*shape);
    }
    tile_position.x += tile_size.x;
    if (tile_position.x >= board.getSize().x) {
      tile_position.x = 0;
      tile_position.y += tile_size.y;
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

// static void draw_menu(sf::RenderWindow &window) {
//   // TODO: Implement -- click to start / quit
// }
