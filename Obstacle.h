#pragma once
#include "Includer.h"
class Obstacle
{
public:
	Coords position;
	int width, height; // in UNITs

	Obstacle(int x, int y, int width, int height);
};