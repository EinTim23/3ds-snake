#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <iostream>
#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2
#define MAXLENGTH 30
#define gridsize 20
namespace game{
    void initGrid(int x, int y);
    void drawgrid();
    void random(int &x, int &y);
    void drawtarget();
    void drawsnake();
    void drawunit(int x, int y);
}

#endif