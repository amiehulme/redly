#pragma once
#include <SDL.h>
#include <vector>
#include "PressurePlate.h"

namespace game
{
    class Game
    {
    public:
        static const int MAX_PLATES = 10;

        Game();
        ~Game();

        void Reset();
        void GenerateNewPuzzle();

        void Render(SDL_Renderer* renderer);
        bool OnMouseEvent(SDL_Event e);

    private:
        std::vector<PressurePlate*> PressurePlates;
        std::vector<int> Solution;
        int Attempts;
        PressurePlate* SelectedPlate;
    };
}