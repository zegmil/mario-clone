#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include"./sdl/include/SDL.h"
#include"./sdl/include/SDL_main.h"


#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UNIT 32 // single bitmap size
#define GROUND_Y SCREEN_HEIGHT - (2*UNIT) // 2 units represent the ground
#define DEADLINE_Y SCREEN_HEIGHT + UNIT 
#define ONGOING 0
#define WIN 1
#define LOSE 2
#define DEAD 3
#define NEW 4

#define SPEED 60
#define X_INC 6
#define DY_INC 70
#define SPRITE_CHANGE_RATE 20 

#define NEW_GAME 0	
#define LOAD_LEVEL 1
#define LOAD_GAME 2
#define SAVE_GAME 3
#define MOVE_LEFT 4
#define MOVE_RIGHT 5
#define JUMP 6
#define EXIT 7
#define PROCEED 8

#define LIVES 3

struct Coords
{
	double x;
	double y;
};