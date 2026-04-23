#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "map.h"
#include "pacman.h"

struct PacMan
{
    Vector2 position;
    Vector2 direction;
    Vector2 nextDirection;
    float radius;
    Color color;
};

void drawPacMan(PacMan_t pacman) 
{
    DrawCircle(pacman->position.x * TILE_SIZE + TILE_SIZE/2,
                    pacman->position.y * TILE_SIZE + TILE_SIZE/2,
                    pacman->radius,
                    pacman->color);
}

PacMan_t makePacMan(PacMan_t pacman, float x, float y)
{
    pacman = malloc(sizeof(struct PacMan));
    pacman->position = (Vector2){x, y};
    pacman->direction = (Vector2){1, 0};
    pacman->nextDirection = (Vector2){1, 0};
    pacman->radius = 16.0f;
    pacman->color = YELLOW;
    return pacman;
}

void getPacmanInput(PacMan_t pacman) 
{
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) pacman->nextDirection = (Vector2){1, 0};
    if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) pacman->nextDirection = (Vector2){-1, 0};
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) pacman->nextDirection = (Vector2){0, -1};
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) pacman->nextDirection = (Vector2){0, 1};
}

int checkDirection(PacMan_t pacman, int map[ROWS][COLUMNS]) 
{
    int next_column = pacman->position.x + pacman->direction.x;
    int next_row = pacman->position.y + pacman->direction.y;

    if(map[next_row][next_column] == 1) return -1; 
    return 1;
}

int checkNextDirection(PacMan_t pacman, int map[ROWS][COLUMNS]) 
{
    int next_column = pacman->position.x + pacman->nextDirection.x;
    int next_row = pacman->position.y + pacman->nextDirection.y;

    if(map[next_row][next_column] == 1) return -1; 
    return 1;
}

void updateDirection(PacMan_t pacman) 
{
    pacman->direction = pacman->nextDirection;
}

void updatePacMan(PacMan_t pacman, int map[ROWS][COLUMNS]) 
{   
    pacman->position.x += pacman->direction.x;
    pacman->position.y += pacman->direction.y;
}

