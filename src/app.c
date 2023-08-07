#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>

#include "app.h"

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;
static uint32_t pixels[] =
{
	0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
	0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
	0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
	0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
	0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
	0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
};

static int w = 6, h = 6;

static int shouldRun = 1;

int mns_ShouldRun()
{
	return shouldRun;
}

void mns_Init(int argc, char** argv)
{
	{
		int rendererFlags, windowFlags;

		rendererFlags = SDL_RENDERER_ACCELERATED;

		windowFlags = 0;

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("Couldn't initialize SDL: %s\n", SDL_GetError());
			exit(1);
		}

		window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, windowFlags);

		if (!window)
		{
			printf("Failed to open %d x %d window: %s\n", 600, 400, SDL_GetError());
			exit(1);
		}

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

		renderer = SDL_CreateRenderer(window, -1, rendererFlags);

		if (!renderer)
		{
			printf("Failed to create renderer: %s\n", SDL_GetError());
			exit(1);
		}
	}

	{
		SDL_Surface* s = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, 8, w * 4, SDL_PIXELFORMAT_ABGR8888);

		texture = SDL_CreateTextureFromSurface(renderer, s);

		SDL_FreeSurface(s);
	}
}

void mns_Shutdown()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void mns_Update()
{
	SDL_Rect dest;

	dest.x = 10;
	dest.y = 10;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void mns_InitFrame()
{
	SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255);
	SDL_RenderClear(renderer);
}

void mns_RenderFrame()
{
	SDL_RenderPresent(renderer);
}

void mns_PollEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			shouldRun = 0;
			break;

		case SDL_MOUSEBUTTONDOWN:
		{
			int mx, my;
			uint32_t ms = SDL_GetMouseState(&mx, &my);
			printf("mouse state: %d\tx: %d\ty: %d\n", ms, mx, my);
			break;
		}

		default:
			break;
		}
	}
}