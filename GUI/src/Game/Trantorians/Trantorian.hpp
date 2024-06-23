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
    #include <memory>
    #include "Tile.hpp"

/**
 * @brief Trantorian class
 * 
 */
class Trantorian
{
    public:
        /**
         * @brief Construct a new Trantorian object
         * 
         * @param id The id of the trantorian
         * @param teamName The name of the team
         * @param pos The position of the trantorian
         * @param direction The direction of the trantorian
         * @param level The level of the trantorian
         * @param teamNumber The number of the team
         */
        Trantorian(int id, std::string teamName = "", sf::Vector2i pos = sf::Vector2i(0, 0), int direction = 1, int level = 1, int teamNumber = 0);

        /**
         * @brief Destroy the Trantorian object
         * 
         */
        ~Trantorian() = default;

        /**
         * @brief Set the sprite of the trantorian
         * 
         */
        void setSprite();

        /**
         * @brief Draw the trantorian
         * 
         * @param window The window to draw the trantorian on
         */
        void draw(sf::RenderWindow &window);

        /**
         * @brief Set the inventory of the trantorian
         * 
         * @param q0 The quantity of food
         * @param q1 The quantity of linemate
         * @param q2 The quantity of deraumere
         * @param q3 The quantity of sibur
         * @param q4 The quantity of mendiane
         * @param q5 The quantity of phiras
         * @param q6 The quantity of thystame
         */
        void setInventory(int q0, int q1, int q2, int q3, int q4, int q5, int q6);

        /**
         * @brief Set the position of the trantorian
         * 
         * @param pos The position of the trantorian
         */
        void setPos(sf::Vector2i pos);

        /**
         * @brief Get the position of the trantorian
         * 
         * @param pos The position of the trantorian
         */
        sf::Vector2i getPos();

        /**
         * @brief Set the level of the trantorian
         * 
         * @param level The level of the trantorian
         */
        void setLevel(int level);

        /**
         * @brief Collect an item from a tile
         * 
         * @param tile The tile to collect the item from
         * @param nb The number of the item to collect
         */
        void collectItem(Tile &tile, int nb);

        /**
         * @brief Drop an item on a tile
         * 
         * @param tile The tile to drop the item on
         * @param nb The number of the item to drop
         */
        void dropItem(Tile &tile, int nb);

        /**
         * @brief Animate the trantorian
         * 
         * @param time The time to animate the trantorian
         */
        void animate(float time);

        /**
         * @brief Check if the trantorian is elevating
         * 
         * @return true If the trantorian is elevating
         * @return false If the trantorian is not elevating
         */
        bool isElevating();

        /**
         * @brief Set the elevating of the trantorian
         * 
         * @param isElevating If the trantorian is elevating
         */
        void setElevating(bool isElevating);

        /**
         * @brief Get the team name of the trantorian
         * 
         * @return std::string The team name of the trantorian
         */
        std::string getTeamName() { return teamName; }

        /**
         * @brief Get the level of the trantorian
         * 
         * @return int The level of the trantorian
         */
        int getLevel() { return level; }

    // Identification
    private:
        int id;
        std::string teamName;
        int teamNumber;

    // Graphics
    private:
        sf::Sprite sprite;
        sf::Texture texture;

    // Game data
    private:
        sf::Vector2i pos;
        int *inventory;
        int level;
        int direction;
        bool elevation = false;

    // Animation
    private:
        int currentFrame;
        int frameCount;
        float frameDuration;
        float elapsedTime;
};

#endif
