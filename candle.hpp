#pragma once

#include <SFML/Graphics.hpp>

class Candle {
public:
    float open;
    float close;
    float high;
    float low;

    Candle(float open, float close, float high, float low) : open(open), close(close), high(high), low(low) {}
    
    void render(sf::RenderWindow&, int, int);
};
