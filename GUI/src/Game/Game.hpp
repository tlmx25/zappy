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

class Game
{
    public:
        Game(int x, int y);
        ~Game();
        void run();
        void handleEvents();
        void render();
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