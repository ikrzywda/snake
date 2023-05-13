#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <optional>

enum class TileDescriptors { BOARD_TILE, SNAKE_BODY, SNAKE_HEAD, FRUIT };

struct SnakeAssets {
  inline static const std::string FONT_PATH{"assets/Ubuntu-Bold.ttf"};
  static sf::RectangleShape get_board_tile(sf::Vector2f position,
                                           sf::Vector2f size, sf::Color color);
  static sf::RectangleShape get_snake_body(sf::Vector2f position,
                                           sf::Vector2f size, sf::Color color);
  static sf::ConvexShape get_snake_head(sf::Vector2f position,
                                        sf::Vector2f size, sf::Color color);
  static sf::CircleShape get_fruit(sf::Vector2f position, sf::Vector2f size,
                                   sf::Color color);
  static std::unique_ptr<sf::Shape> shape_factory(TileDescriptors descriptor,
                                                  sf::Vector2f position,
                                                  sf::Vector2f size);

  static sf::Font get_font();
};

#endif
