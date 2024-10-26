#include <SDL.h>
#include <stdio.h>
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* closeddoor_texture = NULL;
	SDL_Texture* opendoor_texture = NULL;

	game::Game* game = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Redly Test Assignment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, 0);
			SDL_Surface* closed_image = SDL_LoadBMP("../resources/closeddoor.bmp");
			SDL_Surface* open_image = SDL_LoadBMP("../resources/opendoor.bmp");
			
			closeddoor_texture = SDL_CreateTextureFromSurface(renderer,
				closed_image);
			opendoor_texture = SDL_CreateTextureFromSurface(renderer,
				open_image);
			game = new game::Game(SCREEN_WIDTH, SCREEN_HEIGHT, opendoor_texture, closeddoor_texture);

			if (game != NULL)
			{
				game->GenerateNewPuzzle();

				SDL_UpdateWindowSurface(window);

				// hack to force window to stay open
				SDL_Event event;
				bool quit = false;


				// handle events
				while (!quit)
				{
					SDL_WaitEvent(&event);

					switch (event.type)
					{
					case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
						game->OnMouseEvent(event);
						break;
					case SDL_QUIT:
						quit = true;
						break;
					}

					game->Render(renderer);
				}
			}
		}
	}

	// cleanup
	if (game != NULL)
	{
		delete game;
	}

	SDL_DestroyTexture(closeddoor_texture);
	SDL_DestroyTexture(opendoor_texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
