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
    int status; // 0 = normal, 1 = powered up
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
    pacman->status = 0;
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

void updatePacmanDirection(PacMan_t pacman) 
{
    pacman->direction = pacman->nextDirection;
}

void updatePacMan(PacMan_t pacman) 
{   
    pacman->position.x += pacman->direction.x;
    pacman->position.y += pacman->direction.y;
}


int checkCurrentTile(PacMan_t pacman, int map[ROWS][COLUMNS]) 
{
    int current_column = pacman->position.x;
    int current_row = pacman->position.y;

    return map[current_row][current_column];
}

void updateTile(PacMan_t pacman, int map[ROWS][COLUMNS]) 
{
    int current_column = pacman->position.x;
    int current_row = pacman->position.y;
    map[current_row][current_column] = 0;
}

void powerUp(PacMan_t pacman)
{
    pacman->status = 1;
    pacman->color = GREEN;
}

void powerDown(PacMan_t pacman)
{
    pacman->status = 0;
    pacman->color = YELLOW;
}

int checkStatus(PacMan_t pacman)
{
    return pacman->status;
}

Vector2 getPacmanPosition(PacMan_t pacman)
{
    return pacman->position;
}

Vector2 getPacmanNextPosition(PacMan_t pacman)
{
    Vector2 next_position;
    next_position.x = pacman->position.x + pacman->direction.x;
    next_position.y = pacman->position.y + pacman->direction.y;
    return next_position;
}