/*
** EPITECH PROJECT, 2022
** 3D
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include "Asset.hpp"
#include <iostream>

struct resDist
{
    resDist(int _type, int _index, float _dist): type(_type), dist(_dist), index(_index) {}
    int type;
    float dist;
    int index;
};

class Player
{
public:
    Player(std::vector<std::vector<int>> &_map);
    void loop(sf::RenderWindow &window);
    void modAngle(float mod);
    void modPos(bool up);
    void setMap(std::vector<std::vector<int>> &_map){map = _map;} 
    void castRay(sf::RenderWindow &window);
    int getMapValue(int y, int x);
    float x = 10 * 64;
    float y = 10 * 64;
    std::vector<resDist> getRayCastRes(){return resRayCast;}
private:
    ///float rx, ry, ra, xo, yo, aTan, nTan;
    ///float disH =3.40282347e+38F, disV = 3.40282347e+38F, hx = x, hy = y, vx = x, vy = y;
    ///int  mx = 0, my = 0, dof = 0;
    
    int mMaxX;
    int mMapy;
    int speed = 10;
    sf::Clock timer;
    float deltx = 0;
    float delty = 0;
    float angle = 0;
    int dofMax = 25;
    std::vector<resDist> resRayCast;
    sf::VertexArray line = sf::VertexArray(sf::LinesStrip, 2);
    std::vector<std::vector<int>> &map;
    SimpleAsset pl = SimpleAsset("asset/player2D.png");
    SimpleAsset dot = SimpleAsset("asset/dot.jpg");
};
#endif /* !PLAYER_HPP_ */
