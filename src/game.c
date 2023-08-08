#include <SDL.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "app.h"

static Texture textures[] =
{
	{ NULL, 128, 128, NULL },
};

enum CellCode
{
	CellEmpty = 0u,
	CellMine = 1u,
	CellExposed = 1 << 1,
};

static int isMine(uint32_t cell)
{
	return cell & 0x1u;
}

static void setCellNum(uint32_t* cell, uint32_t num)
{
	*cell |= (num << 8);
}

static int getCellNum(uint32_t cell)
{
	return (int)((cell & 0x0000ff00) >> 8);
}

typedef struct Map
{
	uint32_t* cells;
	int width, height, numMines;
} Map;

static Map s_Map =
{
	NULL,
	8, 8,
	10
};

void mns_GameInit()
{
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
	s_Map.cells = (uint32_t*)malloc(sizeof(uint32_t) * s_Map.width * s_Map.height);
	memset(s_Map.cells, 0, sizeof(uint32_t) * s_Map.width * s_Map.height);
}

void mns_GameShutdown()
{
	mns_FreeTexture(textures);
}

void mns_GameUpdate(float delta)
{
	
}

void mns_GameRender()
{
	float x = -1.f, y = -1.f;
	float wx = 2.f / s_Map.width, wy = 2.f / s_Map.height;

	for (int i = 0; i < s_Map.width; i++)
	{
		y = -1.f;
		for (int j = 0; j < s_Map.height; j++)
		{
			mns_DrawTextureWithBounds2f(textures, x + 0.025f, y + 0.025f, wx - 0.05f, wy - 0.05f);
			y += wy;
		}
		x += wx;
	}
}
