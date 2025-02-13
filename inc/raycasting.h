#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>

/* Player data */
extern float playerX, playerY;
extern float playerDirX, playerDirY;

/* Camera plane */
extern float planeX, planeY;

void raycast(SDL_Surface *screenSurface);
void changePlayerAngle(float angle);

#endif /* RAYCASTING_H */
