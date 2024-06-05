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
    const int mapSize = 1600; // Larger map size
    const int tileCount = 20; // More tiles to fit the larger map
    const float tileSize = mapSize / tileCount;
    const int windowSize = 800;

    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    // Lightest and darkest colors
    sf::Color lightColor(36, 76, 156); // #244c9c
    sf::Color darkColor(1, 39, 117);   // #012775

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Blinking Tiles with Movable Camera");
    window.setFramerateLimit(60);

    // Create the grid of tiles
    std::vector<sf::RectangleShape> tiles(tileCount * tileCount);
    std::vector<sf::Color> currentColors(tileCount * tileCount);
    std::vector<sf::Color> targetColors(tileCount * tileCount);
    std::vector<float> phases(tileCount * tileCount);

    for (int y = 0; y < tileCount; ++y) {
        for (int x = 0; x < tileCount; ++x) {
            sf::RectangleShape tile(sf::Vector2f(tileSize - 1, tileSize - 1));
            tile.setPosition(x * tileSize, y * tileSize);

            sf::Color initialColor = generateRandomColorInRange(lightColor, darkColor);
            tile.setFillColor(initialColor);

            tiles[y * tileCount + x] = tile;
            currentColors[y * tileCount + x] = initialColor;
            targetColors[y * tileCount + x] = generateRandomColorInRange(lightColor, darkColor); // Initial target color
            phases[y * tileCount + x] = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f; // Random phase for each tile
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
    sf::View mapView(sf::FloatRect(0, 0, windowSize, windowSize));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle keyboard input for moving the view
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            mapView.move(-5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            mapView.move(5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            mapView.move(0, -5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            mapView.move(0, 5);
        }

        // Constrain the view within the map boundaries
        sf::Vector2f center = mapView.getCenter();
        sf::Vector2f size = mapView.getSize();

        float halfWidth = size.x / 2.0f;
        float halfHeight = size.y / 2.0f;

        if (center.x - halfWidth < 0) {
            mapView.setCenter(halfWidth, center.y);
        }
        if (center.x + halfWidth > mapSize) {
            mapView.setCenter(mapSize - halfWidth, center.y);
        }
        if (center.y - halfHeight < 0) {
            mapView.setCenter(center.x, halfHeight);
        }
        if (center.y + halfHeight > mapSize) {
            mapView.setCenter(center.x, mapSize - halfHeight);
        }

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
