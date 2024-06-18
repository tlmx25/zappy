/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** game
*/

#include "Game.hpp"

Game::Game(int x, int y) : map(x, y, 1200)
{
    window.create(sf::VideoMode(1200, 1200), "Zappy");
    window.setFramerateLimit(60);

    // Load and start music
    if (!music.openFromFile("GUI/src/Assets/music.ogg")) {
        std::cerr << "Error loading music file" << std::endl;
    } else {
        music.setLoop(true);
        music.play();
    }

    // trantorians["test"] = std::make_shared<Trantorian>(0, "test", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test"));
}

Game::~Game()
{
    if (window.isOpen())
        window.close();
    music.stop();
}

void Game::run()
{
    handleEvents();

    float time = clock.getElapsedTime().asSeconds();
    for (auto& trantorian : trantorians) {
        trantorian.second->animate(time);
    }

    render();
}


void Game::handleEvents()
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !(map.view.getCenter().x - map.view.getSize().x / 2.0f <= 0)) {
        map.view.move(-5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !(map.view.getCenter().x + map.view.getSize().x / 2.0f >= map.mapWidthInPixels)) {
        map.view.move(5, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !(map.view.getCenter().y - map.view.getSize().y / 2.0f <= 0)) {
        map.view.move(0, -5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !(map.view.getCenter().y + map.view.getSize().y / 2.0f >= map.mapHeightInPixels)) {
        map.view.move(0, 5);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && currentZoom > 90.0f / 1200.0f) {
        map.view.zoom(0.95f); // Zoom in (reduce view size by 5%)
        currentZoom *= 0.95f;
    }
    // Zoom out with X key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && currentZoom < 4.0f) {
        map.view.zoom(1.05f); // Zoom out (increase view size by 5%)
        currentZoom *= 1.05f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        currentZoom = 1.0f;
        map.view.setSize(1200, 1200);
    }
    // Control music with keyboard
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        if (music.getStatus() == sf::Music::Playing) {
            music.pause(); // Pause the music
        } else {
            music.play(); // Play the music
        }
        sf::sleep(sf::milliseconds(200)); // To avoid multiple key presses
    }
}

void Game::render()
{
    float time = clock.getElapsedTime().asSeconds();

    map.updateColors(time);

    window.clear();
    window.setView(map.view);
    map.renderTiles(window);
    for (auto& trantorian : trantorians) {
        trantorian.second->draw(window);
    }
    // To draw UI elements correctly?
    // window.setView(window.getDefaultView());
    window.display();
}

int Game::getTeamNumber(std::string teamName)
{
    auto it = teamToNumber.find(teamName);
    if (it == teamToNumber.end()) {
        int nb = nextTeamNumber++;
        teamToNumber[teamName] = nb;
        return nb;
    }
    return it->second;
}

sf::RenderWindow& Game::getWindow()
{
    return window;
}

Map& Game::getMap()
{
    return map;
}

std::map<std::string, std::shared_ptr<Trantorian>>& Game::getTrantorians()
{
    return trantorians;
}