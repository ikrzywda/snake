#include "game_view.hpp"

void GameView::draw_game(sf::RenderWindow &window, GameModel &game_model) {
  window.clear(sf::Color::Black);

  auto board = game_model.board;
  auto snake = board.snake;
  auto food = board.food_position;

  sf::RectangleShape rectangle(sf::Vector2f(10, 10));
  rectangle.setFillColor(sf::Color::White);

  for (auto &segment : snake.body) {
    rectangle.setPosition(
        sf::Vector2f(segment.first * 10, segment.second * 10));
    window.draw(rectangle);
  }

  rectangle.setFillColor(sf::Color::Red);
  rectangle.setPosition(sf::Vector2f(food.first * 10, food.second * 10));
  window.draw(rectangle);

  window.display();
}

static void draw_menu(sf::RenderWindow &window) {
  // TODO: Implement -- click to start / quit
}
