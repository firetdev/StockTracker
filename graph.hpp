#pragma once

#include "candle.hpp"
#include <vector>

class Graph {
public:
    std::vector<Candle> candles;
    float offsetX;
    float offsetY;
    
    Graph() : offsetX(400), offsetY(300) {}
    
    void render(sf::RenderWindow&);
    void load(std::vector<Candle>);
};
