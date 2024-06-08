/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

// #include "stdio.h"

// int main(int ac, char **av)
// {
//     printf("Hello, World!\n");
//     return (0);

//     // try {
//     //     // init all
//     //     // run
//     // } catch () {
//     //     // handle error
//     // }

//     // // destroy all
//     // return (0);
// }

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <ctime>

// Function to interpolate between two colors
sf::Color interpolateColor(sf::Color start, sf::Color end, float t) {
    return sf::Color(
        static_cast<sf::Uint8>(start.r + t * (end.r - start.r)),
        static_cast<sf::Uint8>(start.g + t * (end.g - start.g)),
        static_cast<sf::Uint8>(start.b + t * (end.b - start.b))
    );
}

// Function to generate a random color within the given range
sf::Color generateRandomColorInRange(sf::Color lightColor, sf::Color darkColor) {
    float t = static_cast<float>(rand()) / RAND_MAX; // Random float between 0 and 1
    return interpolateColor(darkColor, lightColor, t);
}

int main() {

    const int mapWidth = 30;
    const int mapHeight = 30;
    const float tileSize = 80;
    const int windowSize = 1200;

    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    // Lightest and darkest colors
    sf::Color lightColor(36, 76, 156); // #244c9c
    sf::Color darkColor(1, 39, 117);   // #012775

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Blinking Tiles with Movable Camera");
    window.setFramerateLimit(60);

    int mapWidthInPixels = mapWidth * tileSize;
    int mapHeightInPixels = mapHeight * tileSize;

    sf::Vector2f initialViewCenter((mapWidthInPixels - windowSize) / 2.0f, (mapHeightInPixels - windowSize) / 2.0f);
    sf::View mapView(sf::FloatRect(initialViewCenter.x, initialViewCenter.y, windowSize, windowSize));

    std::vector<sf::RectangleShape> tiles(mapWidth * mapHeight);
    std::vector<sf::Color> currentColors(mapWidth * mapHeight);
    std::vector<sf::Color> targetColors(mapWidth * mapHeight);
    std::vector<float> phases(mapWidth * mapHeight);

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            sf::RectangleShape tile(sf::Vector2f(tileSize - 1, tileSize - 1));
            tile.setPosition(x * tileSize, y * tileSize);

            sf::Color initialColor = generateRandomColorInRange(lightColor, darkColor);
            tile.setFillColor(initialColor);

            tiles[y * mapWidth + x] = tile;
            currentColors[y * mapWidth + x] = initialColor;
            targetColors[y * mapWidth + x] = generateRandomColorInRange(lightColor, darkColor); // Initial target color
            phases[y * mapWidth + x] = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f; // Random phase for each tile
        }
    }

    sf::Clock clock;
    float colorChangeInterval = 1.0f; // Change color every second
    float lastColorChangeTime = 0.0f;

    // Example button
    sf::RectangleShape button(sf::Vector2f(150, 50));
    button.setFillColor(sf::Color::White);
    button.setPosition(25, windowSize - 75); // Position at the bottom left of the window

    sf::Font font;
    if (!font.loadFromFile("GUI/src/Assets/arial.ttf")) {
        return -1;
    }

    sf::Text buttonText("Button", font, 20);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(button.getPosition().x + 25, button.getPosition().y + 10);

    // Create a view for the map

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle keyboard input for moving the view
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(mapView.getCenter().x - mapView.getSize().x / 2.0f <= 0)) {
            mapView.move(-5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(mapView.getCenter().x + mapView.getSize().x / 2.0f >= mapWidthInPixels)) {
            mapView.move(5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !(mapView.getCenter().y - mapView.getSize().y / 2.0f <= 0)) {
                mapView.move(0, -5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !(mapView.getCenter().y + mapView.getSize().y / 2.0f >= mapHeightInPixels)) {
            mapView.move(0, 5);
        }

        // Constrain the view within the map boundaries
        sf::Vector2f center = mapView.getCenter();
        sf::Vector2f size = mapView.getSize();

        float halfWidth = size.x / 2.0f;
        float halfHeight = size.y / 2.0f;

        float time = clock.getElapsedTime().asSeconds();

        // Change target colors every second
        if (time - lastColorChangeTime >= colorChangeInterval) {
            for (size_t i = 0; i < targetColors.size(); ++i) {
                targetColors[i] = generateRandomColorInRange(lightColor, darkColor);
            }
            lastColorChangeTime = time;
        }

        // Update the color of each tile to create a blinking effect
        for (size_t i = 0; i < tiles.size(); ++i) {
            float alpha = (std::sin(time * 2.0f + phases[i]) + 1.0f) / 2.0f; // Alpha oscillates between 0 and 1
            sf::Color interpolatedColor = interpolateColor(currentColors[i], targetColors[i], alpha);
            tiles[i].setFillColor(interpolatedColor);
        }

        window.clear();

        // Apply the map view and draw the tiles
        window.setView(mapView);
        for (const auto& tile : tiles) {
            window.draw(tile);
        }

        // Reset the view to default to draw UI elements correctly
        window.setView(window.getDefaultView());
        window.draw(button);
        window.draw(buttonText);

        window.display();
    }

    return 0;
}
