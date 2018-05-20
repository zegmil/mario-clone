#pragma once
#define BLACK 0
#define GREEN 1
#define RED 2
#define BLUE 3
#include "World.h"
class Renderer {
public:
	int colors[4];
	char info[128];
	SDL_Surface *screen, *charset;
	SDL_Texture *texture;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface * menu;
	SDL_Surface * ground, *brick, *clouds;
	World *world;

	Renderer(World * world);
	~Renderer();
	void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset);
	void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y);
	void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k, Uint32 fillColor);
	void update(int &state);
	int displayMenu();
};