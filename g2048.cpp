#include <iostream>
#include "g2048.h"
#include <cstdlib>
#include <iomanip>
#include <unistd.h>

G2048::G2048()
{
    initPane();
}

G2048::~G2048()
{

}

void G2048::rotate90(Pane& pane1, Pane& pane2)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            pane2[i][j] = pane1[j][i];
        }
    G2048::rotate180(pane2, pane1);
}

void G2048::rotate180(Pane& pane1, Pane& pane2)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            pane2[i][j] = pane1[i][SIZE - j - 1];
        }
}

void G2048::rotate_90(Pane& pane1, Pane& pane2)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            pane2[i][j] = pane1[j][i];
        }
    G2048::rotate_180(pane2, pane1);
}

void G2048::rotate_180(Pane& pane1, Pane& pane2)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            pane2[i][j] = pane1[SIZE - i - 1][j];
        }
}

bool G2048::isGameOver()
{
    int tmp = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            if(pane1[i][j] == 0)
                tmp += 1;
        }
    if (tmp == 0) return true;
    else return false; 
}

bool G2048::isEmpty(int x, int y)
{
    if (pane1[x][y] == 0)
        return true;
    else
        return false;
}

int G2048::generateNum(int x, int y)
{
    if (isEmpty(x, y) == true)
        return (rand() % 2 == 0) ? 2 : 4;
    else
        return 0;
}

void G2048::initPane()
{
    srand(rand() % 10);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            pane1[i][j] = 0;
            pane2[i][j] = 0;
        }
    score = 0;
}

void G2048::copyP1P2()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            pane1[i][j] = pane2[i][j];
}

void G2048::disPane(Pane& p)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            std::cout << std::setw(4) << p[i][j] << ' ';
        }
        std::endl(std::cout);
    }
}

void G2048::resetScore()
{
    score = 0;
}

int G2048::getScore(Pane& p)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            score += p[i][j];
        }
    return score;
}

void G2048::showPane(Pane& p)
{
    disPane(p);
    resetScore();
    std::cout << "score: " << getScore(p) << std::endl;
}

void G2048::coreAlgorithm(Pane& p)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = SIZE - 1; j > 0; j--)
        {
            if (p[i][j-1] == 0)
            {
                int k = j-1;
                for (; k < SIZE - 1; k++)
                {
                    p[i][k] = p[i][k+1];
                }
                p[i][k] = 0;
            }
            else if (p[i][j-1] == p[i][j])
            {
                p[i][j-1] = p[i][j] * 2;
                int k = j;
                for (; k < SIZE -1; k++)
                {
                    p[i][k] = p[i][k+1];
                }
                p[i][k] = 0;
            }
        }
    }
}

void G2048::setNum(Pane& pane1, int x, int y, int n)
{
    pane1[x][y] = n;
}

void G2048::handleOps(Direction& d)
{
    if (d == QUIT)
    {
        std::cout << "Quit!" << std::endl;
        exit(0);
    }
    switch(d)
    {
        case UP:{
            rotate_90(pane1, pane2);
            coreAlgorithm(pane2);
            rotate90(pane2, pane1);
        }break;
        case DOWN:{
            rotate90(pane1, pane2);
            coreAlgorithm(pane1);
            rotate_90(pane1, pane2);
        }break;
        case LEFT:{
            coreAlgorithm(pane1);
        }break;
        case RIGHT:{
            rotate180(pane1, pane2);
            coreAlgorithm(pane2);
            rotate180(pane2, pane1);
        }break;
    }
}

void G2048::run()
{
    std::cout << "game start........." << std::endl;
    std::cout << "-------------------" << std::endl;
    showPane(pane1);
    sleep(1);
    while (true)
    {
        if (isGameOver())
        {
            system("clear");
            std::cout << "--------game over--------" << std::endl;
            showPane(pane1);
            //std::cout << getScore(pane1) << std::endl;
            exit(0);
        }
        int tempx = 0;
        int tempy = 0;
        int num = 0;
        do{
            tempx = rand() % SIZE;
            tempy = rand() % SIZE;
            num = generateNum(tempx, tempy);
            if (num)
                setNum(pane1, tempx, tempy, num);
        }while (!num);
        showPane(pane1);
        std::cout << "-------------------" << std::endl;
        std::cout << "Please enter the direction -> | <- (w,s,a,d)" << std::endl;
        
        Direction d;
        char dirt;
        while (std::cin.good())
        {
            std::cin.clear();
            dirt = std::cin.get();
            switch(dirt)
            {
                case 'w': d = UP; break;
                case 's': d = DOWN; break;
                case 'a': d = LEFT; break;
                case 'd': d = RIGHT; break;
                default : d = ERR; break;
            }
            if (d == ERR)
            {
                char ch;
                while ((ch = std::cin.get()) != '\n') continue;
                std::cin.clear();
            }
            else
            {
                handleOps(d);
                char ch;
                while ((ch = std::cin.get()) != '\n') continue;
                std::cin.clear();
                break;
            }
        }
    }
    showPane(pane1);
    std::cout << "-----------------" << std::endl;
    std::endl(std::cout);
}
