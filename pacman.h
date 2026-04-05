#ifndef PACMAN_H
#define PACMAN_H

#include <stdio.h>
#include "raylib.h"
#include "map.h"

typedef struct PacMan* PacMan_t;

void drawPacMan(PacMan_t pacman);
PacMan_t makePacMan(PacMan_t pacman, float x, float y);
int checkCollision(PacMan_t pacman, int map[ROWS][COLUMNS]);
void getPacmanInput(PacMan_t pacman);
void updatePacMan(PacMan_t pacman, int map[ROWS][COLUMNS]);
int isWall(int, int, int map[ROWS][COLUMNS]);

#endif