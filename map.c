#include <stdio.h>
#include <math.h>
#include "map.h"
#include "raylib.h"

void renderMap(int map[ROWS][COLUMNS])
{
    //BeginTextureMode(target);
        ClearBackground(BLACK); 
        for (int i = 0; i < ROWS; i++)  
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                int tile = map[i][j];
                if (tile == 1) DrawRectangle(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKBLUE);
                if (tile == 2)DrawCircle(j * TILE_SIZE + TILE_SIZE/2,
                                i * TILE_SIZE + TILE_SIZE/2,
                                4,
                                WHITE);
            }
        }
    //EndTextureMode();
}

void drawMap(RenderTexture2D target, int map[ROWS][COLUMNS])
{
    BeginDrawing();
        float scale = fmin(
            (float)GetScreenWidth() / GAME_WIDTH,
            (float)GetScreenHeight() / GAME_HEIGHT
        );
        DrawTexturePro(
            target.texture,
            (Rectangle){0, 0, GAME_WIDTH, -GAME_HEIGHT},
            (Rectangle){
                (GetScreenWidth() - GAME_WIDTH * scale) / 2,
                (GetScreenHeight() - GAME_HEIGHT * scale) / 2,
                GAME_WIDTH * scale,
                GAME_HEIGHT * scale
            },
            (Vector2){0, 0},
            0.0f,
            WHITE
        );
    EndDrawing();
}