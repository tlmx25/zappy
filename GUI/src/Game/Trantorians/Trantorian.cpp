/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** trantorian
*/

#include "Trantorian.hpp"

Trantorian::Trantorian(int id, std::string teamName, sf::Vector2i pos, int direction, int level)
{
    this->id = id;
    this->teamName = teamName;
    this->pos = pos;
    this->level = level;
    this->direction = direction;
}

void Trantorian::setSprite(sf::Sprite sprite)
{
    this->sprite = sprite;
}

void Trantorian::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
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