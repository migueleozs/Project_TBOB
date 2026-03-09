#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAP_HEIGHT 9
#define MAP_WIDTH 15

// Structure de la salle (Pièce)
typedef struct {
    char grid[MAP_HEIGHT][MAP_WIDTH];
} Room;

// Structure du joueur
typedef struct {
    int x, y;
} Player;

// 1. Affichage de la salle dans le terminal
void afficher_salle(Room *salle, Player *player) {
    // Nettoyage d'écran (sur Windows)
    system("cls"); 

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == player->y && j == player->x) {
                printf("B "); // 'B' pour Briatte
            } else {
                printf("%c ", salle->grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\nUtilisez Z (haut), S (bas), Q (gauche), D (droite). 'X' pour quitter.\n");
}

int main() {
    // 2. Création d'une salle de test
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

    Player briatte = {7, 3}; // Position initiale
    char commande;
    bool running = true;

    // 3. Boucle principale du jeu
    while (running == true) {
        afficher_salle(&salle, &briatte);

        printf("Action : ");
        scanf(" %c", &commande); // L'espace avant %c est vital pour ignorer le 'entrée' précédent

        int nextX = briatte.x;
        int nextY = briatte.y;

        if (commande == 'z') nextY--;
        if (commande == 's') nextY++;
        if (commande == 'q') nextX--;
        if (commande == 'd') nextX++;
        if (commande == 'x') running = false;

        // 4. Gestion simple des collisions (Murs 'W' et Rochers 'R')
        if (salle.grid[nextY][nextX] != 'W' && salle.grid[nextY][nextX] != 'R') {
            briatte.x = nextX;
            briatte.y = nextY;
        }
    }

    return 0;
}