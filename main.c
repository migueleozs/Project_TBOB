#include "salle.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h> // Nécessaire pour getch() sur Windows


int main(int argc, char const *argv[])
{
    
    //Variables génériques
    int i, j, n, m;
    char choix;
    Room tab_Room[14];

    //Title
    printf("CRUD des pieces du donjon\n\n");


    //Prédéfinition des salles

    Room spawner, itRoom, bRoom, itRoomB; //Salles spéciales
    Room R1, R2, R3, R4, R5, R6, R7, R8, R9, R10; //10 salles
    //tab_Room[14] = {spawner, itRoom, bRoom, itRoomB, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10}; 
    tab_Room[0] = R1;   tab_Room[5] = R6;   tab_Room[10] = spawner;
    tab_Room[1] = R2;   tab_Room[6] = R7;   tab_Room[11] = itRoom;
    tab_Room[2] = R3;   tab_Room[7] = R8;   tab_Room[12] = bRoom;
    tab_Room[3] = R4;   tab_Room[8] = R9;   tab_Room[13] = itRoomB;
    tab_Room[4] = R5;   tab_Room[9] = R10;
    
    
    //Création des salles par défaut

        //Choix de la taille par l'user
    
    printf("Entrer n: ");
    scanf("%d", &n);
    printf("Entrer m: ");
    scanf("%d", &m);
    printf("\n");

    for(i = 0; i < 14; i++)
        set_RoomId(&tab_Room[i], i+1); //Affectation des id
    

            //Salles modifiables par l'user
    creer(&tab_Room[0], n, m);
    show(&tab_Room[0]);


    bool running = true;

    char choice;
    printf("Obstacle a ajouter : G | R ? : ");
    scanf(" %c", &choice);  
    //tab_Room[0].grid[tab_Room[0].height/2][tab_Room[0].width/2] = choice;
    
    int X = tab_Room[0].width/2;
    int Y = tab_Room[0].height/2;

    int nextX = X;
    int nextY = Y;

    while (running) {

        
        
        int nextX , nextY; 
        // int X = tab_Room[0].width/2;
        // int Y = tab_Room[0].height/2;

        // nextX = tab_Room[0].width/2;
        // nextY = tab_Room[0].height/2;

        tab_Room[0].grid[Y][X] = choice;

        printf("\n");
        show(&tab_Room[0]);
        
        
        printf("\n");
        printf("\n");
        printf("Deplacements [Gauche (a/q); Droite (d); Haut (s); Bas (z/w)] : ");
        //scanf(" %c", &touche); 
        int touche = getch();

            if (touche == 'z' || touche == 'w') 
                nextY--;
            if (touche == 's') 
                nextY++;
            if (touche == 'q' || touche == 'a') 
                nextX--;
            if (touche == 'd') 
                nextX++;
            if (touche == 'x') 
                running = false;
        

        // Collision : on ne bouge que si la case n'est pas un Mur ou un Rocher
        if (tab_Room[0].grid[nextY][nextX] != 'W' && tab_Room[0].grid[nextY][nextX] != 'R') {
            X = nextX;
            Y = nextY;
        }
        
    }





     /*     
    creer(&tab_Room[0], n, m);
    show(&tab_Room[0]);
    printf("\n");
    creer(&tab_Room[2], n, m);
    show(&tab_Room[2]);
    printf("\n");
    creer(&tab_Room[4], n, m);
    show(&tab_Room[4]);
    printf("\n");
    creer(&tab_Room[7], n, m);
    show(&tab_Room[7]);
    printf("\n");
    */
    
    printf("\n");
   
    






    // for(i = 0; i < 10; i++)
    //     show(&tab_Room[i]);




    //Choix de l'action
    // printf("Que souhaitez vous faire?\n"); 
    // do{
    //     printf("Tapez c(Create); r(read), u(update) ou d(delete) : ");
    //     scanf(" %c", &choix);
    // }while(choix != 'c' &&  choix != 'r' && choix != 'u' && choix != 'd');
    //Exécution selon le choix de l'user
    switch(choix){
        case 'c' :
            //creer(n, m);
            break;
        case 'r' :
            //show(..., n, m); //Mettre plutôt en paramètre le numéro de la salle correspondante
            break;
        case 'u' :
            //modif(..., n, m); //Idem ici
            break;
        case 'd' :
            //suppr(...) //Idem pour l'indice correspondant dans le tableau de la strucure
            break;
        default :
            //...
            break;

    }

    return 0;
}
