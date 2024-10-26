#include <SDL.h>
#include <stdio.h>
#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
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
			game = new game::Game();

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
						switch (event.button.button)
						{
						case SDL_BUTTON_LEFT:
							SDL_ShowSimpleMessageBox(0, "Mouse", "Left button was pressed!", window);
							break;
						case SDL_BUTTON_RIGHT:
							SDL_ShowSimpleMessageBox(0, "Mouse", "Right button was pressed!", window);
							break;
						default:
							SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", window);
							break;
						}
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

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
