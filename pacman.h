#ifndef PACMAN_H
#define PACMAN_H

#include <stdio.h>
#include "raylib.h"
#include "map.h"

typedef struct PacMan* PacMan_t;

void drawPacMan(PacMan_t pacman);
PacMan_t makePacMan(PacMan_t pacman, float x, float y);
int checkDirection(PacMan_t pacman, int map[ROWS][COLUMNS]);
int checkNextDirection(PacMan_t pacman, int map[ROWS][COLUMNS]);
void updateDirection(PacMan_t pacman);
void getPacmanInput(PacMan_t pacman);
void updatePacMan(PacMan_t pacman, int map[ROWS][COLUMNS]);



#endif