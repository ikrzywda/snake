#ifndef ASSETS_HPP
#define ASSETS_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <optional>

enum class TileDescriptors { BOARD_TILE, SNAKE_BODY, SNAKE_HEAD, FRUIT };

namespace SnakeAssets {
  
const std::string FONT_PATH{"assets/Ubuntu-Bold.ttf"};
sf::RectangleShape get_board_tile(sf::Vector2f position, sf::Vector2f size,
                                  sf::Color color);
sf::RectangleShape get_snake_body(sf::Vector2f position, sf::Vector2f size,
                                  sf::Color color);
sf::ConvexShape get_snake_head(sf::Vector2f position, sf::Vector2f size,
                               sf::Color color);
sf::CircleShape get_fruit(sf::Vector2f position, sf::Vector2f size,
                          sf::Color color);
std::unique_ptr<sf::Shape> shape_factory(TileDescriptors descriptor,
                                         sf::Vector2f position,
                                         sf::Vector2f size);
sf::Font get_font();
};  // namespace SnakeAssets

#endif
