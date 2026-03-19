#ifndef STRUCTS_H

#define STRUCTS_H


//Structure des salles
typedef struct{
    int id;
    int height; // Hauteur de la pièce
    int width;  // Largeur de la pièce
    char** grid; // Matrice de caractères : W (wall), R (rock), G (gap), D (door), S (spike), H (item)
}Room;



#endif /* STRUCTS_H */

//