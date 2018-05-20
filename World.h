#include "Player.h"

class World {
public:
	int level_length,obstacles_amount;
	double offset;
	double time, fpsTimer, fps, frames, ticks;
	Player *player;
	Obstacle **obstacles_container;

	World(Player * player,int level_length,int time, int obstacles_amount);
	~World();
	void timing(); 
	void update(int &state);
};