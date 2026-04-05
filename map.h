#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include "raylib.h"

#define ROWS 15
#define COLUMNS 19

#define TILE_SIZE 33

#define GAME_WIDTH (COLUMNS * TILE_SIZE)
#define GAME_HEIGHT (ROWS * TILE_SIZE)

void renderMap(int map[ROWS][COLUMNS]);
void drawMap(RenderTexture2D,int map[ROWS][COLUMNS]);

#endif