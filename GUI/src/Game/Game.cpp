/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** game
*/

#include "Game.hpp"

Game::Game()
{
    // link port and ip
    // create window
}

Game::~Game()
{
    // if window is open, close it
}

void Game::run()
{
    // in window loop, call events, update, render in try catch
}

void Game::render()
{
    // render game

    // draw map
    // get/draw eggs, players, food, stones
}

void Game::updateRender()
{
    this->window.clear(sf::Color::Black);
    this->render();
    this->window.display();
}