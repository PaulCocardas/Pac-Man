#include <stdio.h>
#include <math.h>
#include "raylib.h"

#define ROWS 15
#define COLUMNS 19

const int tileSize = 32;


const int gameWidth = COLUMNS * tileSize;
const int gameHeight = ROWS * tileSize;

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
    float next_x = pacman->position.x + pacman->direction.x * pacman->speed;
    float next_y = pacman->position.y + pacman->direction.y * pacman->speed;

    int next_column = (int)floorf(next_x);
    int next_row = (int)floorf(next_y);

    if (next_column < 0 || next_column >= COLUMNS || next_row < 0 || next_row >= ROWS) return 1;
    return map[next_row][next_column] == 1;
}


int main() 
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(800, 600, "Pac-Man");

    RenderTexture2D target = LoadRenderTexture(gameWidth, gameHeight);

    SetTargetFPS(60);

    PacMan pacman;
    makePacMan(&pacman, 9, 7); //Initialize Pac-Man in the middle, empty part of the map

    while (!WindowShouldClose()) 
    {
        // Begin drawing to the off-screen render texture
        BeginTextureMode(target);
        ClearBackground(BLACK); 
        for (int i = 0; i < ROWS; i++)  
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                int tile = map[i][j];
                if (tile == 1) DrawRectangle(j * tileSize, i * tileSize, tileSize, tileSize, DARKBLUE);
                if (tile == 2)DrawCircle(j * tileSize + tileSize/2,
                                i * tileSize + tileSize/2,
                                4,
                                WHITE);
                //Draw the tile based on its type
            }
        }
        DrawCircle(pacman.position.x * tileSize + tileSize/2,
                   pacman.position.y * tileSize + tileSize/2,
                   pacman.radius,
                   pacman.color);
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
        //End drawing to the off-screen render texture

        if(IsKeyPressed(KEY_RIGHT)) pacman.direction = (Vector2){1, 0};
        if(IsKeyPressed(KEY_LEFT)) pacman.direction = (Vector2){-1, 0};
        if(IsKeyPressed(KEY_UP)) pacman.direction = (Vector2){0, -1};
        if(IsKeyPressed(KEY_DOWN)) pacman.direction = (Vector2){0, 1};

        if (!checkCollision(&pacman)) {
            pacman.position.x += pacman.direction.x * pacman.speed;
            pacman.position.y += pacman.direction.y * pacman.speed;
        }
    }
    CloseWindow();
    return 0;
}