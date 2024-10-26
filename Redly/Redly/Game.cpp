#include "Game.h"

namespace game
{
    Game::Game(int width, int height, SDL_Texture* opendoor, SDL_Texture* closeddoor)
        : Opendoor(opendoor)
        , Closeddoor(closeddoor)
        , Attempts(0)
        , CorrectPlates(0)
        , SelectedPlate(NULL)
        , CurrentState(State::Incomplete)
        , Width(width)
        , Height(height)
    {
        CenterPosX = Width / 2;
        CenterPosY = Height / 2;

        Door.w = 80;
        Door.h = 90;
        Door.x = CenterPosX - Door.w / 2;
        Door.y = Height - 100 - Door.h / 2;
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
        CorrectPlates = 0;
        SelectedPlate = NULL;
        CurrentState = State::Incomplete;

        for (int i = 0; i < PressurePlates.size(); ++i)
        {
            delete PressurePlates[i];
        }
        PressurePlates.clear();
        Solution.clear();
    }

    void Game::GenerateNewPuzzle()
    {
        Reset();

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

    void Game::ValidatePlate()
    {
        if (SelectedPlate->GetPlateNumber() == Solution[CorrectPlates])
        {
            SelectedPlate->Activate();
            CorrectPlates += 1;

            if (Solution.size() == CorrectPlates)
            {
                CurrentState = State::Complete;
            }
        }
        else
        {
            SelectedPlate->SetInvalid();
        }
    }

    void Game::Render(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        switch (CurrentState)
        {
        case State::Incomplete:
        {
            // plates
            for (int i = 0; i < PressurePlates.size(); ++i)
            {
                PressurePlates[i]->Render(renderer);
            }

            // locked door
            SDL_RenderCopy(renderer, Closeddoor, NULL, &Door);

            break;
        }
        case State::Complete:
        {
            // plates
            for (int i = 0; i < PressurePlates.size(); ++i)
            {
                PressurePlates[i]->Render(renderer);
            }

            // unlocked door
            SDL_RenderCopy(renderer, Opendoor, NULL, &Door);

            // New Puzzle Button

            // 
            break;
        }
        }
        
        
        SDL_RenderPresent(renderer);
    }

    bool Game::OnMouseEvent(SDL_Event event)
    {
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
        {
            if (event.button.button != SDL_BUTTON_LEFT)
            {
                break;
            }

            switch (CurrentState)
            {
            case State::Incomplete:
            {
                for (int i = 0; i < PressurePlates.size(); ++i)
                {
                    if (PressurePlates[i]->OnMouseEvent(event))
                    {
                        SelectedPlate = PressurePlates[i];
                        break;
                    }
                }
                break;
            }
            case State::Complete:
            {
                break;
            }
            }
            
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            if (event.button.button != SDL_BUTTON_LEFT)
            {
                break;
            }

            switch (CurrentState)
            {
            case State::Incomplete:
            {
                if (SelectedPlate == NULL)
                {
                    break;
                }

                if (SelectedPlate->OnMouseEvent(event))
                {
                    // touch up is inside the same plate
                    // check if this plate is the next in our solution
                    ValidatePlate();
                }

                // done handling clicks, clear the selected plate
                SelectedPlate = NULL;
                break;
            }
            case State::Complete:
            {
                break;
            }
            }

            break;
        }
        }

        return false;
    }
}