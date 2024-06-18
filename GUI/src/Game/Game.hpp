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
    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Clock clock;
        float currentZoom = 1.0f;
        Map map;
        std::map<std::string, std::shared_ptr<Trantorian>> trantorians;
        sf::Music music;
        std::map<std::string, int> teamToNumber;
        int nextTeamNumber = 0;
};

#endif