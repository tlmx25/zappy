/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** game
*/

#include "Game.hpp"

Game::Game(int x, int y) : map(x, y, 1200)
{
    window.create(sf::VideoMode(960, 960), "Zappy");
    window.setFramerateLimit(60);
    font.loadFromFile("GUI/src/Assets/arial.ttf");

    // Load and start music
    if (!music.openFromFile("GUI/src/Assets/music.ogg")) {
        std::cerr << "Error loading music file" << std::endl;
    } else {
        music.setLoop(true);
        music.play();
    }

    // for (auto& tile : map.getTiles()) {
    //     for (int i = 0; i <= 6; i++) {
    //         tile.setItemQuantity(i, 1);
    //     }
    // }
    // std::string msg = "Welcome to Zappy qerhqerheqrh regheqh end!";
    // std::string team = "test";
    // std::string id = "0";
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);
    // chatbox.addMessage(team, id, msg);

    trantorians["test"] = std::make_shared<Trantorian>(0, "test", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test"));
    trantorians["test1"] = std::make_shared<Trantorian>(1, "test1", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test1"));
    trantorians["test2"] = std::make_shared<Trantorian>(2, "test2", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test2"));
    trantorians["test3"] = std::make_shared<Trantorian>(3, "test3", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test3"));
    trantorians["test4"] = std::make_shared<Trantorian>(4, "test4", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test4"));
    trantorians["test5"] = std::make_shared<Trantorian>(5, "test5", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test5"));
    trantorians["test6"] = std::make_shared<Trantorian>(6, "test6", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test6"));
    trantorians["test7"] = std::make_shared<Trantorian>(7, "test7", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test7"));
    trantorians["test8"] = std::make_shared<Trantorian>(8, "test8", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test8"));
    trantorians["test9"] = std::make_shared<Trantorian>(9, "test9", sf::Vector2i(2, 2), 0, 1, getTeamNumber("test9"));

}

Game::~Game()
{
    if (window.isOpen())
        window.close();
    music.stop();
}

void Game::run()
{
    while (window.isOpen()) {
        handleEvents();
        float time = clock.getElapsedTime().asSeconds();
        for (auto& trantorian : trantorians) {
            trantorian.second->animate(time);
        }
        render();
    }
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
    chatbox.handleEvents(event);
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
    window.setView(window.getDefaultView());
    chatbox.render(window);
    displayTeamBoxes();
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

void Game::checkTeamBoxes()
{
    for (const auto& trantorian : trantorians) {
        std::string teamName = trantorian.second->getTeamName();
        if (std::find(teamNames.begin(), teamNames.end(), teamName) == teamNames.end()) {
            teamNames.push_back(teamName);
        }
    }
}

int Game::getNbElevatedPlayers(std::string teamName)
{
    int nb = 0;
    for (const auto& trantorian : trantorians) {
        if (trantorian.second->getTeamName() == teamName && trantorian.second->getLevel() == 8) {
            nb++;
        }
    }
    return nb;
}

void Game::displayTeamBoxes()
{
    int i = 0;
    checkTeamBoxes();
    for (const auto& teamName : teamNames) {
        int nbElevatedPlayers = getNbElevatedPlayers(teamName);
        int teamNumber = getTeamNumber(teamName);

        sf::RectangleShape teamBox(sf::Vector2f(200, 50));

        // Set color based on team number
        sf::Color teamColor;
        switch (teamNumber) {
            case 0: teamColor = sf::Color(128, 255, 128); break;
            case 1: teamColor = sf::Color(255, 128, 128); break;
            case 2: teamColor = sf::Color(255, 255, 128); break;
            case 3: teamColor = sf::Color(255, 192, 203); break;
            case 4: teamColor = sf::Color(128, 128, 255); break;
            case 5: teamColor = sf::Color(192, 128, 192); break;
            case 6: teamColor = sf::Color(255, 200, 128); break;
            case 7: teamColor = sf::Color(128, 255, 255); break;
            case 8: teamColor = sf::Color(192, 192, 192); break;
            case 9: teamColor = sf::Color(255, 255, 255); break;
            default: teamColor = sf::Color::Black; break;
        }

        teamBox.setFillColor(teamColor);
        teamBox.setOutlineColor(sf::Color::Black);
        teamBox.setOutlineThickness(1);
        teamBox.setPosition(10, 10 + i * 60);

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        text.setString(teamName + "\n" + "Level 8 players: " + std::to_string(nbElevatedPlayers) + " / 6");
        text.setPosition(15, 15 + i * 60);

        window.draw(teamBox);
        window.draw(text);
        i++;
    }
}
