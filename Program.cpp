#include "Program.h"

Program::Program()
{
	keystate = SDL_GetKeyboardState(NULL);
	file_manager = new File_Manager();
	renderer = new Renderer(NULL);
	world = NULL;
	ticks = 0;
	level = 1;
}

void Program::run(World * loaded)
{
	bool finish = false;
	world = loaded;
	if (world == NULL)
		lives = LIVES;
	else
		lives = world->player->lives;
	while (!finish)
	{
		int end = 0;
		if (world == NULL)
		{
			char filename[] = "./levels/etapX.txt";
			filename[13] = level + 48;
			world = file_manager->loadLevel(filename);
		}
		if (world != NULL)
		{
			renderer->world = world;
			world->ticks = ticks;
			Player *player = world->player;
			player->lives = lives;
			game_state = ONGOING;
			while (end != 1)
			{
				if (game_state == ONGOING)
				{
					world->update(game_state);
					renderer->update(game_state);
				}
				else if (game_state != NEW)
				{
					world->time = 3; // 3 seconds wait after win or lose
					while (world->time > 0)
					{
						SDL_RenderPresent(renderer->renderer);
						world->timing();
					}
					end = 1;
				}
				player->prev_position.x = player->position.x;
				player->prev_position.y = player->position.y;
				int action = getAction();
				int temp_level;
				World *temp_world;
				switch (action)
				{
				case NEW_GAME:
					game_state = NEW;
					ticks = world->ticks;
					world->player->lives = LIVES;
					level = 1;
					end = 1;
					break;
				case LOAD_GAME:
					temp_level = level;
					temp_world = file_manager->loadGame(level);
					if (temp_world != NULL)
					{
						temp_world->ticks = world->ticks;
						delete world;
						world = temp_world;
						player = world->player;
						lives = player->lives;
						renderer->world = world;
					}
					else
						level = temp_level;
					break;
				case SAVE_GAME:
					file_manager->saveGame(world, level);
					break;
				case EXIT:
					end = 1;
				}
			}
			if (game_state == WIN)
			{
				level++;
				game_state = ONGOING;
			}
			else if (game_state == DEAD || game_state == NEW)
				game_state = ONGOING;
			else
				finish = true;
			lives = player->lives;
			ticks = world->ticks;
			delete world;
			world = NULL;
		}
		else
			finish = true;
	}
}

int Program::getAction()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return EXIT;
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_n:
				return NEW_GAME;
				break;
			case SDLK_s:
				return SAVE_GAME;
				break;
			case SDLK_l:
				return LOAD_GAME;
				break;
			case SDLK_ESCAPE:
				return EXIT;
				break;
			}
		}
	}
	if (world != NULL) 
	{
		if (keystate[SDL_SCANCODE_LEFT])
			world->player->setDirection(LEFT);
		else if (world->player->dx == -X_INC)
		{
			world->player->dx = 0;
			world->player->active_sprite = 4;
		}
		if (keystate[SDL_SCANCODE_RIGHT])
			world->player->setDirection(RIGHT);
		else if (world->player->dx == X_INC)
		{
			world->player->dx = 0;
			world->player->active_sprite = 0;
		}
		if (keystate[SDL_SCANCODE_UP])
			world->player->jump();
	}
	return PROCEED;
}