#include "Game.h"

namespace game
{
    Game::Game()
    {
        Reset();
    }
    
    Game::~Game()
    {
        SelectedPlate = NULL;

        for (int i = 0; i < PressurePlates.size(); ++i)
        {
            delete PressurePlates[i];
        }
        PressurePlates.clear();
    }

    void Game::Reset()
    {
        Attempts = 0;
        SelectedPlate = NULL;

        for (int i = 0; i < PressurePlates.size(); ++i)
        {
            delete PressurePlates[i];
        }
        PressurePlates.clear();
        Solution.clear();
    }

    void Game::GenerateNewPuzzle()
    {
        // generate the pressure plates
        int count = rand() % MAX_PLATES + 1;
        int row = 0;
        std::vector<int> plate_numbers;

        for (int i = 0; i < count; ++i)
        {
            if (row == 0 && i >= 5)
            {
                row = 1;
            }
            PressurePlates.push_back(new PressurePlate(i, 50 + i * (PressurePlate::PLATE_WIDTH + 20), 50 + row * (PressurePlate::PLATE_WIDTH + 20)));
            plate_numbers.push_back(i);
        }

        // generate the solution
        int index;
        while (plate_numbers.size() > 0)
        {
            index = rand() % plate_numbers.size();
            Solution.push_back(plate_numbers[index]);
            plate_numbers.erase(plate_numbers.begin() + index);
        }
    }

    void Game::Render(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < PressurePlates.size(); ++i)
        {
            PressurePlates[i]->Render(renderer);
        }
        
        SDL_RenderPresent(renderer);
    }

    bool Game::OnMouseEvent(SDL_Event event)
    {
        for (int i = 0; i < PressurePlates.size(); ++i)
        {
            if (PressurePlates[i]->OnMouseEvent(event))
            {
                SelectedPlate = PressurePlates[i];
            }
        }

        return false;
    }
}