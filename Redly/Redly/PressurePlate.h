#pragma once
#include <SDL.h>

namespace game
{
    class PressurePlate
    {
    public:
        static const int PLATE_WIDTH = 64;
        static const int PLATE_HEIGHT = 64;

        PressurePlate(int plate_number, int x, int y);

        inline int GetPlateNumber() { return PlateNumber; }

        void Activate();
        void SetInvalid();

        void Render(SDL_Renderer* renderer);
        bool OnMouseEvent(SDL_Event event);

    private:
        enum State
        {
            Inactive,
            Valid,
            Invalid
        };

        State CurrentState;
        SDL_Rect Rect;
        int PlateNumber;
    };
}