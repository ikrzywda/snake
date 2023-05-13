#include "assets.hpp"

sf::RectangleShape SnakeAssets::get_board_tile(sf::Vector2f position,
                                               sf::Vector2f size,
                                               sf::Color color) {
  sf::RectangleShape tile(size);
  tile.setPosition(position);
  tile.setFillColor(color);
  return tile;
}

sf::RectangleShape SnakeAssets::get_snake_body(sf::Vector2f position,
                                               sf::Vector2f size,
                                               sf::Color color) {
  sf::RectangleShape tile(size);
  tile.setPosition(position);
  tile.setFillColor(color);
  return tile;
}

sf::ConvexShape SnakeAssets::get_snake_head(sf::Vector2f position,
                                            sf::Vector2f size,
                                            sf::Color color) {
  sf::ConvexShape tile(3);
  tile.setPoint(0, sf::Vector2f(0, 0));
  tile.setPoint(1, sf::Vector2f(size.x, 0));
  tile.setPoint(2, sf::Vector2f(size.x / 2, size.y));
  tile.setPosition(position);
  tile.setFillColor(color);
  return tile;
}

sf::CircleShape SnakeAssets::get_fruit(sf::Vector2f position, sf::Vector2f size,
                                       sf::Color color) {
  sf::CircleShape tile(size.x / 2);
  tile.setPosition(position);
  tile.setFillColor(color);
  return tile;
}

std::unique_ptr<sf::Shape> SnakeAssets::shape_factory(
    TileDescriptors descriptor, sf::Vector2f position, sf::Vector2f size) {
  switch (descriptor) {
    case TileDescriptors::BOARD_TILE:
      return std::make_unique<sf::RectangleShape>(
          get_board_tile(position, size, sf::Color::Black));
    case TileDescriptors::SNAKE_BODY:
      return std::make_unique<sf::RectangleShape>(
          get_snake_body(position, size, sf::Color::Green));
    case TileDescriptors::SNAKE_HEAD:
      return std::make_unique<sf::ConvexShape>(
          get_snake_head(position, size, sf::Color::Yellow));
    case TileDescriptors::FRUIT:
      return std::make_unique<sf::CircleShape>(
          get_fruit(position, size, sf::Color::Red));
    default:
      return nullptr;
  }
}

sf::Font SnakeAssets::get_font() {
  sf::Font font;
  if (!font.loadFromFile(FONT_PATH)) {
    throw std::runtime_error("Could not load font");
  }
  return font;
}
