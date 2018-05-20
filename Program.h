#pragma once
#include "File_Manager.h"
class Program
{
public:
	Uint8 const *keystate;
	File_Manager *file_manager;
	Renderer *renderer;
	World *world;
	double ticks;
	int level,lives;
	int game_state;

	Program();
	void run(World * loaded = NULL);
	int getAction();
};