#include "graph.hpp"

void Graph::render(sf::RenderWindow& window) {
    int extraOffset = 0;  // Offset so each candle will begin where the last one ended
    for (int i = static_cast<int>(candles.size()) - 1; i >= 0; i--) {
        candles[i].render(window, offsetX - (((candles.size() - 1) - i) * 26), offsetY + extraOffset);
        extraOffset += (offsetY + (candles[i].close - candles[i].open)) - offsetY;
    }
}

void Graph::load(std::vector<Candle> bars) {
    candles = bars;  // Load candles from a vector
}
