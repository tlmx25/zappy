/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** chatbox
*/

#include "Chatbox.hpp"

Chatbox::Chatbox(float width, float height) : width(width), height(height), isOpen(false)
{
    font.loadFromFile("GUI/src/Assets/arial.ttf");

    header.setSize(sf::Vector2f(width, 30));
    header.setFillColor(sf::Color::Blue);
    header.setPosition(0, 0);

    headerText.setFont(font);
    headerText.setString("Chatbox");
    headerText.setCharacterSize(20);
    headerText.setFillColor(sf::Color::White);
    headerText.setPosition(10, 2);

    toggleButton.setSize(sf::Vector2f(50, 30));
    toggleButton.setFillColor(sf::Color::Red);
    toggleButton.setPosition(width - 50, 0);

    toggleButtonText.setFont(font);
    toggleButtonText.setCharacterSize(15);
    toggleButtonText.setFillColor(sf::Color::White);
    toggleButtonText.setPosition(width - 45, 5);

    background.setSize(sf::Vector2f(width, height - 30));
    background.setFillColor(sf::Color::White);
    background.setPosition(0, 30);

    updateToggleButton();
    setPosition(sf::Vector2f(0, 0));
}

void Chatbox::addMessage(std::string &team, std::string &id, std::string &message)
{
    sf::RectangleShape messageRect(sf::Vector2f(width - 20, 50));
    messageRect.setFillColor(sf::Color::White);
    messageRect.setOutlineColor(sf::Color::Black);
    messageRect.setOutlineThickness(1);
    messageRect.setPosition(10, 40 + messageTexts.size() * 60);

    sf::Text text;
    text.setFont(font);
    // text.setString("Player " + id + "(" + team + "): \n" + message);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);

    std::string fullMessage = "Player " + id + "(" + team + "): \n" + message;
    text.setString(fullMessage);
    float textWidth = text.getGlobalBounds().width;
    float maxTextWidth = width - 40;

    if (textWidth > maxTextWidth) {
        std::string cutMessage = fullMessage;
        while (text.getLocalBounds().width > maxTextWidth && cutMessage.length() > 3) {
            cutMessage = cutMessage.substr(0, cutMessage.length() - 4) + "...";
            text.setString(cutMessage);
        }
    }

    text.setPosition(15, 45 + messageTexts.size() * 60);

    messageTexts.push_back(text);
    messages.push_back(messageRect);
}

void Chatbox::render(sf::RenderWindow &window)
{
    window.draw(header);
    window.draw(headerText);
    window.draw(toggleButton);
    window.draw(toggleButtonText);

    if (isOpen) {
        window.draw(background);
        for (auto &message : messages) {
            window.draw(message);
        }
        for (auto &messageText : messageTexts) {
            window.draw(messageText);
        }
    }
}

void Chatbox::handleEvents(sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (toggleButton.getGlobalBounds().contains(mousePos)) {
            toggleChatbox();
        }
        sf::sleep(sf::milliseconds(200));
    }
}

void Chatbox::toggleChatbox()
{
    isOpen = !isOpen;
    updateToggleButton();
}

void Chatbox::updateToggleButton()
{
    if (isOpen) {
        toggleButtonText.setString("Close");
        toggleButton.setFillColor(sf::Color::Red);
    } else {
        toggleButtonText.setString("Open");
        toggleButton.setFillColor(sf::Color::Blue);
    }
}

void Chatbox::setPosition(sf::Vector2f pos)
{
    position = pos;
    // updatePositions();
}

void Chatbox::updatePositions()
{
    header.setPosition(position);
    headerText.setPosition(position.x, position.y);
    toggleButton.setPosition(position.x + width - 50, position.y);
    toggleButtonText.setPosition(position.x + width - 45, position.y + 5);
    background.setPosition(position.x, position.y + 30);
    for (size_t i = 0; i < messages.size(); ++i) {
        messages[i].setPosition(10, 40 + i * 60 + position.y);
        messageTexts[i].setPosition(15, 45 + i * 60 + position.y);
    }
}