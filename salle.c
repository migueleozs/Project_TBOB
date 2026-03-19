#include "salle.h"
#include "structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Getter and setter

void set_RoomId(Room *R, int id){
    R->id = id;
}



void creer(Room *R, int n, int m){
    
    int i, j;
    R->height = n;
    R->width = m;
    R->grid = malloc(sizeof(char*) * n);
    //Allocation de l'espace et Initialisation 
    //de la salle à des espaces vides partout
    for(i = 0; i < n; i += 1){
        R->grid[i] = malloc(m);
        for(j = 0; j < m; j += 1){
            R->grid[i][j] = ' ';
        }
    }
    
    //Murs et portes
        //M_H et M_B
        
    for(j = 0; j < m; j += 1){
        if(j == m/2){
            R->grid[0][j] = 'D';
            R->grid[n-1][j] = 'D';
        }/*
        else if(j == m/2+1){
            R->grid[0][j] = 'W';
            R->grid[n-1][j] = 'D';
        }*/
        else{
            R->grid[0][j] = 'W';
            R->grid[n-1][j] = 'W';
        }
    }

        //M_D et M_G
    for(i = 1; i < n-1; i += 1){
        if(i == n/2){
            R->grid[i][0] = 'D';
            R->grid[i][m-1] = 'D';
        }
        else{
            R->grid[i][0] = 'W';
            R->grid[i][m-1] = 'W';
        }
    }
    /*
    //Diagonale_1
    R->grid[1][1] = 'H'; R->grid[1][2] = 'G'; R->grid[2][2] = 'G'; R->grid[2][1] = 'G'; 
    R->grid[n-2][m-2] = 'H'; R->grid[n-2][m-3] = 'G'; R->grid[n-3][m-3] = 'G'; R->grid[n-3][m-2] = 'G'; 
    //Diagonale_2
    R->grid[n-3][1] = 'G'; R->grid[n-3][2] = 'G'; R->grid[n-2][2] = 'G';
    R->grid[2][m-2] = 'G'; R->grid[2][m-3] = 'G'; R->grid[1][m-3] = 'G';
    */


    //Ajout d'éléments dans la salle

    
}


void modif(char** s, int n, int m){

    

}


void suppr(char** s){
    
}


void show(Room *R){
    
    int i, j;
    for(i = 0; i < R->height; i += 1){
        for(j = 0; j < R->width; j += 1){
            printf("%c ", R->grid[i][j]);
        }
        printf("\n");
    }
    
    //freeR(R);
}

void freeR(Room *R){
    int i;
    for(i=0; i < R->height; i++)
        free(R->grid[i]);
    free(R->grid);
}