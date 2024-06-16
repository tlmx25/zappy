/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tile
*/

#ifndef TILE_HPP
    #define TILE_HPP
    #include <iostream>
    #include <string>
    #include <algorithm>
    #include <vector>
    #include <SFML/Graphics.hpp>
    #include <memory>

class Tile
{
    public:
        Tile(sf::Vector2i size = sf::Vector2i(80,80), sf::Vector2i pos = sf::Vector2i(0,0), int q0 = 0, int q1 = 0, int q2 = 0, int q3 = 0, int q4 = 0, int q5 = 0, int q6 = 0);
        ~Tile() = default;
        void addItem(int item);
        void removeItem(int item);
        int getItemsQuantity(int item);
        void setAllItemsQuantity(int q0, int q1, int q2, int q3, int q4, int q5, int q6);
        void setItemQuantity(int item, int quantity);
        sf::Vector2i getPos();
        sf::RectangleShape getShape();
        void setFillColor(sf::Color color);
        void setPos(sf::Vector2i pos);
        void load_sprites();
        void draw(sf::RenderWindow &window);
        // update tile ??
    private:
        sf::Vector2i pos;
        sf::Vector2i size;
        sf::RectangleShape shape;
        int tileSize = 90;
        int qAll;
        int q0;
        int q1;
        int q2;
        int q3;
        int q4;
        int q5;
        int q6;
        std::map<std::string, std::shared_ptr<sf::Texture>> textures;
        std::map<std::string, std::shared_ptr<sf::Sprite>> items;
};

#endif