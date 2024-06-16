/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** trantorian
*/

#include "Trantorian.hpp"

Trantorian::Trantorian(int id, std::string teamName, sf::Vector2i pos, int direction, int level, int teamNumber)
{
    this->id = id;
    this->teamName = teamName;
    this->pos = pos;
    this->level = level;
    this->direction = direction;
    this->inventory = new int[7];
    this->teamNumber = teamNumber;

    // Initialize animation variables
    currentFrame = 0;
    frameCount = 9;       // Total number of frames
    frameDuration = 0.1f; // Duration of each frame in seconds
    elapsedTime = 0.0f;   // Start with zero elapsed time

    setSprite();
}

void Trantorian::setSprite()
{
    switch (teamNumber) {
        case 0:
            if (!texture.loadFromFile("GUI/src/Assets/VIRUS/VIRUS-GREEN.png")) {
                std::cerr << "Error loading trantorian sprite" << std::endl;
            }
            break;
        case 1:
            if (!texture.loadFromFile("GUI/src/Assets/VIRUS/VIRUS-RED.png")) {
                std::cerr << "Error loading trantorian sprite" << std::endl;
            }
            break;
        case 2:
            if (!texture.loadFromFile("GUI/src/Assets/VIRUS/VIRUS-YELLOW.png")) {
                std::cerr << "Error loading trantorian sprite" << std::endl;
            }
            break;
        case 3:
            if (!texture.loadFromFile("GUI/src/Assets/VIRUS/VIRUS-PINK.png")) {
                std::cerr << "Error loading trantorian sprite" << std::endl;
            }
            break;
        default:
            // TODO: handle error for invalid teamNumber
            break;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 90, 90));
}

void Trantorian::draw(sf::RenderWindow &window)
{
    const int tileSize = 90;

    sf::IntRect frameRectElevation(currentFrame * 100, 100, 90, 90);
    sf::IntRect frameRect(currentFrame * 100, 0, 90, 90);
    sf::Vector2f pixelPos(pos.x * tileSize, pos.y * tileSize);
    
    if (elevation)
        sprite.setTextureRect(frameRectElevation);
    else
        sprite.setTextureRect(frameRect);
    sprite.setPosition(pixelPos);
    window.draw(sprite);
}

void Trantorian::animate(float time)
{
    if (time - elapsedTime > frameDuration) {
        currentFrame = (currentFrame + 1) % frameCount;
        elapsedTime = time;
    }
}

void Trantorian::setInventory(int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
    this->inventory[0] = q0;
    this->inventory[1] = q1;
    this->inventory[2] = q2;
    this->inventory[3] = q3;
    this->inventory[4] = q4;
    this->inventory[5] = q5;
    this->inventory[6] = q6;
}

void Trantorian::setPos(sf::Vector2i pos)
{
    this->pos = pos;
}

void Trantorian::setLevel(int level)
{
    this->level = level;
}

void Trantorian::collectItem(std::shared_ptr<Tile> &tile, int nb)
{
    for (int i = 0; i < 7; i++) {
        while (nb != 0 && tile->getItemsQuantity(i) > 0) {
            this->inventory[i]++;
            tile->removeItem(i);
            nb--;
        }
    }
}

void Trantorian::dropItem(std::shared_ptr<Tile> &tile, int nb)
{
    for (int i = 0; i < 7; i++) {
        while (nb != 0 && this->inventory[i] > 0) {
            tile->addItem(i);
            this->inventory[i]--;
            nb--;
        }
    }
}

bool Trantorian::isElevating()
{
    return elevation;
}

void Trantorian::setElevating(bool isElevating)
{
    elevation = isElevating;
}