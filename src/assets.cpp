#include "assets.hpp"

// generated with gpt 3.5

sf::RectangleShape Tileset::get_board_tile(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
    sf::RectangleShape tile(size);
    tile.setPosition(position);
    tile.setFillColor(color);
    return tile;
}


sf::RectangleShape Tileset::get_snake_body(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
    sf::RectangleShape tile(size);
    tile.setPosition(position);
    tile.setFillColor(color);
    return tile;
}


sf::ConvexShape Tileset::get_snake_head(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
    sf::ConvexShape tile(3);
    tile.setPoint(0, sf::Vector2f(0, 0));
    tile.setPoint(1, sf::Vector2f(size.x, 0));
    tile.setPoint(2, sf::Vector2f(size.x / 2, size.y));
    tile.setPosition(position);
    tile.setFillColor(color);
    return tile;
}


sf::CircleShape Tileset::get_fruit(sf::Vector2f position, float radius, sf::Color color) {
    sf::CircleShape tile(radius);
    tile.setPosition(position);
    tile.setFillColor(color);
    return tile;
}
