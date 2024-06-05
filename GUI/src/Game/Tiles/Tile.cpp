/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tile
*/

#include "Tile.hpp"

Tile::Tile(sf::Vector2i pos, int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
    this->pos = pos;
    this->q0 = q0;
    this->q1 = q1;
    this->q2 = q2;
    this->q3 = q3;
    this->q4 = q4;
    this->q5 = q5;
    this->q6 = q6;
    this->qAll = q0 + q1 + q2 + q3 + q4 + q5 + q6;

    try {
        // load textures
        // create sprites
        // set textures to sprites
        // link sprites to items
    } catch (const std::exception &e) {
        // TODO: faire erreur propre
        std::cerr << e.what() << std::endl;
    }
}

void Tile::addItem(int item)
{
    switch (item) {
        case 0:
            this->q0++;
            break;
        case 1:
            this->q1++;
            break;
        case 2:
            this->q2++;
            break;
        case 3:
            this->q3++;
            break;
        case 4:
            this->q4++;
            break;
        case 5:
            this->q5++;
            break;
        case 6:
            this->q6++;
            break;
    }
}

void Tile::removeItem(int item)
{
    switch (item) {
        case 0:
            this->q0--;
            break;
        case 1:
            this->q1--;
            break;
        case 2:
            this->q2--;
            break;
        case 3:
            this->q3--;
            break;
        case 4:
            this->q4--;
            break;
        case 5:
            this->q5--;
            break;
        case 6:
            this->q6--;
            break;
    }
}

int Tile::getItemsQuantity(int item)
{
    switch (item) {
        case 0:
            return (this->q0);
        case 1:
            return (this->q1);
        case 2:
            return (this->q2);
        case 3:
            return (this->q3);
        case 4:
            return (this->q4);
        case 5:
            return (this->q5);
        case 6:
            return (this->q6);
    }
    return (0);
}

sf::Vector2i Tile::getPos()
{
    return (this->pos);
}

void Tile::setAllItemsQuantity(int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
    this->q0 = q0;
    this->q1 = q1;
    this->q2 = q2;
    this->q3 = q3;
    this->q4 = q4;
    this->q5 = q5;
    this->q6 = q6;
    this->qAll = q0 + q1 + q2 + q3 + q4 + q5 + q6;
}

void Tile::setItemQuantity(int item, int quantity)
{
    switch (item) {
        case 0:
            this->q0 = quantity;
            break;
        case 1:
            this->q1 = quantity;
            break;
        case 2:
            this->q2 = quantity;
            break;
        case 3:
            this->q3 = quantity;
            break;
        case 4:
            this->q4 = quantity;
            break;
        case 5:
            this->q5 = quantity;
            break;
        case 6:
            this->q6 = quantity;
            break;
    }
}