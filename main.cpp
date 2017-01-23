#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>

int main() {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 640;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Search Algorithms");
    sf::CircleShape circle(10.f);
    circle.setPosition({10,10});
    circle.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
                case sf::Event::KeyReleased:
                    break;
                case sf::Event::MouseButtonPressed:
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
            }
        }
        window.clear();
        window.draw(circle);
        window.display();
    }
    return 0;
}
