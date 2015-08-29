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

        //placing pixels
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 0 && mousePos.x <= WIDTH && mousePos.y >= 0 && mousePos.y <= HEIGHT) {
                bool positionTaken = false;
                for (auto e : world.pixels) {
                    if (e != nullptr) {
                        if (floor(e->x) == mousePos.x || floor(e->y) == mousePos.y) { //if there's not a pixel under your cursor
                            positionTaken = true;
                        }
                    }
                }
                if (!positionTaken) {
                    printf("putting element at X: %i, Y: %i\n", mousePos.x, mousePos.y);
                    Element currentPixel = Element((double)mousePos.x, (double)mousePos.y, DIRT);
                    world.placePixel(&currentPixel);
                }
            }
        }

        //render/update loop
        window.clear(sf::Color::Black);
        for(size_t pixelIndex = 0; pixelIndex < WORLD_SIZE; ++pixelIndex) {
            if (world.pixels[pixelIndex] != nullptr) {
                Element currentPixel = *world.pixels[pixelIndex];
                printf("drawing pixel X: %i, Y: %i, MAT: %i\n", currentPixel.x, currentPixel.y, currentPixel.type);
                //updating
                //e.tick(world.pixels);
                //currentPixelPointer->y += 1;

                //rendering
                sf::RectangleShape pix(sf::Vector2f(1,1));
                pix.setPosition(floor(currentPixel.x), floor(currentPixel.y));
                pix.setFillColor(typeColors[currentPixel.type]);
                window.draw(pix);
            }
        }
        window.display();
    }
    return 0;
}
