/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tile
*/

#include "Tile.hpp"

Tile::Tile(sf::Vector2i size, sf::Vector2i pos, int q0, int q1, int q2, int q3, int q4, int q5, int q6)
{
    this->size = size;
    this->pos = pos;
    this->q0 = q0;
    this->q1 = q1;
    this->q2 = q2;
    this->q3 = q3;
    this->q4 = q4;
    this->q5 = q5;
    this->q6 = q6;
    this->qAll = q0 + q1 + q2 + q3 + q4 + q5 + q6;
    this->shape = sf::RectangleShape(sf::Vector2f(size.x, size.y));

    try {
        items["q0"];
        items["q1"];
        items["q2"];
        items["q3"];
        items["q4"];
        // TODO: put them back once all assets are done
        // items["q5"];
        // items["q6"];
        // items["egg"];
        load_sprites();
    } catch (const std::exception &e) {
        // TODO: faire erreur propre
        std::cerr << e.what() << std::endl;
    }
}

void Tile::load_sprites()
{
    for (auto& item : items) {
        std::string key = item.first;
        std::string texturePath = "GUI/src/Assets/" + key + ".png";
        sf::Texture texture;
        sf::Sprite sprite;
        if (!texture.loadFromFile(texturePath))
        {
            // TODO: handle error if texture loading fails
        }
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        sprite.setPosition(pos.x + size.x / 2, pos.y + size.y / 2);
        items[key] = sprite;
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

sf::RectangleShape Tile::getShape()
{
    return (this->shape);
}

void Tile::setFillColor(sf::Color color)
{
    this->shape.setFillColor(color);
}

void Tile::setPos(sf::Vector2i pos)
{
    this->pos = pos;
    this->shape.setPosition(pos.x, pos.y);
}

void Tile::draw(sf::RenderWindow &window)
{
    if (q0 > 0)
        window.draw(items["q0"]);
    if (q1 > 0)
        window.draw(items["q1"]);
    if (q2 > 0)
        window.draw(items["q2"]);
    if (q3 > 0)
        window.draw(items["q3"]);
    if (q4 > 0)
        window.draw(items["q4"]);
    if (q5 > 0)
        window.draw(items["q5"]);
    if (q6 > 0)
        window.draw(items["q6"]);  
}
