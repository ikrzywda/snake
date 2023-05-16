#ifndef DRAWING_SERVICE_HPP
#define DRAWING_SERVICE_HPP

#include <SFML/Graphics.hpp>
#include <sstream>

#include "assets.hpp"
#include "game_model.hpp"
#include "types.hpp"

struct GameDrawingBuffer {
  m_game_coordinates board_dimensions;
  std::vector<TileDescriptors> tiles;
  std::string time_string;
  std::string score_string;

  GameDrawingBuffer(m_game_coordinates board_dimensions_in);
};

namespace DrawingService {
bool update_drawing_buffer(GameDrawingBuffer *draw_game_in,
                           GameModel *game_model_in);
void draw_game(sf::RenderWindow &window, GameDrawingBuffer *draw_game_in);
void draw_menu(sf::RenderWindow &window);
void draw_game_over(sf::RenderWindow &window,
                    std::vector<std::string> scores_string);
void draw_game_over_header(sf::RenderWindow &window);
void draw_game_over_scoreboard(sf::RenderWindow &window,
                               std::vector<std::string> scores_string);
void draw_game_over_prompt(sf::RenderWindow &window);
void draw_header(sf::RenderWindow &window, std::string time_string,
                 std::string score_string);
void draw_board(sf::RenderWindow &window, m_game_coordinates board_dimensions,
                std::vector<TileDescriptors> tiles);

const double HEADER_HEIGHT_PERCENTAGE{0.2};
const double BOARD_HEIGHT_PERCENTAGE{0.8};
};  // namespace DrawingService

#endif
