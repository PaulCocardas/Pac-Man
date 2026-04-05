#include <stdio.h>
#include <math.h>
#include "raylib.h"

#include "map.h"

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

typedef struct {
    Vector2 position;
    Vector2 direction;
    Vector2 nextDirection;
    float speed;
    float radius;
    Color color;
} PacMan;

void makePacMan(PacMan* pacman, float x, float y) {
    pacman->position = (Vector2){x, y};
    pacman->direction = (Vector2){1, 0};
    pacman->nextDirection = (Vector2){1, 0};
    pacman->speed = 0.075f;
    pacman->radius = 16.0f;
    pacman->color = YELLOW;
}

int checkCollision(PacMan* pacman) {
    float next_x = pacman->position.x + pacman->nextDirection.x * pacman->speed;
    float next_y = pacman->position.y + pacman->nextDirection.y * pacman->speed;

    int next_column = (int)floorf(next_x);
    int next_row = (int)floorf(next_y);

    if (next_column < 0 || next_column >= COLUMNS || next_row < 0 || next_row >= ROWS) return 1;
    return map[next_row][next_column] == 1;
}


int main() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(800, 600, "Pac-Man");

    RenderTexture2D target = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);

    SetTargetFPS(60);

    PacMan pacman;
    makePacMan(&pacman, 9, 7); //Initialize Pac-Man in the middle, empty part of the map

    while (!WindowShouldClose()) 
    {
        BeginTextureMode(target);
            renderMap(map);
            DrawCircle(pacman.position.x * TILE_SIZE + TILE_SIZE/2,
                    pacman.position.y * TILE_SIZE + TILE_SIZE/2,
                    pacman.radius,
                    pacman.color);
        EndTextureMode();

        drawMap(target, map);

                
        if (IsKeyPressed(KEY_F)) ToggleFullscreen();

        if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) pacman.nextDirection = (Vector2){1, 0};
        if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) pacman.nextDirection = (Vector2){-1, 0};
        if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) pacman.nextDirection = (Vector2){0, -1};
        if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) pacman.nextDirection = (Vector2){0, 1};

        if (!checkCollision(&pacman)) {
            float pacman_center_x = pacman.position.x * TILE_SIZE + TILE_SIZE/2;
            float pacman_center_y = pacman.position.y * TILE_SIZE + TILE_SIZE/2;

            
            pacman.position.x += pacman.nextDirection.x * pacman.speed;
            pacman.position.y += pacman.nextDirection.y * pacman.speed;
        }
    }
    CloseWindow();
    return 0;
}