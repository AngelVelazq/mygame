#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow(
        "Raycasting Game",               // Window title
        SDL_WINDOWPOS_CENTERED,          // X position (centered)
        SDL_WINDOWPOS_CENTERED,          // Y position (centered)
        800,                             // Width
        600,                             // Height
        SDL_WINDOW_SHOWN                 // Flags
    );

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,                          // Window to render to
        -1,                              // Index of the rendering driver (-1 to use the first available)
        SDL_RENDERER_ACCELERATED         // Use hardware acceleration
    );

    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    SDL_Event e;
    int quit = 0;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Set the draw color (e.g., white background)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        
        // Clear the window with the draw color
        SDL_RenderClear(renderer);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup and close the window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
