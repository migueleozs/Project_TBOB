#include "structs.h"

#ifndef SALLE_H

#define SALLE_H


void set_RoomId(Room*, int); //Identification des salles
void creer(Room*, int, int);
void modif(char**, int, int);
void suppr(char**);
void show(Room*);
void freeR(Room*);

#endif /* SALLE_H */