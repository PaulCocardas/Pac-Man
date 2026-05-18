#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"
#include "map.h"
#include "ghost.h"

struct Ghost
{
    Vector2 position;
    Vector2 direction;
    float radius;
    Color color;
    int status; // 0 = normal, 1 = frightened
};

static Vector2 directions[4] = {
    {1, 0},   // right
    {-1, 0},  // left
    {0, -1},  // up
    {0, 1}    // down
};

void drawGhost(Ghost_t ghost) 
{
    DrawCircle(ghost->position.x * TILE_SIZE + TILE_SIZE/2,
                    ghost->position.y * TILE_SIZE + TILE_SIZE/2,
                    ghost->radius,
                    ghost->color);
}

Ghost_t makeGhost(Ghost_t ghost, float x, float y, Color color)
{
    ghost = malloc(sizeof(struct Ghost));
    ghost->position = (Vector2){x, y};
    ghost->direction = (Vector2){1, 0};
    ghost->radius = 16.0f;
    ghost->color = color;
    ghost->status = 0;
    return ghost;
}

void freightenGhost(Ghost_t ghost) 
{
    ghost->status = 1;
    ghost->color = BLUE;
}

void unfreightenRed(Ghost_t ghost) 
{
    ghost->status = 0;
    ghost->color = RED;
}

void unfreightenPink(Ghost_t ghost) 
{
    ghost->status = 0;
    ghost->color = PINK;
}

int calcPacmanGhostDistance(PacMan_t pacman, Vector2 ghost_position) 
{
    Vector2 pacmanPos = getPacmanPosition(pacman);
    float dx = pow(pacmanPos.x - ghost_position.x, 2);
    float dy = pow(pacmanPos.y - ghost_position.y, 2);
    return sqrt(dx + dy);
}

void updateGhostDirection(Ghost_t ghost, PacMan_t pacman, int map[ROWS][COLUMNS]) 
{
    int bestDistance = 9999;
    for(int i = 0; i < 4; i++) 
    {
        if(ghost->direction.x == -directions[i].x && ghost->direction.y == -directions[i].y) continue;
        int next_column = ghost->position.x + directions[i].x;
        int next_row = ghost->position.y + directions[i].y;
        if(map[next_row][next_column] != 1) 
        {
            Vector2 next_position = {ghost->position.x + directions[i].x, ghost->position.y + directions[i].y};
            int distance = calcPacmanGhostDistance(pacman, next_position);
            if(distance < bestDistance)             
            {
                bestDistance = distance;
                ghost->direction = directions[i];
            }
        }
    }
}

void updateGhostDirectionFreightened(Ghost_t ghost, PacMan_t pacman, int map[ROWS][COLUMNS]) 
{
    int bestDistance = -1;
    for(int i = 0; i < 4; i++) 
    {
        if(ghost->direction.x == -directions[i].x && ghost->direction.y == -directions[i].y) continue;
        int next_column = ghost->position.x + directions[i].x;
        int next_row = ghost->position.y + directions[i].y;
        if(map[next_row][next_column] != 1) 
        {
            Vector2 next_position = {ghost->position.x + directions[i].x, ghost->position.y + directions[i].y};
            int distance = calcPacmanGhostDistance(pacman, next_position);
            if(distance > bestDistance)             
            {
                bestDistance = distance;
                ghost->direction = directions[i];
            }
        }
    }
}

void updateGhostPosition(Ghost_t ghost) 
{
    ghost->position.x += ghost->direction.x;
    ghost->position.y += ghost->direction.y;
}

int getGhostStatus(Ghost_t ghost) 
{
    return ghost->status;
}

int checkIntersection(Ghost_t ghost, int map[ROWS][COLUMNS]) 
{
   for(int i = 0; i < 4; i++) 
   {
        //if(ghost->direction.x == directions[i].x && ghost->direction.y == directions[i].y) continue;
        int next_column = ghost->position.x + directions[i].x;
        int next_row = ghost->position.y + directions[i].y;
        if(map[next_row][next_column] != 1) 
        {
            return 1;
        }
   }
   return 0;
}

Vector2 getGhostPosition(Ghost_t ghost) 
{
    return ghost->position;
}

void resetGhostPosition(Ghost_t ghost, float x, float y)
{
    ghost->position = (Vector2){x, y};
}

int checkCollision(Ghost_t ghost, PacMan_t pacman)
{
    Vector2 pacmanPos = getPacmanPosition(pacman);
    Vector2 pacmanNextPos = getPacmanNextPosition(pacman);

    Vector2 ghostPos = getGhostPosition(ghost);
    Vector2 ghostNextPos = {ghostPos.x + ghost->direction.x, ghostPos.y + ghost->direction.y};

    if(pacmanPos.x == ghostPos.x && pacmanPos.y == ghostPos.y)
    {
        return 1; 
    }
    // if(pacmanNextPos.x == ghostPos.x && pacmanNextPos.y == ghostPos.y)
    // {
    //     return 1; 
    // }
    // if(pacmanPos.x == ghostNextPos.x && pacmanPos.y == ghostNextPos.y)
    // {
    //     return 1;
    // }
    return 0;
}