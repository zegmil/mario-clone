#include "World.h"

World::World(Player *player, int level_lenght, int time, int obstacles_amount) {
	this->level_length = level_lenght;
	this->time = time;
	this->obstacles_amount = obstacles_amount;
	offset = 0;
	ticks = 0; fpsTimer = 0; fps = 0; frames=0;
	this->player = player;
	obstacles_container = new Obstacle*[obstacles_amount];
}

World::~World()
{
	for (int i = 0; i < obstacles_amount; i++)
		delete obstacles_container[i];
	delete obstacles_container;
}

void World::timing()
{
	double ticks = SDL_GetTicks();
	double delta = (ticks - this->ticks) * 0.001; // seconds since last redraw
	this->ticks = ticks;
	time -= delta;
	fpsTimer += delta;
	if (fpsTimer > 0.5) {
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	};
	frames++;
	player->multiplier = delta;
}

void World::update(int &state)
{
	if ((player->position.x - offset) >= SCREEN_WIDTH / 3)
		offset += SPEED * X_INC * player->multiplier;
	timing();
	if (time <= 0)
	{
		player->lives--;
		if (player->lives > 0)
			state = DEAD;
		else
			state = LOSE;
	}
	else if (player->position.x >= level_length)
		state = WIN;
	else
		player->update(obstacles_container, offset,obstacles_amount, state, ticks);
}


