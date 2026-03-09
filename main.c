#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>

// Dimensions de la fenêtre (basées sur 15x9 cases de 64 pixels)
#define TILE_SIZE 64
#define MAP_WIDTH 15
#define MAP_HEIGHT 9

// Structure de la Salle (Version simplifiée pour commencer)
typedef struct {
    char grid[MAP_HEIGHT][MAP_WIDTH];
} Room;

// Une salle de test écrite "en dur" (Hardcoded)
Room room_test = {
    {
        {'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},
        {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
        {'W',' ','R',' ',' ',' ',' ',' ',' ',' ',' ','R',' ',' ','W'},
        {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
        {'W',' ',' ',' ',' ','G','G','G',' ',' ',' ',' ',' ',' ','W'},
        {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
        {'W',' ','R',' ',' ',' ',' ',' ',' ',' ',' ','R',' ',' ','W'},
        {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
        {'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'}
    }
};

int main(int argc, char* argv[]) {
    // 1. Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    SDL_Window* window = SDL_CreateWindow("The Binding of Briatte - Dev Mode", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;

    // 2. Boucle principale (Game Loop)
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        // 3. Rendu (Dessiner la salle)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fond noir
        SDL_RenderClear(renderer);

        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                SDL_Rect tile = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                
                if (room_test.grid[y][x] == 'W') {
                    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gris pour Murs
                } else if (room_test.grid[y][x] == 'R') {
                    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);   // Marron pour Rochers
                } else if (room_test.grid[y][x] == 'G') {
                    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);    // Noir foncé pour Gaps
                } else {
                    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Blanc cassé pour Sol
                }
                SDL_RenderFillRect(renderer, &tile);
                
                // Dessiner les bordures des cases pour y voir clair
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &tile);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}