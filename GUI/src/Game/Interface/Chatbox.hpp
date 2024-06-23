/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** chatbox
*/

#ifndef CHATBOX_HPP
    #define CHATBOX_HPP
    #include <SFML/Graphics.hpp>
    #include <vector>
    #include <string>
    #include <iostream>
    #include <sstream>

class Chatbox
{
    public:
        Chatbox(float width = 240, float height = 480, sf::Vector2f windowSize = sf::Vector2f(960, 960));
        ~Chatbox() = default;

        void addMessage(std::string& team, std::string& id, std::string& message);
        void render(sf::RenderWindow& window);
        void handleEvents(sf::Event& event);
        void toggleChatbox();
        void updateToggleButton();
        void setPosition(sf::Vector2f pos);
        void updatePositions();
    private:
        float width;
        float height;
        bool isOpen;
        int maxMessages;
        sf::Vector2f position;
        sf::Vector2f windowSize;
        sf::RectangleShape header;
        sf::RectangleShape background;
        sf::RectangleShape toggleButton;
        sf::Font font;
        sf::Text headerText;
        sf::Text toggleButtonText;
        std::vector<sf::Text> messageTexts;
        std::vector<sf::RectangleShape> messages;
};

#endif