#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <optional>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "candle.hpp"
#include "graph.hpp"

int main() {
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Stock Tracker",
        sf::Style::Titlebar | sf::Style::Close
    );
    
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
        std::cout << ".";

    sf::Clock deltaClock;

    std::vector<Candle> candles = {Candle(140, 80, 160, 0), Candle(80, 100, 110, 60), Candle(100, 180, 240, 50), Candle(180, 90, 200, 60)};
    Graph graph;
    graph.load(candles);
    //Candle myCandle(140, 80, 160, 0);  // Example candle

    bool buttonPressed = false;
    std::string inputText;

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        char buffer[128];
        strncpy(buffer, inputText.c_str(), sizeof(buffer));
        buffer[sizeof(buffer)-1] = '\0';
        
        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBackground |
            ImGuiWindowFlags_NoScrollbar;

        ImGui::SetNextWindowPos(ImVec2(
            ImGui::GetIO().DisplaySize.x - 270, // X: screen width - window width
            20                                  // Y: offset from top
        ));
        
        ImGui::SetNextWindowSize(ImVec2(230, 150));
        
        ImGui::Begin("##NoTitle", nullptr, window_flags);
        ImGui::Text("Input file: ");
        ImGui::SameLine();
        if (ImGui::InputText("##Input file", buffer, sizeof(buffer)))
            inputText = buffer;
        if (ImGui::Button("Load File"))
            buttonPressed = !buttonPressed;
        ImGui::End();

        window.clear(sf::Color::Black);
        graph.render(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
