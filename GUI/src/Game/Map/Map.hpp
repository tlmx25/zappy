/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map
*/

#ifndef MAP_HPP
    #define MAP_HPP
    #include <iostream>
    #include <string>
    #include <algorithm>
    #include <vector>
    #include <SFML/Graphics.hpp>
    #include <cmath>
    #include "Tile.hpp"

// TODO: Objects sprites handled here: create, load etc in constructor

class Map
{
    public:
        Map(int width, int height, int windowSize);
        ~Map() = default;
        sf::Color generateRandomColor();
        sf::Color interpolateColor(sf::Color start, sf::Color end, float t);
        void updateColors(float time);
        void renderTiles(sf::RenderWindow& window);
        sf::View view;
        int mapWidthInPixels;
        int mapHeightInPixels;
    private:
        int width;
        int height;
        int tileSize = 80;
        int windowSize = 1200;
        float colorChangeSpeed = 1.0f;
        float lastColorChange = 0.0f;
        sf::Color lightColor = sf::Color(36, 76, 156);
        sf::Color darkColor = sf::Color(1, 39, 117);
        std::vector<Tile> tiles = std::vector<Tile>(width * height);
        std::vector<sf::Color> currentColors = std::vector<sf::Color>(width * height);
        std::vector<sf::Color> targetColors = std::vector<sf::Color>(width * height);
        std::vector<float> phases = std::vector<float>(width * height);
};

#endif