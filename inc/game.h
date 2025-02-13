#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

extern SDL_Window *window;
extern SDL_Surface *screenSurface;

bool init_game(void);
void cleanup_game(void);

#endif /* GAME_H */
