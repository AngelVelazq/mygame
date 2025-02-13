#include "../inc/game.h"
#include <stdio.h>
#include <SDL2/SDL.h>

/* SDL Window and Surface */
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;

/* Initialize SDL */
bool init_game(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Raycasting Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    screenSurface = SDL_GetWindowSurface(window);
    return true;
}

/* Cleanup SDL */
void cleanup_game(void) {
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
