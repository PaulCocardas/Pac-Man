#include <stdio.h>
#include <math.h>
#include "raylib.h"

#include "map.h"
#include "pacman.h"

int map[ROWS][COLUMNS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
    {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
    {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,1,1,1,2,2,2,2,0,0,0,2,2,2,2,1,1,1,1},
    {1,1,1,1,2,2,2,2,0,0,0,2,2,2,2,1,1,1,1},
    {1,1,1,1,2,2,2,2,0,0,0,2,2,2,2,1,1,1,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
    {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
    {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    // 0 = empty, 1 = wall, 2 = pellet

int main() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(800, 600, "Pac-Man");

    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    SetTargetFPS(60);

    PacMan_t pacman = NULL;
    pacman = makePacMan(pacman, 9, 7); //Initialize Pac-Man in the middle, empty part of the map

    while (!WindowShouldClose()) 
    {
        //TEXTTURES AND WINDOW STUFF
        BeginTextureMode(target);

            renderMap(map);
            drawPacMan(pacman);

        EndTextureMode();

        drawMap(target, map);

        if (IsKeyPressed(KEY_F)) ToggleFullscreen();

        //GAME LOGIC

        getPacmanInput(pacman);
        if(!checkCollision(pacman, map))
        {
            updatePacMan(pacman, map);
        }
    }
    CloseWindow();
    return 0;
}