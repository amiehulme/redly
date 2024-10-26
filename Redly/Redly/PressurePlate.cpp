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

    void PressurePlate::Activate()
    {
        CurrentState = Valid;
    }

    void PressurePlate::SetInvalid()
    {
        CurrentState = Invalid;
    }

    bool PressurePlate::OnMouseEvent(SDL_Event event)
    {
        // skip valid plates
        if (CurrentState == Valid)
        {
            return false;
        }

        // check if we're touching the plate
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;

            if (mouseX >= Rect.x && mouseX <= (Rect.x + PLATE_WIDTH))
            {
                if (mouseY >= Rect.y && mouseY <= (Rect.y + PLATE_HEIGHT))
                {
                    return true;
                }
            }
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
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            break;
        }
        case State::Invalid:
        {
            // Set render color to red
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            break;
        }
        }

        // Render rect
        SDL_RenderFillRect(renderer, &Rect);
    }
}