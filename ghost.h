#ifndef GHOST_H
#define GHOST_H

#include <stdio.h>
#include "raylib.h"
#include "pacman.h"
#include "map.h"

typedef struct Ghost* Ghost_t;

void drawGhost(Ghost_t ghost);
Ghost_t makeGhost(Ghost_t ghost, float x, float y, Color color);
void updateGhostStatusRed(Ghost_t ghost);
void updateGhostStatusPink(Ghost_t ghost);
int calcPacmanGhostDistance(PacMan_t pacman, Vector2 ghost_position); //euclidean distance between pacman and ghost
void updateGhostDirection(Ghost_t ghost, PacMan_t pacman, int map[ROWS][COLUMNS]);
void updateGhostPosition(Ghost_t ghost);
int getGhostStatus(Ghost_t ghost);
int checkIntersection(Ghost_t ghost, int map[ROWS][COLUMNS]);

#endif 