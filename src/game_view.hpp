#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

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

struct DrawingService {
  static bool update_drawing_buffer(GameDrawingBuffer *draw_game_in,
                                    GameModel *game_model_in);
  static void draw_game(sf::RenderWindow &window,
                        GameDrawingBuffer *draw_game_in);
  static void draw_menu(sf::RenderWindow &window);
  static void draw_game_over(sf::RenderWindow &window,
                             std::string scores_string);

 private:
  static void draw_header(sf::RenderWindow &window, std::string time_string,
                          std::string score_string);
  static void draw_board(sf::RenderWindow &window,
                         m_game_coordinates board_dimensions,
                         std::vector<TileDescriptors> tiles);

  inline static const double HEADER_HEIGHT_PERCENTAGE{0.2};
  inline static const double BOARD_HEIGHT_PERCENTAGE{0.8};
};

#endif
