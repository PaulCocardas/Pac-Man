#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"

#include "map.h"
#include "pacman.h"
#include "ghost.h"

#define MOVE_DELAY 0.2f

typedef enum {
    STATE_START,
    STATE_GAMEPLAY,
    STATE_GAMEOVER,
    STATE_VICTORY
} GameState;

int pelletCount = 137;

int main() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Pac-Man");
    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
    SetTargetFPS(60);

    PacMan_t pacman = NULL;
    Ghost_t ghost_red = NULL;
    Ghost_t ghost_pink = NULL;

    int score = 0;
    float moveTimer = 0;
    float powerUpTimer = 0;
    
    GameState state = STATE_START;

    while (!WindowShouldClose()) 
    {
        if(IsKeyPressed(KEY_F)) ToggleFullscreen();
        
        // --- 1. STATE MACHINE LOGIC ---
        switch(state) 
        {
            case STATE_START:
                if (IsKeyPressed(KEY_ENTER)) {
                    // Initialize objects on transition to Gameplay
                    pelletCount = 137;
                    resetMap(map, backup_map);
                    if(pacman) free(pacman);
                    if(ghost_red) free(ghost_red);
                    if(ghost_pink) free(ghost_pink);
                    
                    pacman = makePacMan(pacman, 5, 3); 
                    ghost_red = makeGhost(ghost_red, 5, 9, RED);
                    ghost_pink = makeGhost(ghost_pink, 5, 12, PINK);
                    score = 0;
                    moveTimer = 0;
                    powerUpTimer = 0;
                    state = STATE_GAMEPLAY;
                }
                break;

            case STATE_GAMEPLAY:
                
                switch(checkCurrentTile(pacman, map))
                {
                    case 2:
                        score += 100;
                        pelletCount--;
                        updateTile(pacman, map);
                        break;
                    case 3:
                        score += 500;
                        pelletCount--;
                        powerUp(pacman);
                        freightenGhost(ghost_red);
                        freightenGhost(ghost_pink);
                        powerUpTimer = 5.0f;
                        updateTile(pacman, map);
                        break;
                    default:
                        break;
                }

                if (checkWinCondition(pelletCount)) {
                    state = STATE_VICTORY;
                }

                if(checkStatus(pacman) == 1)
                {
                    powerUpTimer -= GetFrameTime();
                    if(powerUpTimer <= 0)
                    {   
                        powerDown(pacman);
                        unfreightenRed(ghost_red);
                        unfreightenPink(ghost_pink);
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
                        //if(checkIntersection(ghost_red, map) == 1)
                            updateGhostDirection(ghost_red, pacman, map);
                        updateGhostPosition(ghost_red);
                    }
                    else
                    {
                        updateGhostDirectionFreightened(ghost_red, pacman, map);
                        updateGhostPosition(ghost_red);
                    }

                    if(getGhostStatus(ghost_pink) == 0)
                    {
                        //if(checkIntersection(ghost_pink, map) == 1)
                            updateGhostDirection(ghost_pink, pacman, map);
                        updateGhostPosition(ghost_pink);
                    }
                    else
                    {
                        updateGhostDirectionFreightened(ghost_pink, pacman, map);
                        updateGhostPosition(ghost_pink);
                    }
                        
                    moveTimer = 0;
                }

                //verifica daca urmatoarea poz a lui pacman e poitia unei fantome si daca poziti urm a fantomei este cea a lui pacman pt collision ai bun
                if(checkCollision(ghost_red, pacman)) 
                {
                    if (getGhostStatus(ghost_red) == 0) state = STATE_GAMEOVER;
                    else 
                    {
                        unfreightenRed(ghost_red); 
                        resetGhostPosition(ghost_red, 12, 9);
                    }
                }
                if(checkCollision(ghost_pink, pacman)) 
                {
                    if (getGhostStatus(ghost_pink) == 0) state = STATE_GAMEOVER;
                    else 
                    {  
                        unfreightenPink(ghost_pink); 
                        resetGhostPosition(ghost_pink, 12, 7);
                    } 
                }
                // if ((pacman_pos.x == red_pos.x && pacman_pos.y == red_pos.y)) 
                // {
                //     if (getGhostStatus(ghost_red) == 0) state = STATE_GAMEOVER;
                //     else 
                //     {
                //         unfreightenRed(ghost_red); 
                //         resetGhostPosition(ghost_red, 12, 9);
                //     }
                // }
                // if ((pacman_pos.x == pink_pos.x && pacman_pos.y == pink_pos.y)) 
                // {
                //     if (getGhostStatus(ghost_pink) == 0) state = STATE_GAMEOVER;
                //     else 
                //     {  
                //         unfreightenPink(ghost_pink); 
                //         resetGhostPosition(ghost_pink, 12, 7);
                //     } 
                // }
                break;

            case STATE_GAMEOVER:
            case STATE_VICTORY:
                pelletCount = 137;
                if (IsKeyPressed(KEY_ENTER)) {
                    state = STATE_START;
                }
                break;
        }

        // --- 2. RENDER FLOW ---
        BeginTextureMode(target);
            ClearBackground(BLACK);

            if (state == STATE_GAMEPLAY) {
                renderMap(map);
                drawPacMan(pacman);
                drawGhost(ghost_red);
                drawGhost(ghost_pink);
                DrawText(TextFormat("POWER UP: %.1f", powerUpTimer), 10, 10, 20, RAYWHITE);
                DrawText(TextFormat("SCORE: %05d", score), GAME_WIDTH - 175, 10, 20, RAYWHITE);
            } 
            else if (state == STATE_START) {
                DrawText("PAC-MAN", GAME_WIDTH / 2 - MeasureText("PAC-MAN", 40) / 2, GAME_HEIGHT / 2 - 60, 40, YELLOW);
                DrawText("PRESS ENTER TO PLAY", GAME_WIDTH / 2 - MeasureText("PRESS ENTER TO PLAY", 20) / 2, GAME_HEIGHT / 2 + 10, 20, WHITE);
            } 
            else if (state == STATE_GAMEOVER) {
                DrawText("GAME OVER", GAME_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, GAME_HEIGHT / 2 - 60, 40, RED);
                DrawText(TextFormat("FINAL SCORE: %05d", score), GAME_WIDTH / 2 - MeasureText(TextFormat("FINAL SCORE: %05d", score), 20) / 2, GAME_HEIGHT / 2 - 10, 20, WHITE);
                DrawText("PRESS ENTER FOR MAIN MENU", GAME_WIDTH / 2 - MeasureText("PRESS ENTER FOR MAIN MENU", 16) / 2, GAME_HEIGHT / 2 + 40, 16, GRAY);
            } 
            else if (state == STATE_VICTORY) {
                DrawText("VICTORY!", GAME_WIDTH / 2 - MeasureText("VICTORY!", 40) / 2, GAME_HEIGHT / 2 - 60, 40, GREEN);
                DrawText(TextFormat("FINAL SCORE: %05d", score), GAME_WIDTH / 2 - MeasureText(TextFormat("FINAL SCORE: %05d", score), 20) / 2, GAME_HEIGHT / 2 - 10, 20, WHITE);
                DrawText("PRESS ENTER FOR MAIN MENU", GAME_WIDTH / 2 - MeasureText("PRESS ENTER FOR MAIN MENU", 16) / 2, GAME_HEIGHT / 2 + 40, 16, GRAY);
            }
        EndTextureMode();

        drawMap(target, map);
    }

    if(pacman) free(pacman);
    if(ghost_red) free(ghost_red);
    if(ghost_pink) free(ghost_pink);

    CloseWindow();
    return 0;
}