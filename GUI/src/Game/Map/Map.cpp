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
            tile.setPos(sf::Vector2i(x * tileSize, y * tileSize));
            sf::Color initialColor = generateRandomColor();
            tile.setFillColor(initialColor);
            tiles.push_back(tile);

            currentColors.push_back(initialColor);
            targetColors.push_back(generateRandomColor());
            phases.push_back(static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f);
        }
    }
}

sf::Color Map::generateRandomColor()
{
    float t = static_cast<float>(rand()) / RAND_MAX; // Random float between 0 and 1
    return interpolateColor(darkColor, lightColor, t);
}

void Map::renderTiles(sf::RenderWindow &window)
{
    for (auto &tile : tiles) {
        window.draw(tile.getShape());
        tile.draw(window);
    }
}

void Map::updateColors(float time)
{
    if (time - lastColorChange > colorChangeSpeed) {
        for (size_t i = 0; i < targetColors.size(); ++i) {
            targetColors[i] = generateRandomColor();
        }
        lastColorChange = time;
    }

    for (size_t i = 0; i < tiles.size(); ++i) {
        float t = (std::sin(time + phases[i]) + 1) / 2;
        sf ::Color newColor = interpolateColor(currentColors[i], targetColors[i], t);
        tiles[i].setFillColor(newColor);
    }
}

sf::Color Map::interpolateColor(sf::Color start, sf::Color end, float t)
{
    return sf::Color(
        static_cast<sf::Uint8>(start.r + t * (end.r - start.r)),
        static_cast<sf::Uint8>(start.g + t * (end.g - start.g)),
        static_cast<sf::Uint8>(start.b + t * (end.b - start.b))
    );
}

std::vector<Tile>& Map::getTiles()
{
    return tiles;
}