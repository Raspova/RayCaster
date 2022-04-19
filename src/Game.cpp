/*
** EPITECH PROJECT, 2022
** $
** File description:
** Game
*/

#include "Game.hpp"
#include <fstream>

Game::Game() : window(sf::VideoMode::getDesktopMode(), "Window")
{
    sf::Vector2u wsize = window.getSize();
    std::cout << wsize.x << "*" << wsize.y << "\n";
    window.setFramerateLimit(60);
    loadMap("map/map0");
    vR.setSize(wsize.x, wsize.y);
    vR.setCenter(wsize.x / 2, wsize.y / 2);
    //vR.setViewport(sf::FloatRect(0, 0, 0.5f, 1)); 
    vR.setViewport(sf::FloatRect(0.76, 0, 0.25, 0.25)); 
    //vR.zoom(0.5);
    vL.setSize(wsize.x, wsize.y);
    vL.setCenter(wsize.x / 2, wsize.y / 2);
    //vL.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
    vL.setViewport(sf::FloatRect(0, 0, 1, 1));
    player = new Player(map);
}

void Game::loadMap(std::string path)
{
    std::string mapS;
    std::getline(std::ifstream(path.c_str()), mapS, '\0');
    int index = 0;

    map.clear();
    map.push_back(std::vector<int>());

    for (char c : mapS)
    {
        if (c == '#')
            map[index].push_back(WALL);
        else if (c == ' ')
            map[index].push_back(EMPTY);
        else if (c == '\n')
        {
            index++;
            map.push_back(std::vector<int>());
        }
        else
            std::cout << "Map value unrecognise" << c << std::endl;
    }
}

void Game::drawMap()
{
    int y = 0;
    int x = 0;

    for (std::vector<int> row : map) {
        for (int cell : row) {
            if (cell == WALL) {
                wall.setPos(x * 64, y * 64);
                wall.draw(window);
            }
            x++;
        }
        x = 0;
        y++;
    }
}

void Game::drawHorinzontalLine(int size, int y, int wight, int xOffset = 0, sf::Color col = sf::Color::Cyan)
{
    sf::VertexArray line = sf::VertexArray(sf::TrianglesStrip, 4);

    for (size_t i = 0; i < 4; i++)
        line[i].color =  col;
    line[0].position = sf::Vector2f(xOffset, y);
    line[1].position = sf::Vector2f(xOffset, y + wight);
    line[2].position = sf::Vector2f(xOffset + size, y);
    line[3].position = sf::Vector2f(xOffset + size, y + wight);
    window.draw(line);
}

void Game::drawVerticalLine(int size, int x, int wight, int yOffset = 0, sf::Color col = sf::Color::Cyan)
{
    sf::VertexArray line = sf::VertexArray(sf::TrianglesStrip, 4);

    for (size_t i = 0; i < 4; i++)
        line[i].color =  col;
    line[0].position = sf::Vector2f(x, size + yOffset);
    line[1].position = sf::Vector2f(x + wight, size + yOffset);
    line[2].position = sf::Vector2f(x, yOffset);
    line[3].position = sf::Vector2f( x + wight, yOffset);
    window.draw(line);
}

void Game::play()
{
    
 
    SimpleAsset bck("asset/bck.jpg");
    bck.setToBackgroung();
   // int mapCube = map.size() * map[0].size();
    float winSizeY = window.getSize().y;
    float winSizeX = window.getSize().x;
    float lineWight = winSizeX / 240;
    sf::RectangleShape floor(sf::Vector2f(winSizeX , winSizeY /2));
    sf::RectangleShape sky(sf::Vector2f(winSizeX , winSizeY /2));
    
    floor.setPosition(0,  winSizeY /2);
    sky.setPosition(0, 0);
    floor.setFillColor(sf::Color(0,250,0,100));
    sky.setFillColor(sf::Color(0,0,200,100));
    player->loop(window);
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        if (!window.hasFocus())
            continue;
        window.clear();//sf::Color(0,0, 200));
        //
        window.setView(vL);
        //drawVerticalLine(100,100, 20, 50);
        window.draw(floor);
        window.draw(sky);
        for (resDist res : player->getRayCastRes()) {
            float lineY = winSizeY * 150 / res.dist;
            lineY =  lineY > winSizeY ? winSizeY : lineY;
            drawVerticalLine(lineY, res.index * lineWight, lineWight, (winSizeY - lineY)/ 2,
            res.type == WALL ? sf::Color(180, 80, 0) :  sf::Color(150, 50,0));
        }
        window.setView(vR);
        bck.draw(window);
        player->loop(window);
        //vR.setCenter(player->x, player->y);
        drawMap();
        drawVerticalLine(winSizeY + 50, -5, 20, -25, sf::Color(150,150,0));
        drawVerticalLine(winSizeY + 50, winSizeX - 100, 20, -25, sf::Color(150,150,0));
        drawHorinzontalLine(winSizeX - 75, 0, 20, 0, sf::Color(180,180,0));
        drawHorinzontalLine(winSizeX - 75, winSizeY -20, 20, 0, sf::Color(180,180,0));
        //window.clear(sf::Color::Red);
       // window.setView(vR);
        //player->loop(window);
        //drawMap();
        window.display();
    }
}
Game::~Game()
{
}
