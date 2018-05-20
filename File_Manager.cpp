#include "File_Manager.h"

World * File_Manager::loadLevel(char *filename)
{
	World *world;
	int level_length, time_limit, obstacles_amount;
	int x, y;
	FILE *file;
	if (file = fopen(filename, "rb"))
	{
		if (fscanf(file, "%d %d %d %d %d", &level_length, &time_limit, &x, &y, &obstacles_amount) == 5)
		{
			Player * player = new Player(x, GROUND_Y - y);
			world = new World(player, level_length, time_limit, obstacles_amount);
			for (int i = 0; i < obstacles_amount; ++i)
			{
				int x, y, width, height;
				if (fscanf(file, "%d %d %d %d", &x, &y, &width, &height) == 4)
					world->obstacles_container[i] = new Obstacle(x, GROUND_Y - y, width, height);
				else
					return NULL;
			}
		}
		else
			return NULL;
		fclose(file);
		return world;
	}
	else
		return NULL;
}

void File_Manager::saveGame(World * world, int lvl_number)
{
	FILE *file;
	if (file = fopen("./levels/save.txt", "w"))
	{
		fprintf(file, "%d %d %f %f %f %f", lvl_number,world->player->lives,
			world->player->position.x, world->player->position.y, world->time, world->offset);
		fclose(file);
	}
}

World * File_Manager::loadGame(int &level)
{
	World * world = NULL;
	FILE *file;
	int lvl_number,lives;
	double position_x, position_y, time, offset;
	if (file = fopen("./levels/save.txt", "rb"))
	{
		fscanf(file, "%d %d %lf %lf %lf %lf", &lvl_number, &lives, &position_x, &position_y,&time, &offset);
		char filename[] = "./levels/etapX.txt";
		filename[13] = lvl_number + 48;
		world = loadLevel(filename);
		if (world != NULL)
		{
			world->player->lives = lives;
			world->player->position.x = position_x;
			world->player->prev_position.x = position_x;
			world->player->position.y = position_y;
			world->player->prev_position.y = position_y;
			world->time = time;
			world->offset = offset;
			level = lvl_number;
		}
		fclose(file);
	}
	return world;
}