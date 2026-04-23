#include <stdio.h>
#include <math.h>
#include "raylib.h"

#include "map.h"
#include "pacman.h"

#define MOVE_DELAY 0.16f

int map[ROWS][COLUMNS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int main() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(800, 600, "Pac-Man");

    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    SetTargetFPS(60);

    PacMan_t pacman = NULL;
    pacman = makePacMan(pacman, 1, 1); 

    while (!WindowShouldClose()) 
    {
        //TEXTURES AND WINDOW STUFF
        BeginTextureMode(target);

            renderMap(map);
            drawPacMan(pacman);

        EndTextureMode();

        drawMap(target, map);

        if (IsKeyPressed(KEY_F)) ToggleFullscreen();

        //GAME LOGIC

        getPacmanInput(pacman);

        // if(checkCollision(pacman, map) == 1)
        // {
        //     updatePacMan(pacman);
        // }

        static float moveTimer = 0;
        moveTimer += GetFrameTime();

        if (moveTimer >= MOVE_DELAY)
        {
            if(checkNextDirection(pacman, map) == 1)
            {
                updateDirection(pacman);
            }
            if(checkDirection(pacman, map) == 1)
            {
                updatePacMan(pacman, map);
            }
            moveTimer = 0;
        }
    }
    CloseWindow();
    return 0;
}