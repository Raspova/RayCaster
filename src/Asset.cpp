/*
** EPITECH PROJECT, 2022
** 3D
** File description:
** SimpleAsset
*/

#include "Asset.hpp"


SimpleAsset::SimpleAsset(const std::string path,int x , int y)
{
    sf::Vector2u res;

    texture.loadFromFile(path);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    res = texture.getSize();
    sprite.setOrigin(res.x / 2, res.y / 2);
}

void SimpleAsset::draw(sf::RenderWindow &win)
{
    win.draw(sprite);
}

void SimpleAsset::setPos(int x, int y)
{
    sprite.setPosition(x, y);
}

void SimpleAsset::setToBackgroung()
{
    sprite.setOrigin(0,0);
}

SimpleAsset::~SimpleAsset()
{
}
