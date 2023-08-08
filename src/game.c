#include <SDL.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "game.h"
#include "app.h"

static Texture textures[] =
{
	{ NULL, 128, 128, NULL },
};

void mns_GameInit()
{
	Texture* t = textures;

	t->data = (void*)malloc(sizeof(uint32_t) * t->width * t->height);

	for (int i = 0; i < t->width; i++)
		for (int j = 0; j < t->height; j++)
			((uint32_t*)(t->data))[j + i * t->width] = 0xffdfdedf;

	SDL_Surface* s = SDL_CreateRGBSurfaceWithFormatFrom(t->data, t->width, t->height, 8, 4 * t->width, SDL_PIXELFORMAT_ABGR8888);
	t->texture = SDL_CreateTextureFromSurface(mns_Application->renderer, s);
	SDL_FreeSurface(s);
}

void mns_GameShutdown()
{
	mns_FreeTexture(textures);
}

void mns_GameUpdate(float delta)
{
	mns_DrawTextureWithBounds2f(textures, -.9f, -.9f, .9f, .9f);
}

void mns_GameRender()
{
}
