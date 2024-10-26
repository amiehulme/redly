#include "PressurePlate.h"


namespace game
{
    PressurePlate::PressurePlate(int plate_number, int x, int y)
        : PlateNumber(plate_number)
        , CurrentState(State::Inactive)
    {
        Rect.x = x;
        Rect.y = y;
        Rect.w = PLATE_WIDTH;
        Rect.h = PLATE_HEIGHT;
    }

    bool PressurePlate::OnMouseEvent(SDL_Event event)
    {
        // check if we're touching the plate
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
        {
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            break;
        }
        }
        return false;
    }

    void PressurePlate::Render(SDL_Renderer* renderer)
    {
        switch (CurrentState)
        {
        case State::Inactive:
        {
            // Set render color to black
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            break;
        }
        case State::Valid:
        {
            // Set render color to green
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
            break;
        }
        case State::Invalid:
        {
            // Set render color to red
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
            break;
        }
        }

        // Render rect
        SDL_RenderFillRect(renderer, &Rect);
    }
}