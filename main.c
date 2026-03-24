#include <stdio.h>
#include <math.h>
#include "raylib.h"

#define ROWS 15
#define COLUMNS 19

const int gameWidth = COLUMNS * 32;
const int gameHeight = ROWS * 32;

int main() 
{
    int map[ROWS][COLUMNS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,2,1},
    {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,2,1,1,1,1,1,2,1,2,1,1,2,1},
    {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
    {1,2,1,1,2,1,1,1,0,0,0,1,1,1,2,1,1,2,1},
    {1,2,1,1,2,1,0,0,0,0,0,0,0,1,2,1,1,2,1},
    {1,2,1,1,2,1,0,1,1,1,1,1,0,1,2,1,1,2,1},
    {1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1},
    {1,2,1,1,2,1,1,2,1,1,2,1,1,2,1,1,2,2,1},
    {1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1},
    {1,1,2,1,2,1,2,1,1,1,1,1,2,1,2,1,2,1,1},
    {1,2,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int tileSize = 32;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(800, 600, "Pac-Man");

    RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);

    SetTargetFPS(60);

    while (!WindowShouldClose()) 
    {
        BeginTextureMode(target);
        
        ClearBackground(BLACK); 

        for (int i = 0; i < ROWS; i++)  
        {
            for (int j = 0; j < COLUMNS; j++)
            {

                int tile = map[i][j];

                if (tile == 1) 
                {
                    DrawRectangle(j * tileSize, i * tileSize, tileSize, tileSize, DARKBLUE);
                }

                if (tile == 2) 
                {
                    DrawCircle(j * tileSize + tileSize/2,
                            i * tileSize + tileSize/2,
                            4,
                            WHITE);
                }
            }
        }
        EndTextureMode();

        BeginDrawing();

        float scale = fmin(
            (float)GetScreenWidth() / gameWidth,
            (float)GetScreenHeight() / gameHeight
        );

        DrawTexturePro(
            target.texture,
            (Rectangle){0, 0, gameWidth, -gameHeight},
            (Rectangle){
                (GetScreenWidth() - gameWidth * scale) / 2,
                (GetScreenHeight() - gameHeight * scale) / 2,
                gameWidth * scale,
                gameHeight * scale
            },
            (Vector2){0, 0},
            0.0f,
            WHITE
        );
        
        if (IsKeyPressed(KEY_F)) ToggleFullscreen();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}