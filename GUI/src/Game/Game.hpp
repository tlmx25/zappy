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
    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Clock clock;
        Map map;
        std::vector<Trantorian> trantorians;
};

#endif