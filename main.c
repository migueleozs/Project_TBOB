#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> // Nécessaire pour getch() sur Windows

#define MAP_HEIGHT 9
#define MAP_WIDTH 15

typedef struct {
    char grid[MAP_HEIGHT][MAP_WIDTH];
} Room;

typedef struct {
    int x, y;
} Player;

void afficher_salle(Room *salle, Player *player) {
    system("cls"); 

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == player->y && j == player->x) {
                printf("B "); 
            } else {
                printf("%c ", salle->grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nControles : Fleches ou ZQSD. 'X' pour quitter.\n");
}

int main() {
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

    Player briatte = {7, 3};
    bool running = true;

    while (running) {
        afficher_salle(&salle, &briatte);

        // Lecture instantanée de la touche sans attendre 'Entrée'
        int touche = getch(); 

        int nextX = briatte.x;
        int nextY = briatte.y;

        // Gestion des touches spéciales (Flèches directionnelles)
        // Sous Windows, les flèches envoient un code 0 ou 224 d'abord
        if (touche == 0 || touche == 224) {
            touche = getch(); // On lit le deuxième code pour identifier la flèche
            if (touche == 72) nextY--; // Flèche Haut
            if (touche == 80) nextY++; // Flèche Bas
            if (touche == 75) nextX--; // Flèche Gauche
            if (touche == 77) nextX++; // Flèche Droite
        } 
        // Gestion des touches normales (ZQSD / WASD / X)
        else {
            if (touche == 'z' || touche == 'w') nextY--;
            if (touche == 's') nextY++;
            if (touche == 'q' || touche == 'a') nextX--;
            if (touche == 'd') nextX++;
            if (touche == 'x') running = false;
        }

        // Collision : on ne bouge que si la case n'est pas un Mur ou un Rocher
        if (salle.grid[nextY][nextX] != 'W' && salle.grid[nextY][nextX] != 'R') {
            briatte.x = nextX;
            briatte.y = nextY;
        }
    }

    return 0;
}