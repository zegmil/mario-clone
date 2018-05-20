#include "Player.h"

Player::Player(int x, int y) {
	position.x = x;
	position.y = y;
	prev_position.x = position.x;
	prev_position.y = position.y;
	active_sprite = 0;
	dx = 0;
	dy = 0;
	is_flying = false;
	lives = 3;
	multiplier = 0;

	sprites[0] = SDL_LoadBMP("./data/mario.bmp");
	SDL_SetColorKey(sprites[0], true, 0x00FF00FF);
	sprites[1] = SDL_LoadBMP("./data/mario_move0.bmp");
	SDL_SetColorKey(sprites[1], true, 0x00FF00FF);
	sprites[2] = SDL_LoadBMP("./data/mario_move1.bmp");
	SDL_SetColorKey(sprites[2], true, 0x00FF00FF);
	sprites[3] = SDL_LoadBMP("./data/mario_move2.bmp");
	SDL_SetColorKey(sprites[3], true, 0x00FF00FF);
	sprites[4] = SDL_LoadBMP("./data/mario_rev.bmp");
	SDL_SetColorKey(sprites[4], true, 0x00FF00FF);
	sprites[5] = SDL_LoadBMP("./data/mario_move0_rev.bmp");
	SDL_SetColorKey(sprites[5], true, 0x00FF00FF);
	sprites[6] = SDL_LoadBMP("./data/mario_move1_rev.bmp");
	SDL_SetColorKey(sprites[6], true, 0x00FF00FF);
	sprites[7] = SDL_LoadBMP("./data/mario_move2_rev.bmp");
	SDL_SetColorKey(sprites[7], true, 0x00FF00FF);
	sprites[8] = SDL_LoadBMP("./data/mario_jump.bmp");
	SDL_SetColorKey(sprites[8], true, 0x00FF00FF);
	sprites[9] = SDL_LoadBMP("./data/mario_jump_rev.bmp");
	SDL_SetColorKey(sprites[9], true, 0x00FF00FF);
}

void Player::setDirection(int direction) 
{
	prev_position.x = position.x;
	prev_position.y = position.y;
	switch (direction)
	{
	case RIGHT:
		dx = X_INC;
		break;
	case LEFT:
		dx = -X_INC;
		break;
	}
}

void Player::jump() 
{
	if (!is_flying) 
	{
		is_flying = true;
		dy = 20;
	}
}

void Player::update(Obstacle **obstacles, double offset, int obstacles_amount, int &game_state, int ticks)
{
	double x = position.x;
	double y = position.y;

	if (is_flying)
	{
		y -= multiplier * SPEED * dy;
		dy -= DY_INC * multiplier;
		if (y >= DEADLINE_Y)
		{
			lives--;
			if (lives > 0)
				game_state = DEAD;
			else
				game_state = LOSE;
		}
	}
	if (!isInsideScene(position.x + multiplier*SPEED*dx, offset))
		dx = 0;
	move(dx, dy, obstacles, obstacles_amount);
	//-------	Animation update
	if (ticks % SPRITE_CHANGE_RATE == 0) 
	{
		if (prev_position.x < position.x)
		{
			if (is_flying)
				active_sprite = 8;
			else
				active_sprite = active_sprite % 3 + 1;
		}
		else if (prev_position.x > position.x)
		{
			if (is_flying)
				active_sprite = 9;
			else
				active_sprite = active_sprite % 3 + 5;
		}
	}
}

bool Player::isInsideScene(double x, double offset)
{
	if ( x > offset)
		return true;
	else
		return false;
}

bool Player::isCollision (double x, double y, Obstacle * obstacle)
{
	if (x < obstacle->position.x + (obstacle->width)*UNIT && x + UNIT > obstacle->position.x &&
		y > obstacle->position.y - (obstacle->height)*UNIT && y - UNIT < obstacle->position.y)
		return true;
	else
		return false;
}

void Player::move(double &dx, double &dy, Obstacle ** obstacles, int obstacles_amount) {
	bool vertical_collision = false;
	bool horizontal_collision = false;
	double diff_x = dx * multiplier * SPEED;
	double diff_y = dy * multiplier * SPEED;
	for (int i = 0; i < obstacles_amount; i++)
	{
		if (obstacles[i] != NULL) {
			if (!vertical_collision)
			{
				if(dy != 0)
					vertical_collision = isCollision(position.x, position.y - diff_y, obstacles[i]);
				else
					vertical_collision = isCollision(position.x, position.y + 1, obstacles[i]);
			}
			if (!horizontal_collision)
				horizontal_collision = isCollision(position.x + diff_x, position.y, obstacles[i]);
		}
	}

	if (!vertical_collision)
	{
		position.y -= multiplier * SPEED * dy;
		is_flying = true;
	}
	else
	{
		if (dy < 0)
			is_flying = false;
		dy = 0;
	}
	if (!horizontal_collision)
		position.x += multiplier * SPEED * dx;
}
