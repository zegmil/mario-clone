#include "Program.h"
// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	Program program;
	bool finish = false;
	World *loadedGame;
	while (!finish)
	{
		program.renderer->displayMenu();
		int action = program.getAction();
		switch (action) 
		{
		case NEW_GAME:
			program.level = 1;
			program.run();
			break;
		case LOAD_GAME:
			loadedGame = program.file_manager->loadGame(program.level);
			if(loadedGame != NULL)
				program.run(loadedGame);
			break;
		case EXIT:
			finish = true;
		}
	}
	return 0;
	};