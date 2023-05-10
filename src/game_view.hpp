#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics.hpp>

#include "game_model.hpp"

struct GameView {
  static void draw_game(sf::RenderWindow &window, GameModel &game_model);
  static void draw_menu(sf::RenderWindow &window);
};

#endif
