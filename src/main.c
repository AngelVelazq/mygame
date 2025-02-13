#include "../inc/game.h"
#include "../inc/raycasting.h"

int main() {
    SDL_Event e;
    bool quit = false;
    if (!init_game()) return 1;

    changePlayerAngle(45.0f); /* Set initial angle */
    raycast(screenSurface);
    SDL_UpdateWindowSurface(window);

    /* Event loop */
    while (!quit) {
        while (SDL_PollEvent(&e)) {
           if (e.type == SDL_QUIT) quit = true;
        }
    }

    cleanup_game();
    return 0;
}
