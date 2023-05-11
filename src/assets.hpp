#ifndef ASSETS_HPP
#define ASSETS_HPP


#include <SFML/Graphics.hpp>
#include <map>

enum class TileDescriptors {
    BOARD_TILE,
    SNAKE_BODY,
    SNAKE_HEAD,
    FRUIT
};

struct Tileset {
    static sf::RectangleShape get_board_tile(sf::Vector2f position, sf::Vector2f size, sf::Color color);
    static sf::RectangleShape get_snake_body(sf::Vector2f position, sf::Vector2f size, sf::Color color);
    static sf::ConvexShape get_snake_head(sf::Vector2f position, sf::Vector2f size, sf::Color color);
    static sf::CircleShape get_fruit(sf::Vector2f position, float radius, sf::Color color);
};

static std::map<TileDescriptors, std::function<sf::Shape(sf::Vector2f, sf::Vector2f, sf::Color)>> tileset = {
    {TileDescriptors::BOARD_TILE, Tileset::get_board_tile},
    {TileDescriptors::SNAKE_BODY, Tileset::get_snake_body},
    {TileDescriptors::SNAKE_HEAD, Tileset::get_snake_head},
    {TileDescriptors::FRUIT, Tileset::get_fruit}
};

#endif
