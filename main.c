#include <stdio.h>
#include <math.h>
#include "raylib.h"

#include "map.h"
#include "pacman.h"
#include "ghost.h"

#define MOVE_DELAY 0.2f

int map[ROWS][COLUMNS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
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
    {1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int main() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(800, 600, "Pac-Man");

    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    SetTargetFPS(60);

    PacMan_t pacman = NULL;
    pacman = makePacMan(pacman, 5, 3); 

    Ghost_t ghost_red = NULL;
    ghost_red = makeGhost(ghost_red, 12, 9, RED);

    Ghost_t ghost_pink = NULL;
    ghost_pink = makeGhost(ghost_pink, 12, 7, PINK);

    int score = 0;
    static float moveTimer = 0;
    static float powerUpTimer = 0;

    while (!WindowShouldClose()) 
    {
        if(IsKeyPressed(KEY_F)) ToggleFullscreen();
        
        //TEXTURES AND WINDOW STUFF
        BeginTextureMode(target);

            renderMap(map);
            drawPacMan(pacman);
            drawGhost(ghost_red);
            drawGhost(ghost_pink);
            DrawText(TextFormat("POWER UP: %.1f", powerUpTimer), 10, 10, 20, RAYWHITE);
            DrawText(TextFormat("SCORE: %05d", score), GAME_WIDTH - 175, 10, 20, RAYWHITE);

        EndTextureMode();

        drawMap(target, map);

        //GAME LOGIC
        switch(checkCurrentTile(pacman,map))
        {
            case 2:
                score += 100;
                updateTile(pacman, map);
                break;
            case 3:
                score += 500;
                powerUp(pacman);
                updateGhostStatusRed(ghost_red);
                updateGhostStatusPink(ghost_pink);
                powerUpTimer = 5.0f;
                updateTile(pacman, map);
                break;
            default:
                break;
        }

        if(checkStatus(pacman) == 1)
        {
            powerUpTimer -= GetFrameTime();
            if(powerUpTimer <= 0)
            {   
                powerDown(pacman);
                updateGhostStatusRed(ghost_red);
                updateGhostStatusPink(ghost_pink);
                powerUpTimer = 0;
            }
        }

        getPacmanInput(pacman);

        moveTimer += GetFrameTime();

        if (moveTimer >= MOVE_DELAY)
        {
            if(checkNextDirection(pacman, map) == 1)
                updatePacmanDirection(pacman);
            
            if(checkDirection(pacman, map) == 1)
                updatePacMan(pacman);

            if(getGhostStatus(ghost_red) == 0)
            {
                if(checkIntersection(ghost_red, map) == 1)
                    updateGhostDirection(ghost_red, pacman, map);
                updateGhostPosition(ghost_red);
            }

            if(getGhostStatus(ghost_pink) == 0)
            {
                if(checkIntersection(ghost_pink, map) == 1)
                    updateGhostDirection(ghost_pink, pacman, map);
                updateGhostPosition(ghost_pink);
            }
                
            moveTimer = 0;
        }


    }
    CloseWindow();
    return 0;
}