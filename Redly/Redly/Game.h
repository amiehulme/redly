#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "PressurePlate.h"

namespace game
{
    class Game
    {
    public:
        static const int MAX_PLATES = 10;

        Game(int width, int height, SDL_Texture* opendoor, SDL_Texture* closeddoor, SDL_Texture* newpuzzletexture);
        ~Game();

        void Reset();
        void GenerateNewPuzzle();

        void Render(SDL_Renderer* renderer);
        bool OnMouseEvent(SDL_Event e);

    private:
        enum State
        {
            Incomplete,
            Complete
        };

        SDL_Texture* Opendoor;
        SDL_Texture* Closeddoor;
        SDL_Texture* NewPuzzleTexture;
        std::vector<PressurePlate*> PressurePlates;
        std::vector<int> Solution;
        int Attempts;
        int CorrectPlates;
        PressurePlate* SelectedPlate;
        State CurrentState;
        SDL_Rect Door;
        SDL_Rect NewPuzzleButton;
        SDL_Rect NewPuzzleText;
        int Width;
        int Height;
        int CenterPosX;
        int CenterPosY;

        void ValidatePlate();
    };
}