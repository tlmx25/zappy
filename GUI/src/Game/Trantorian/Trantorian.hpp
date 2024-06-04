/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** trantorian
*/
#ifndef TRANTORIAN_HPP
    #define TRANTORIAN_HPP
    #include <iostream>
    #include <string>
    #include <algorithm>
    #include <vector>
    #include <SFML/Graphics.hpp>

class Trantorian
{
    public:
        Trantorian(int id, std::string teamName, int x, int y);
        ~Trantorian() = default;
        void move(int x, int y);
        void setSprite(sf::Sprite sprite);
        void draw(sf::RenderWindow &window);
        bool updateLife(int timeUnits);
        void updateInventory(std::string item);

    // Identification
    private:
        int id;
        std::string teamName;

    // Graphics
    private:
        sf::Sprite sprite;

    // Game data
    private:
        std::vector<std::string> inventory;
        int lifeTimeLeft;
        int level;
        int posX;
        int posY;
        int direction;
};

#endif
