#include "candle.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void Candle::render(sf::RenderWindow& window, int x, int y) {    
    bool down;  // Whether the candle went down
    
    // Set color depending on which direction the candle moved
    sf::Color color;
    if (open <= close) {
        color = sf::Color::Green;
        down = false;
    } else {
        color = sf::Color::Red;
        down = true;
    }
    
    // Get the height of the candles
    float extremeHeight = low - high;
    float mainHeight = close - open;
    
    // Set up shapes
    sf::RectangleShape extreme(sf::Vector2f(3.f, extremeHeight));
    extreme.setFillColor(color);
    extreme.setPosition(sf::Vector2f(x + 10.5, y + (close - low)));
    sf::RectangleShape main(sf::Vector2f(24.f, mainHeight));
    main.setFillColor(color);
    main.setPosition(sf::Vector2f(x, y));
    
    // Render
    window.draw(main);
    window.draw(extreme);
}
