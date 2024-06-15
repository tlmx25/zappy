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

    items["q0"];
    items["q1"];
    items["q2"];
    items["q3"];
    items["q4"];
    items["q5"];
    items["q6"];
    items["egg"];
    load_sprites();
}

Game::~Game()
{
    if (window.isOpen())
        window.close();
}

void Game::load_sprites()
{
    for (auto& item : items)
    {
        std::string key = item.first;
        std::string texturePath = "GUI/src/Assets/" + key + ".png";
        sf::Texture texture;
        sf::Sprite sprite;
        if (!texture.loadFromFile(texturePath))
        {
            // TODO: handle error if texture loading fails
        }
        sprite.setTexture(texture);
        items[key] = sprite;
    }
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
