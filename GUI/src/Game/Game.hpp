/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** game
*/

#ifndef GAME_HPP
    #define GAME_HPP
    #include <iostream>
    #include <string>
    #include <algorithm>
    #include <vector>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include "Map.hpp"
    #include "Trantorian.hpp"
    #include "Chatbox.hpp"

/**
 *  
 * @brief Game class
 * 
 */
class Game
{
    public:
        /**
         * @brief Construct a new Game object
         * 
         * @param x The width of the map
         * @param y The height of the map
         */
        Game(int x, int y);

        /**
         * @brief Destroy the Game object
         * 
         */
        ~Game();

        /**
         * @brief Run the game
         * 
         */
        void run();

        /**
         * @brief Handle the events
         * 
         */
        void handleEvents();

        /**
         * @brief Update the game
         * 
         */
        void render();

        /**
         * @brief Get the team number
         * 
         * @return int The team number
         */
        int getTeamNumber(std::string teamName);

        /**
         * @brief Get the window
         * 
         * @return sf::RenderWindow the window
         */
        sf::RenderWindow& getWindow();

        /**
         * @brief Get the map
         * 
         * @return Map the map
         */
        Map& getMap();

        /**
         * @brief Get the map
         * 
         * @return Map the map
         */
        std::map<std::string, std::shared_ptr<Trantorian>>& getTrantorians();

        /**
         * @brief Add if new team box
         * 
         */
        void checkTeamBoxes();

        /**
         * @brief Display the team boxes
         * 
         */
        void displayTeamBoxes();

        /**
         * @brief Get the number of elevated players
         * 
         * @param teamName The name of the team
         * @return int The number of elevated players
         */
        int getNbElevatedPlayers(std::string teamName);

        /**
         * @brief Get the number of elevated players
         * 
         */
        Chatbox& getChatbox();

    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Clock clock;
        float currentZoom = 1.0f;
        Map map;
        Chatbox chatbox;
        std::map<std::string, std::shared_ptr<Trantorian>> trantorians;
        sf::Music music;
        std::map<std::string, int> teamToNumber;
        int nextTeamNumber = 0;
        std::vector<std::string> teamNames;

        // Team display info
        sf::Font font;
        sf::Vector2f teamBoxesPos;
        std::vector<sf::RectangleShape> teamBoxes;
        std::vector<sf::Text> teamTexts;
};

#endif