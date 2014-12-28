#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Constants.h"
#include "World.h"
#include <string>
#include <vector>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), ".physics", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    bool running = true;
    World world = World();
    while (running) {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                running = false;
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x <= WIDTH && mousePos.y >= 0 && mousePos.y <= HEIGHT) {
                bool positionTaken = false;
                for (auto e : world.pixels) { if (floor(e.x) == mousePos.x || floor(e.y) == mousePos.y) { positionTaken = true; }}
                if (!positionTaken) {
                    printf("PUTTING ELEMENT AT X: %i, Y: %i\n", mousePos.x, mousePos.y);
                    world.pixels.push_back(Element((double)mousePos.x, (double)mousePos.y, DIRT));
                }
            }
        }

        window.clear(sf::Color::Black);
        for(auto e : world.pixels) {
            sf::RectangleShape pix(sf::Vector2f(1,1));
            pix.setPosition((int)floor(e.x), (int)floor(e.y));
            pix.setFillColor(typeColors[e.type]);
            window.draw(pix);
            break;
        }
        window.display();
    }
    return 0;
}