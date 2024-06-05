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

class Game
{
    public:
        Game();
        ~Game();
        void run();
        void updateRender();
        void render();
    private:
        // TODO: functions for events, update, render
        sf::RenderWindow window;
        sf::Event event;
};

#endif