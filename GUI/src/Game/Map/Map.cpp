/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map
*/

#include "Map.hpp"

Map::Map(int width, int height, int windowSize) : width(width), height(height), windowSize(windowSize)
{
    // // Initialize random seed
    // srand(static_cast<unsigned>(time(0)));
    mapHeightInPixels = height * tileSize;
    mapWidthInPixels = width * tileSize;
    sf::Vector2f center((mapWidthInPixels - windowSize) / 2.0f, (mapHeightInPixels - windowSize) / 2.0f);
    view = sf::View(sf::FloatRect(center.x, center.y, windowSize, windowSize));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Tile tile = Tile(sf::Vector2i(tileSize - 1, tileSize - 1), sf::Vector2i(x * tileSize, y * tileSize), 0, 0, 0, 0, 0, 0, 0);
            sf::Color initialColor = generateRandomColor();
            tile.setFillColor(initialColor);
            tiles.push_back(tile);

            currentColors.push_back(initialColor);
            targetColors.push_back(generateRandomColor());
            phases.push_back(static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f);
        }
    }
}