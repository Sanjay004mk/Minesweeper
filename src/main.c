#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

void initSDL()
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
}

void PollEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		default:
			break;
		}
	}
}


int main(int argc, char** argv)
{
	initSDL();

	while (1)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);

		PollEvents();
	}

	return 0;
}