/*
** EPITECH PROJECT, 2022
** 3D
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.hpp" 


class Game {
    public:
        Game();
        void play();
        void loadMap(const std::string path);
        void drawMap();
        void drawVerticalLine(int size, int x, int wight, int yOffset , sf::Color col);
        void drawHorinzontalLine(int size, int y, int wight, int xOffset  , sf::Color col);
        ~Game();

    protected:
    private:
        sf::View vL; 
        sf::View vR;
        std::vector<std::vector<int>> map;
        sf::RenderWindow window;
        // SimpleAsset 
        SimpleAsset wall = SimpleAsset("asset/wall.png");
        Player *player;
       
};

#endif /* !GAME_HPP_ */
