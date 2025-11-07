#pragma once

#include "candle.hpp"
#include <string>

class Graph {
public:
    std::vector<Candle> candles;
    float offsetX;
    float offsetY;
    float scale;
    
    Graph() : offsetX(400), offsetY(300), scale(10) {}
    
    void render(sf::RenderWindow&);
    void load(std::string);
};
