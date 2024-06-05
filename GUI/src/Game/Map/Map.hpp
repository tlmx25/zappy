/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map
*/

#ifndef MAP_HPP
    #define MAP_HPP
    #include <iostream>
    #include <string>
    #include <algorithm>
    #include <vector>
    #include <SFML/Graphics.hpp>

// TODO: Objects sprites handled here: create, load etc in constructor

class Map
{
    public:
        Map(int width, int height);
        ~Map() = default;
    private:
        int width;
        int height;
};

#endif