#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics.hpp>

#include "game_model.hpp"
#include "types.hpp"
#include "assets.hpp"

struct DrawGameIn {
  m_game_coordinates board_dimensions;
  std::string time_string;
  std::string score_string;
  std::vector<TileDescriptors> tiles;
};

struct GameView {
  static void draw_game(sf::RenderWindow &window, DrawGameIn &draw_game_in);
  static void draw_menu(sf::RenderWindow &window);
  static void draw_game_over(sf::RenderWindow &window);
};

#endif
