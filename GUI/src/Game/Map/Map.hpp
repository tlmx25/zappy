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

/**
 * @brief Map class
 * 
 */
class Map
{
    public:
        /**
         * @brief Construct a new Map object
         * 
         * @param width The width of the map
         * @param height The height of the map
         * @param windowSize The size of the window
         */
        Map(int width, int height, int windowSize);

        /**
         * @brief Destroy the Map object
         * 
         */
        ~Map() = default;

        /**
         * @brief Generate a random color
         * 
         * @return sf::Color The generated color
         */
        sf::Color generateRandomColor();

        /**
         * @brief Interpolate between two colors
         * 
         * @param start The start color
         * @param end The end color
         * @param t The time
         * @return sf::Color The interpolated color
         */
        sf::Color interpolateColor(sf::Color start, sf::Color end, float t);

        /**
         * @brief Update the colors of the tiles
         * 
         * @param time The time
         */
        void updateColors(float time);

        /**
         * @brief Render the tiles
         * 
         * @param window The window to render the tiles on
         */
        void renderTiles(sf::RenderWindow& window);

        /**
         * @brief Get the tiles
         * 
         * @return std::vector<Tile>& The tiles
         */
        std::vector<Tile>& getTiles();

        
        sf::View view;
        int mapWidthInPixels;
        int mapHeightInPixels;
    private:
        int width;
        int height;
        int tileSize = 90;
        int windowSize = 1200;
        float colorChangeSpeed = 0.60f;
        float lastColorChange = 0.0f;
        sf::Color lightColor = sf::Color(36, 76, 156);
        sf::Color darkColor = sf::Color(1, 39, 117);
        std::vector<Tile> tiles = std::vector<Tile>(width * height);
        std::vector<sf::Color> currentColors = std::vector<sf::Color>(width * height);
        std::vector<sf::Color> targetColors = std::vector<sf::Color>(width * height);
        std::vector<float> phases = std::vector<float>(width * height);
};

#endif