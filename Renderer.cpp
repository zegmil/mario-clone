#include "Renderer.h"

Renderer::Renderer(World * world = NULL) {
	this->world = world;
	ground = SDL_LoadBMP("./data/ground1.bmp");
	brick = SDL_LoadBMP("./data/brick.bmp");
	clouds = SDL_LoadBMP("./data/clouds.bmp");
	menu = SDL_LoadBMP("./data/menu.bmp");
	SDL_SetColorKey(menu, true, 0x00FFFFFF);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
	}


	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Mario Clone");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_ShowCursor(SDL_DISABLE);

	charset = SDL_LoadBMP("./data/cs8x8.bmp");
	SDL_SetColorKey(charset, true, 0x000000);

	//------------

	colors[BLACK] = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	colors[GREEN] = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	colors[RED] = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	colors[BLUE] = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
}

void Renderer::DrawString(SDL_Surface *screen, int x, int y, const char *text,
	SDL_Surface *charset) {
	int charset_x, charset_y, character;
	SDL_Rect source, destination;
	source.w = 8;
	source.h = 8;
	destination.w = 8;
	destination.h = 8;
	while (*text) {
		character = *text & 255;
		charset_x = (character % 16) * 8;
		charset_y = (character / 16) * 8;
		source.x = charset_x;
		source.y = charset_y;
		destination.x = x;
		destination.y = y;
		SDL_BlitSurface(charset, &source, screen, &destination);
		x += 8;
		text++;
	};
};

Renderer::~Renderer() {
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



void Renderer::DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


void Renderer::DrawRectangle(SDL_Surface *screen, int x, int y, int width, int height, Uint32 fillColor) {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	SDL_FillRect(screen, &rect, fillColor);
};

void Renderer::update(int &state) {
		Player *mario = world->player;

		SDL_FillRect(screen, NULL, 0x0038b8e9);
		for (int a = 0; a < 5; a++)
		{
			DrawSurface(screen,clouds, 1500 * a - world->offset, 120);
		}
		Obstacle ** objects = world->obstacles_container;
		for (int h = 0; h < world->obstacles_amount; h++)
		{
			for (int i = 0; i < objects[h]->height; i++)
			{
				for (int j = 0; j < objects[h]->width; j++)
				{
					double X = objects[h]->position.x + UNIT / 2 - world->offset;
					if(objects[h]->position.y<SCREEN_HEIGHT)
						DrawSurface(screen, brick, X + j*UNIT, objects[h]->position.y - UNIT / 2 - i*UNIT);
					else
						DrawSurface(screen, ground, X + j*UNIT, objects[h]->position.y - UNIT / 2 - i*UNIT);
				}
			}
		}
		int index = mario->active_sprite;
		DrawSurface(screen, mario->sprites[index], mario->position.x+UNIT/2-world->offset, mario->position.y-UNIT/2);

		DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, colors[BLUE]);
		sprintf(info, "Zycia: %d Pozostaly czas = %.1lf s  %.0lf klatek / s", world->player->lives, world->time, world->fps);
		DrawString(screen, screen->w / 2 - strlen(info) * 8 / 2, 10, info, charset);
		sprintf(info, "Pozycja X: %lf", world->player->position.x);
		DrawString(screen, screen->w / 2 - strlen(info) * 8 / 2, 26, info, charset);
		if (state != ONGOING)
		{
			if(state == WIN)
				sprintf(info, "GRATULACJE, DOTARLES DO KONCA ETAPU");
			else if (state == DEAD)
				sprintf(info, "ZGINALES");
			else
				sprintf(info, "NIESTETY PRZEGRALES :(");
			DrawString(screen, screen->w / 2 - strlen(info) * 8 / 2, screen->h / 2, info, charset);
		}

		SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
}

int Renderer::displayMenu() 
{
	SDL_FillRect(screen, NULL, 0x00009F00);
	DrawSurface(screen, menu, 300, 100);
	sprintf(info, "N - rozpoczecie nowej rozgrywki");
	DrawString(screen, screen->w / 2 - strlen(info) * 8 / 2, 210, info, charset);
	sprintf(info, "L - wczytanie ostatnio zapisanej gry");
	DrawString(screen, screen->w / 2 - strlen(info) * 8 / 2, 242, info, charset);
	sprintf(info, "Esc -wyjscie");
	DrawString(screen, screen->w / 2 - strlen(info) * 8 / 2, 274, info, charset);
	SDL_UpdateTexture(texture, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	return 1;
}