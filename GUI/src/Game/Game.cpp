/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** game
*/

#include "Game.hpp"

Game::Game(int x, int y) : map(x, y, 1200)
{
    // link port and ip
    window.create(sf::VideoMode(1200, 1200), "Zappy");
    window.setFramerateLimit(60);

    // TODO: to remove, FOR TEST ONLY
    for (auto& tile : map.getTiles()) {
        tile.setItemQuantity(0, 1);
    }
}

Game::~Game()
{
    if (window.isOpen())
        window.close();
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        render();
    }
}

void Game::handleEvents()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(map.view.getCenter().x - map.view.getSize().x / 2.0f <= 0))
    {
        map.view.move(-5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(map.view.getCenter().x + map.view.getSize().x / 2.0f >= map.mapWidthInPixels))
    {
        map.view.move(5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !(map.view.getCenter().y - map.view.getSize().y / 2.0f <= 0))
    {
        map.view.move(0, -5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !(map.view.getCenter().y + map.view.getSize().y / 2.0f >= map.mapHeightInPixels))
    {
        map.view.move(0, 5);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && currentZoom > 90.0f / 1200.0f)
    {
        map.view.zoom(0.95f); // Zoom in (reduce view size by 5%)
        currentZoom *= 0.95f;
    }

    // Zoom out with X key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && currentZoom < 4.0f)
    {
        map.view.zoom(1.05f); // Zoom out (increase view size by 5%)
        currentZoom *= 1.05f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        currentZoom = 1.0f;
        map.view.setSize(1200, 1200);
    }
}

void Game::render()
{
    float time = clock.getElapsedTime().asSeconds();

    map.updateColors(time);

    window.clear();
    window.setView(map.view);
    map.renderTiles(window);
    // To draw UI elements correctly
    // window.setView(window.getDefaultView());
    window.display();
}
