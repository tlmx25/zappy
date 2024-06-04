/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** trantorian
*/

#include "Trantorian.hpp"

Trantorian::Trantorian(int id, std::string teamName, int x, int y)
{
    this->id = id;
    this->teamName = teamName;
    this->posX = x;
    this->posY = y;
    this->lifeTimeLeft = 126;
    this->level = 1;
    this->direction = 1;
}

void Trantorian::move(int x, int y)
{
    this->posX = x;
    this->posY = y;
}

bool Trantorian::updateLife(int timeUnits)
{
    this->lifeTimeLeft -= timeUnits;
    if (this->lifeTimeLeft <= 0)
        return (false);
    return (true);
}

bool Trantorian::updateLife(int timeUnits) {
    lifeTimeLeft -= timeUnits;
    if (lifeTimeLeft <= 0) {
        auto it = std::find(inventory.begin(), inventory.end(), "food");
        if (it != inventory.end()) {
            inventory.erase(it);
            lifeTimeLeft = 126;
        } else {
            return false;
        }
    }
    return true;
}

void Trantorian::updateInventory(std::string item)
{
    this->inventory.push_back(item);
}

void Trantorian::setSprite(sf::Sprite sprite)
{
    this->sprite = sprite;
}

void Trantorian::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}
