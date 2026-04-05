#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "raylib.h"
#include "map.h"
#include "pacman.h"

struct PacMan{
    Vector2 position;
    Vector2 direction;
    Vector2 nextDirection;
    float speed;
    float radius;
    Color color;
};

void drawPacMan(PacMan_t pacman) {
    DrawCircle(pacman->position.x * TILE_SIZE + TILE_SIZE/2,
                    pacman->position.y * TILE_SIZE + TILE_SIZE/2,
                    pacman->radius,
                    pacman->color);
}

PacMan_t makePacMan(PacMan_t pacman, float x, float y){
    pacman = malloc(sizeof(struct PacMan));
    pacman->position = (Vector2){x, y};
    pacman->direction = (Vector2){1, 0};
    pacman->nextDirection = (Vector2){1, 0};
    pacman->speed = 0.075f;
    pacman->radius = 16.0f;
    pacman->color = YELLOW;
    return pacman;
}

int checkCollision(PacMan_t pacman, int map[ROWS][COLUMNS]) {
    float next_x = pacman->position.x + pacman->nextDirection.x * pacman->speed;
    float next_y = pacman->position.y + pacman->nextDirection.y * pacman->speed;

    int next_column = (int)floorf(next_x);
    int next_row = (int)floorf(next_y);

    if (next_column < 0 || next_column >= COLUMNS || next_row < 0 || next_row >= ROWS) return 1;
    return map[next_row][next_column] == 1;
}

void getPacmanInput(PacMan_t pacman) {
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) pacman->nextDirection = (Vector2){1, 0};
    if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) pacman->nextDirection = (Vector2){-1, 0};
    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) pacman->nextDirection = (Vector2){0, -1};
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) pacman->nextDirection = (Vector2){0, 1};
}

void updatePacMan(PacMan_t pacman, int map[ROWS][COLUMNS]) {
    if (!checkCollision(pacman, map)) {
        pacman->direction = pacman->nextDirection;
    }
    
    int column = (int)floorf(pacman->position.x);
    int row = (int)floorf(pacman->position.y);

    int column_center = column + TILE_SIZE/2;
    int row_center = row + TILE_SIZE/2;
    
    pacman->position.x += pacman->direction.x * pacman->speed;
    pacman->position.y += pacman->direction.y * pacman->speed;
}