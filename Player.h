#pragma once
#include "Obstacle.h"
class Player {
public:
	SDL_Surface * sprites[10];
	Coords position;
	Coords prev_position;
	int active_sprite;
	double dx; 
	double dy; 
	bool is_flying;
	int lives;
	double multiplier;

	Player(int x, int y);
	void setDirection(int direction);
	void jump ();
	void update(Obstacle ** obstacles,double offset, int obstacles_amount, int &game_state, int ticks);
	bool isInsideScene(double x, double offset);
	bool isCollision(double x, double y, Obstacle * obstacles);
	void move(double &dx, double &dy, Obstacle ** obstacles, int obstacles_amount);

};