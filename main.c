#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAP_HEIGHT 9
#define MAP_WIDTH 15

// La estructura de la sala
typedef struct {
    char grid[MAP_HEIGHT][MAP_WIDTH];
} Room;

// La estructura del jugador
typedef struct {
    int x, y;
} Player;

// 1. Dibujar la sala en la terminal
void afficher_salle(Room *s, Player *p) {
    // Limpiar la pantalla (esto funciona en Windows)
    system("cls"); 

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == p->y && j == p->x) {
                printf("B "); // 'B' de Briatte
            } else {
                printf("%c ", s->grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nUtilisez Z (haut), S (bas), Q (gauche), D (droite). 'X' pour quitter.\n");
}

int main() {
    // 2. Crear una sala de prueba
    Room salle = {
        {
            {'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'},
            {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
            {'W',' ','R',' ',' ',' ',' ',' ',' ',' ',' ','R',' ',' ','W'},
            {'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W'},
            {'W',' ',' ',' ',' ','G','G','G',' ',' ',' ',' ',' ',' ','W'},
            {'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'}
        }
    };

    Player briatte = {7, 3}; // Posición inicial
    char commande;
    bool running = true;

    // 3. Bucle del juego
    while (running == true) {
        afficher_salle(&salle, &briatte);

        printf("Action : ");
        scanf(" %c", &commande); // El espacio antes de %c es vital

        int nextX = briatte.x;
        int nextY = briatte.y;

        if (commande == 'z') nextY--;
        if (commande == 's') nextY++;
        if (commande == 'q') nextX--;
        if (commande == 'd') nextX++;
        if (commande == 'x') running = false;

        // 4. Colisión simple
        if (salle.grid[nextY][nextX] != 'W' && salle.grid[nextY][nextX] != 'R') {
            briatte.x = nextX;
            briatte.y = nextY;
        }
    }

    return 0;
}