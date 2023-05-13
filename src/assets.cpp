#include "assets.hpp"

sf::Sprite SnakeAssets::get_board_tile(sf::Texture& texture,
                                       sf::Vector2f position,
                                       sf::Vector2f size) {
  sf::Sprite tile(texture);
  tile.setPosition(position);
  tile.setScale(size.x / tile.getLocalBounds().width,
                size.y / tile.getLocalBounds().height);
  return tile;
}

sf::Sprite SnakeAssets::get_snake_body(sf::Texture& texture,
                                       sf::Vector2f position,
                                       sf::Vector2f size) {
  sf::Sprite tile(texture);
  tile.setPosition(position);
  tile.setScale(size.x / tile.getLocalBounds().width,
                size.y / tile.getLocalBounds().height);
  return tile;
}

sf::Sprite SnakeAssets::get_snake_head(sf::Texture& texture,
                                       sf::Vector2f position,
                                       sf::Vector2f size) {
  sf::Sprite tile(texture);
  tile.setPosition(position);
  tile.setScale(size.x / tile.getLocalBounds().width,
                size.y / tile.getLocalBounds().height);
  return tile;
}

sf::Sprite SnakeAssets::get_fruit(sf::Texture& texture, sf::Vector2f position,
                                  sf::Vector2f size) {
  sf::Sprite tile(texture);
  tile.setPosition(position);
  tile.setScale(size.x / tile.getLocalBounds().width,
                size.y / tile.getLocalBounds().height);
  return tile;
}

std::optional<sf::Sprite> SnakeAssets::sprite_factory(
    TileDescriptors descriptor, sf::Texture& texture, sf::Vector2f position,
    sf::Vector2f size) {
  switch (descriptor) {
    case TileDescriptors::BOARD_TILE:
      return std::make_optional<sf::Sprite>(
          get_board_tile(texture, position, size));
    case TileDescriptors::SNAKE_BODY:
      return std::make_optional<sf::Sprite>(
          get_snake_body(texture, position, size));
    case TileDescriptors::SNAKE_HEAD:
      return std::make_optional<sf::Sprite>(
          get_snake_head(texture, position, size));
    case TileDescriptors::FRUIT:
      return std::make_optional<sf::Sprite>(get_fruit(texture, position, size));
    default:
      return std::nullopt;
  }
}

sf::Font SnakeAssets::get_font() {
  sf::Font font;
  font.loadFromFile("assets/arial.ttf");
  return font;
}
