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

class Trantorian
{
    public:
        Trantorian(int id, std::string teamName = "", sf::Vector2i pos = sf::Vector2i(0, 0), int direction = 1, int level = 1, int teamNumber = 0);
        ~Trantorian() = default;
        void setSprite();
        void draw(sf::RenderWindow &window);
        void setInventory(int q0, int q1, int q2, int q3, int q4, int q5, int q6);
        void setPos(sf::Vector2i pos);
        void setLevel(int level);
        void collectItem(std::shared_ptr<Tile> &tile, int nb);
        void dropItem(std::shared_ptr<Tile> &tile, int nb);
        void animate(float time);
        bool isElevating();
        void setElevating(bool isElevating);

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
        int currentFrame;   // Current frame index
        int frameCount;     // Number of frames in the animation
        float frameDuration; // Duration of each frame in seconds
        float elapsedTime;  // Time elapsed since last frame change
};

#endif
