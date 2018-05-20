#pragma once
#include "Renderer.h"
class File_Manager {
public:
	World * loadLevel(char * filename);
	void saveGame(World * world, int lvl_number);
	World * loadGame(int &level);
};