#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <regex>

void Graph::render(sf::RenderWindow& window) {
    int extraOffset = 0;  // Offset so each candle will begin where the last one ended
    for (int i = static_cast<int>(candles.size()) - 1; i >= 0; i--) {
        candles[i].render(window, offsetX - (((candles.size() - 1) - i) * 26), offsetY + extraOffset);
        extraOffset += (offsetY + (candles[i].close - candles[i].open)) - offsetY;
    }
}

void Graph::load(std::string dataFile) {
    std::vector<Candle> bars;  // Holds bars while we're working
    
    // Open and read file containing data
    std::ifstream file(dataFile);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << dataFile << std::endl;
        return;
    }
    
    std::string line;

    while (std::getline(file, line)) {
        // Extract data from line
        std::vector<std::string> data;
        
        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);
        
        std::regex pattern(R"((\d+),(\d+),(\d+),(\d+))");
        std::smatch match;
        
        if (std::regex_match(line, match, pattern)) {
            data.push_back(match[1].str());
            data.push_back(match[2].str());
            data.push_back(match[3].str());
            data.push_back(match[4].str());
        } else {
            std::cerr << "Invalid input format\n";
        }
        
        bars.push_back(Candle(std::stof(data[0]), std::stof(data[1]), std::stof(data[2]), std::stof(data[3])));
    }

    file.close();
    
    candles = bars;  // Load candles from a vector
}
