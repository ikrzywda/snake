#include <SFML/Graphics.hpp>

#include "game_controller.hpp"

int main() {
  if (!ScoreService::init()) {
    std::cout << "Failed to initialize score service" << std::endl;
    return 1;
  }

  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "Snake");
  GameController game_controller(window);
  // game_controller.start_game();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    game_controller.tick();
  }
  return 0;
}
