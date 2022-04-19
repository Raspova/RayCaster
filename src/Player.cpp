/*
** EPITECH PROJECT, 2022
** 3D
** File description:
** Player
*/

#include "Player.hpp"
#include "math.h"
#include <iostream>
#define PI 3.1415926535
#define PI2 PI/2
#define PI3 3 * PI / 2
#define DEGRE 0.0174533

float degToRad(int a)
{
    return a * M_PI / 180.0;
}

int FixAng(int a)
{
    if (a > 359)
        a -= 360;
    if (a < 0)
        a += 360;
    return a;
}

float distance(float ax,float ay,float bx,float by,float ang = 0)
{
    std::ignore = ang;
    return sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
}


Player::Player(std::vector<std::vector<int>> &_map) : map(_map)
{
    modAngle(0);
    mMapy = map.size();
    mMaxX = map[0].size();
    line[0].color  = sf::Color::Yellow;
    line[1].color  = sf::Color::Yellow;
  
}

void Player::modPos(bool up)
{
    if (up)
    {
        if (map[((int)(y + 10) / 64)][((int)(x + deltx + 32 + (deltx > 0 ? 32 : -32)) / 64)] == 0 && map[((int)(y + 54) / 64)][((int)(x + deltx + 32 + (deltx > 0 ? 32 : -32)) / 64)] == 0)
            x += deltx;
        if (map[((int)(y + 32 + delty + (delty > 0 ? 32 : -32)) / 64)][((int)(x + 10) / 64)] == 0 && map[((int)(y + 32 + delty + (delty > 0 ? 32 : -32)) / 64)][((int)(x + 54) / 64)] == 0)
            y += delty;
    }
    else
    {
        if (map[((int)(y + 10) / 64)][((int)(x - deltx + 32 + (deltx < 0 ? 32 : -32)) / 64)] == 0 && map[((int)(y + 54) / 64)][((int)(x - deltx + 32 + (deltx < 0 ? 32 : -32)) / 64)] == 0)
            x -= deltx;
        if (map[((int)(y + 32 - delty + (delty < 0 ? 32 : -32)) / 64)][((int)(x + 32) / 64)] == 0 && map[((int)(y + 32 - delty + (delty < 0 ? 32 : -32)) / 64)][((int)(x + 32) / 64)] == 0)
            y -= delty;
    }
    timer.restart();
}

int Player::getMapValue(int _y, int _x)
{
    if (_y >= 0 && _x >= 0 && _x < mMaxX && _y < mMapy)
        return map[_y][_x];
    return -1;
}

void Player::modAngle(float mod)
{
    angle += mod;
    if (angle < 0)
        angle += 2 * PI;
    if (angle > 2 * PI)
        angle -= 2 * PI;
    deltx = cos(angle) * speed;
    delty = sin(angle) * speed;
    pl.sprite.setRotation(angle * 180 / PI);
    timer.restart();
}



void Player::castRay(sf::RenderWindow &win)
{  
    bool found = false;
    float rx, ry, ra, xo, yo, aTan, nTan;
    float disH = MAXFLOAT, disV = MAXFLOAT, hx = -1, hy = -1, vx = -1, vy = -1;
    int  mx = -1, my = -1, dof = 0, typeBuffh = -1, typeBuffv = -1;
    ra = angle - DEGRE * 30;


    resRayCast.clear();
    if (ra < 0)
        ra += 2 * PI;
    if (ra > 2 * PI)
        ra -= 2 * PI;
    for (size_t i = 0; i < 240 ; i++) {
        found = false;
        disH = MAXFLOAT, disV = MAXFLOAT;
        hx = -1, hy = -1, vx = -1, vy = -1;
        mx = -1, my = -1, dof = 0;
        line[0].position = sf::Vector2f(x, y);
        dof =  0;
        aTan = -1 / tan(ra);
        if (ra == 0 || ra == PI) {
            rx = x;
            ry = y;
            dof = dofMax;
        } else if (ra > PI) {
            ry = (((int)y >> 6)<<6) -0.0001;
            rx = (y - ry) * aTan + x;
            yo = -64;
            xo = -yo * aTan;
        } else if (ra < PI) {
            ry = (((int)y >> 6)<<6) + 64;
            rx = (y - ry) * aTan + x;
            yo = 64;
            xo = -yo * aTan;
        }
        while (dof < dofMax) {
            mx = (int)(rx) >>6;
            my =(int)(ry) >>6;
            typeBuffh = getMapValue(my, mx);
            if(typeBuffh != -1 && typeBuffh != EMPTY){// && dof != dofMax -2){
                found = true;
                hx = rx - 32;
                hy = ry -32;
                disH = distance(x, y, hx, hy, ra);
                dof = dofMax;
                //line[0].color = sf::Color::Yellow;
                //line[1].color = sf::Color::Yellow;
                //line[1].position = sf::Vector2f(hx , hy) ;
                //win.draw(line);
            }        
            else{ rx+=xo; ry+=yo; dof+=1;}  
        }
        //if (hx == -1) {
        //    line[1].color = sf::Color::Red;
        //    line[0].color = sf::Color::Red;
        //    line[1].position = sf::Vector2f(rx ,ry);// (x + cos(ra) * 8 * 64 , y + ry + sin(ra) * 8 * 64);
        //    win.draw(line);
        //}*/
        dof =  0;
        nTan = -tan(ra);
        if (ra == 0 || ra == PI) {
            rx = x;
            ry = y;
            dof = dofMax;
        } else if (ra >= PI2 && ra <= PI3) {
            rx = (((int)x >> 6)<<6) -0.0001;
            ry = (x - rx) * nTan + y;
            xo = -64;
            yo = -xo * nTan;
        } else if (ra < PI2 || ra > PI3) {
            rx = (((int)x >> 6)<<6) + 64;
            ry = (x - rx) * nTan + y;
            xo = 64;
            yo = -xo * nTan;
        }
        while (dof < dofMax) {
            mx = (int)(rx) >>6;
            my =(int)(ry) >>6;                          
            typeBuffv = getMapValue(my, mx);
            if(typeBuffv != -1 && typeBuffv != EMPTY){// && dof != dofMax -2){ 
                typeBuffv+=1;
                found = true;
                vx = rx - 32;
                vy = ry -32;
                disV = distance(x, y, vx, vy, ra);
                dof = dofMax;
                //line[1].position = sf::Vector2f(vx , vy );
                //line[1].color = sf::Color::Blue;
                //line[0].color = sf::Color::Blue;
                //win.draw(line);
            }        
            else{ rx+=xo; ry+=yo; dof+=1;}  
        }
        mx = ((disH < disV) ? hx : vx); 
        my = ((disH < disV) ? hy : vy);//*/
        //line[0].position = sf::Vector2f(x, y);
        if (found && my != -1) {
            //win.setView(vR);
            line[1].color = sf::Color::Red;
            line[0].color = sf::Color::Red;
            line[1].position = sf::Vector2f(mx, my);
            win.draw(line);
            float angleDiff = angle - ra;
            if (angleDiff < 0)
                angleDiff += 2 * PI;
            if (angleDiff > 2 * PI)
                angleDiff -= 2 * PI;
            resRayCast.push_back(resDist(((disH < disV) ? typeBuffh : typeBuffv), i,((disH < disV) ? disH : disV) * cos(angleDiff)));
           // win.setView(vL);
           // win.draw(line);
        }
        else {
            //line[1].color = sf::Color::Green;
            //line[0].color = sf::Color::Green;
            //line[1].position = sf::Vector2f(rx, ry);
        }
        //line[0].position = sf::Vector2f(x, y);
        //line[1].position = sf::Vector2f((disH < disV ? hx * 64 : vx * 64+ (ra > PI ? 32 : -32)), (disH < disV ? hy * 64 + (ra > PI ? 32 : -32) : vy * 64));
        //if (disH < disV) {
        //    
        //}
        ra += (DEGRE/ 4);
        if (ra < 0)
        ra += 2 * PI;
        if (ra > 2 * PI)
        ra -= 2 * PI;
    }
    //std::cout << mx << " " << my << "\n";
    //dot.setPos(mx * 64, (my * 64) + (ra > PI ? 32 : -32) );
   
    
}
void Player::loop(sf::RenderWindow &window)
{

    if (timer.getElapsedTime().asMilliseconds() > 30)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) // && timer.getElapsedTime().asMilliseconds() > 1)
            modAngle(-0.1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // && timer.getElapsedTime().asMilliseconds() > 1)
            modAngle(0.1);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            modPos(true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            modPos(false);
    }
    pl.setPos(x, y);
    pl.draw(window);
    castRay(window);
    //window.draw(line);
    //dot.draw(window);
}