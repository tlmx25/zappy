/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tile
*/

#ifndef TILE_HPP
    #define TILE_HPP
    #include <iostream>
    #include <string>
    #include <algorithm>
    #include <vector>
    #include <SFML/Graphics.hpp>

class Tile
{
    public:
        Tile();
        ~Tile() = default;
        void addItem(int item);
        void removeItem(int item);
        int getItemsQuantity(int item);
    private:
        int q0;
        int q1;
        int q2;
        int q3;
        int q4;
        int q5;
        int q6;
};

#endif