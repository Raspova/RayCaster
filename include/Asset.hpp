/*
** EPITECH PROJECT, 2022
** 3D
** File description:
** SimpleAsset
*/

#ifndef SimpleAsset_HPP_
#define SimpleAsset_HPP_
#include <SFML/Graphics.hpp>


enum {
    EMPTY,
    WALL,
    WALLV,
};

class SimpleAsset
{
public:
    sf::Texture  texture;
    sf::Sprite sprite;
    SimpleAsset(const std::string path, int x = 0, int y = 0);
    ~SimpleAsset();
    void setToBackgroung();
    void draw(sf::RenderWindow &win);
    void setPos(int x, int y);
};



#endif /* !SimpleAsset_HPP_ */
