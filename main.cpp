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
    // Set up view
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Stock Tracker",
        sf::Style::Titlebar | sf::Style::Close
    );
    
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
        std::cout << ".";

    sf::Clock deltaClock;

    Graph graph;  // Initialize graph

    std::string inputText;  // Text input for file chooser
    
    // Line showing Y position of pointer
    sf::RectangleShape line(sf::Vector2f(800.0f, 1.0f));
    line.setFillColor(sf::Color(255, 255, 255, 128));
    
    // Setup for graph panning
    sf::Vector2i startingPos = {0, 0};
    sf::Vector2i defaultPos = {400, 300};
    
    bool wasDownLastFrame = false;  // Stores whether the mouse was held down last frame
    
    // Main loop
    while (window.isOpen()) {
        // Poll events
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);
            
            // Detect starting position of mouse click
            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    startingPos = sf::Mouse::getPosition(window);
                }
            }
            
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Drag and pan the screen
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.y > 100) {
                graph.offsetX = defaultPos.x + mousePos.x - startingPos.x;
                graph.offsetY = defaultPos.y + mousePos.y - startingPos.y;
                wasDownLastFrame = true;
            }
        } else {
            if (wasDownLastFrame) {
                defaultPos.x = graph.offsetX;
                defaultPos.y = graph.offsetY;
            }
            graph.offsetX = defaultPos.x;
            graph.offsetY = defaultPos.y;
            
            wasDownLastFrame = false;
        }
        
        // Position line for Y coordinate of pointer
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (mousePos.y > 100) {
            line.setPosition(sf::Vector2f(0.0f, mousePos.y));
        }
        
        // GUI
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
            graph.load(inputText);  // Load file from input
        ImGui::End();

        // Rendering
        window.clear(sf::Color::Black);
        graph.render(window);
        window.draw(line);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
