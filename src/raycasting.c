#include "../inc/raycasting.h"
#include <math.h>
#include <SDL2/SDL.h>
#include "../inc/game.h"

/* Player position and direction */
float playerX = 5.0f, playerY = 5.0f;
float playerDirX = -1.0f, playerDirY = 0.0f;

/* Camera plane (for correct FOV) */
float planeX = 0.0f, planeY = 0.66f; // 0.66 for ~60-degree FOV

/* Map */
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

/* Change player angle */
void changePlayerAngle(float angle) {
    float radians = angle * M_PI / 180.0f;
    playerDirX = cos(radians);
    playerDirY = sin(radians);
    planeX = -playerDirY * 0.66f;  // Keep perpendicular to direction
    planeY = playerDirX * 0.66f;
}

/* Raycasting function */
void raycast(SDL_Surface *screenSurface) {
    SDL_Rect groundRect;
    
    /* Clear screen with sky and ground */
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 255)); /* Sky (Blue) */
    groundRect = (SDL_Rect){0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};  /* Ground (Green) */
    SDL_FillRect(screenSurface, &groundRect, SDL_MapRGB(screenSurface->format, 0, 255, 0));

    /* Raycasting loop */
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        /* Compute ray direction */
        float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
        float rayDirX = playerDirX + planeX * cameraX;
        float rayDirY = playerDirY + planeY * cameraX;

        /* Initial grid cell */
        int mapX = (int)playerX;
        int mapY = (int)playerY;

        /* Ray length from one x or y-side to next x or y-side */
        float deltaDistX = fabs(1 / rayDirX);
        float deltaDistY = fabs(1 / rayDirY);
        float sideDistX, sideDistY;
        
        /* Step direction */
        int stepX, stepY;
        int hit = 0;
        int side; // Vertical or horizontal wall hit 

        /* Set initial step and side distances */
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (playerX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - playerX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (playerY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - playerY) * deltaDistY;
        }

        /* Perform DDA algorithm */
        while (!hit) {
            /* Move to next map square */
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // Vertical hit
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // Horizontal hit
            }

            /* Check if ray hit a wall */
            if (map[mapY][mapX] == 1) hit = 1;
        }

        /* Calculate wall distance */
        float perpWallDist = (side == 0) ? 
            (mapX - playerX + (1 - stepX) / 2) / rayDirX :
            (mapY - playerY + (1 - stepY) / 2) / rayDirY;

        /* Calculate wall height */
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
        SDL_Rect wallRect = {x, SCREEN_HEIGHT / 2 - lineHeight / 2, 1, lineHeight};

        /* Color the walls based on side */
        Uint32 wallColor = (side == 0) ? SDL_MapRGB(screenSurface->format, 200, 200, 200) :
                                          SDL_MapRGB(screenSurface->format, 128, 128, 128);
        SDL_FillRect(screenSurface, &wallRect, wallColor);
    }
}
