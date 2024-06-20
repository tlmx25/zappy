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

/**
 * @brief Tile class
*/
class Tile
{
    public:
        /**
         * @brief Construct a new Tile object
         * 
         * @param size The size of the tile
         * @param pos The position of the tile
         * @param q0 The quantity of food
         * @param q1 The quantity of linemate
         * @param q2 The quantity of deraumere
         * @param q3 The quantity of sibur
         * @param q4 The quantity of mendiane
         * @param q5 The quantity of phiras
         * @param q6 The quantity of thystame
         */
        Tile(sf::Vector2i size = sf::Vector2i(90,90), sf::Vector2i pos = sf::Vector2i(0,0), int q0 = 0, int q1 = 0, int q2 = 0, int q3 = 0, int q4 = 0, int q5 = 0, int q6 = 0);

        /**
         * @brief Destroy the Tile object
         * 
         */
        ~Tile() = default;

        /**
         * @brief Add an item to the tile
         * 
         * @param item The item being the index or nb of the item (ex: 0 for food, 1 for linemate, etc..)
         */
        void addItem(int item);

        /**
         * @brief Remove an item from the tile
         * 
         * @param item The item being the index or nb of the item (ex: 0 for food, 1 for linemate, etc..)
         */
        void removeItem(int item);

        /**
         * @brief Get the quantity of an item
         * 
         * @param item The item being the index or nb of the item (ex: 0 for food, 1 for linemate, etc..)
         * @return int The quantity of the item
         */
        int getItemsQuantity(int item);

        /**
         * @brief Set the quantity of all items
         * 
         * @param q0 The quantity of food
         * @param q1 The quantity of linemate
         * @param q2 The quantity of deraumere
         * @param q3 The quantity of sibur
         * @param q4 The quantity of mendiane
         * @param q5 The quantity of phiras
         * @param q6 The quantity of thystame
         * @param q7 The quantity of the egg
         */
        void setAllItemsQuantity(int q0, int q1, int q2, int q3, int q4, int q5, int q6, int q7);

        /**
         * @brief Set the quantity of an item
         * 
         * @param item The item being the index or nb of the item (ex: 0 for food, 1 for linemate, etc..)
         * @param quantity The quantity of the item
         */
        void setItemQuantity(int item, int quantity);

        /**
         * @brief Get the position of the tile
         * 
         * @return sf::Vector2i The position of the tile
         */
        sf::Vector2i getPos();

        /**
         * @brief Get the shape of the tile
         * 
         * @return sf::RectangleShape The shape of the tile
         */
        sf::RectangleShape getShape();

        /**
         * @brief Set the fill color of the tile
         * 
         * @param color The color to set
         */
        void setFillColor(sf::Color color);

        /**
         * @brief Set the position of the tile
         * 
         * @param pos The position to set
         */
        void setPos(sf::Vector2i pos);

        /**
         * @brief Load the sprites
         * 
         */
        void load_sprites();

        /**
         * @brief Draw the tile
         * 
         * @param window The window to draw the tile on
         */
        void draw(sf::RenderWindow &window);
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
        int q7; // the egg
        std::map<std::string, std::shared_ptr<sf::Texture>> textures;
        std::map<std::string, std::shared_ptr<sf::Sprite>> items;
};

#endif