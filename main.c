#include "salle.h"
#include "structs.h"
#include "items.h"
#include "monsters.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h> // Nécessaire pour getch() sur Windows

static void clear_stdin(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

static void trim_newline(char *s)
{
    if (!s) return;
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len - 1] == '\n')
        s[len - 1] = '\0';
}

static void prompt_item(Item *item)
{
    if (!item)
        return;

    printf("Nom (peut contenir des espaces) : ");
    if (fgets(item->name, sizeof(item->name), stdin)) {
        trim_newline(item->name);
    }

    printf("hpMax (float) : ");
    scanf("%f", &item->hpMax);

    printf("shield (int) : ");
    scanf("%d", &item->shield);

    printf("dmg (float) : ");
    scanf("%f", &item->dmg);

    printf("ps (0/1) : ");
    scanf("%d", (int *)&item->ps);

    printf("ss (0/1) : ");
    scanf("%d", (int *)&item->ss);

    printf("flight (0/1) : ");
    scanf("%d", (int *)&item->flight);

    clear_stdin();
}

static void run_item_menu(void)
{
    bool running = true;
    while (running) {
        printf("\n=== CRUD d'objets (items) ===\n");
        printf("1) Creer item\n");
        printf("2) Lister les items\n");
        printf("3) Modifier item\n");
        printf("4) Supprimer item\n");
        printf("0) Retour\n");
        printf("Choix : ");

        int choix = -1;
        if (scanf("%d", &choix) != 1) {
            clear_stdin();
            continue;
        }
        clear_stdin();

        switch (choix) {
            case 1: {
                Item newItem = {0};
                prompt_item(&newItem);
                if (append_item_to_file(ITEMS_FILE_NAME, &newItem))
                    printf("Item ajoute\n");
                else
                    printf("Erreur a l\'ecriture\n");
            } break;
            case 2:
                print_all_items(ITEMS_FILE_NAME);
                break;
            case 3: {
                print_all_items(ITEMS_FILE_NAME);
                printf("Index de l\'item a modifier: ");
                size_t idx;
                if (scanf("%zu", &idx) != 1) {
                    clear_stdin();
                    break;
                }
                clear_stdin();
                Item updated = {0};
                prompt_item(&updated);
                if (update_item_in_file(ITEMS_FILE_NAME, idx, &updated))
                    printf("Item mis à jour\n");
                else
                    printf("Erreur : indice invalide ou mise a jour impossible\n");
            } break;
            case 4: {
                print_all_items(ITEMS_FILE_NAME);
                printf("Index de l\'item a supprimer: ");
                size_t idx;
                if (scanf("%zu", &idx) != 1) {
                    clear_stdin();
                    break;
                }
                clear_stdin();
                if (delete_item_in_file(ITEMS_FILE_NAME, idx))
                    printf("Item supprime\n");
                else
                    printf("Erreur : indice invalide ou suppression impossible\n");
            } break;
            case 0:
                running = false;
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    }
}

static void prompt_entity(Entity *entity)
{
    if (!entity)
        return;

    printf("Nom (peut contenir des espaces) : ");
    if (fgets(entity->name, sizeof(entity->name), stdin)) {
        trim_newline(entity->name);
    }

    printf("Vie : ");
    scanf("%f", &entity->hpMax);
/*
    printf("dmg (float) : ");
    scanf("%f", &entity->dmg);

    printf("x (int) : ");
    scanf("%d", &entity->x);

    printf("y (int) : ");
    scanf("%d", &entity->y);
*/
    printf("Peut tirer? (0/1) : ");
    scanf("%d", (int *)&entity->shoot);

    printf("Tir spectral? (0/1) : ");
    scanf("%d", (int *)&entity->ss);

    printf("Peut voler? (0/1) : ");
    scanf("%d", (int *)&entity->flight);

    clear_stdin();
}

static void run_monster_menu(void)
{
    bool running = true;
    while (running) {
        printf("\n=== CRUD de monstres ===\n");
        printf("1) Creer monstre\n");
        printf("2) Lister les monstres\n");
        printf("3) Modifier monstre\n");
        printf("4) Supprimer monstre\n");
        printf("0) Retour\n");
        printf("Choix : ");

        int choix = -1;
        if (scanf("%d", &choix) != 1) {
            clear_stdin();
            continue;
        }
        clear_stdin();

        switch (choix) {
            case 1: {
                Entity newEntity = {0};
                prompt_entity(&newEntity);
                if (append_entity_to_file(MONSTERS_FILE_NAME, &newEntity))
                    printf("Monstre ajouté\n");
                else
                    printf("Erreur à l'écriture\n");
            } break;
            case 2:
                print_all_entities(MONSTERS_FILE_NAME);
                break;
            case 3: {
                print_all_entities(MONSTERS_FILE_NAME);
                printf("Index du monstre à modifier : ");
                size_t idx;
                if (scanf("%zu", &idx) != 1) {
                    clear_stdin();
                    break;
                }
                clear_stdin();
                Entity updated = {0};
                prompt_entity(&updated);
                if (update_entity_in_file(MONSTERS_FILE_NAME, idx, &updated))
                    printf("Monstre mis à jour\n");
                else
                    printf("Erreur : indice invalide ou mise à jour impossible\n");
            } break;
            case 4: {
                print_all_entities(MONSTERS_FILE_NAME);
                printf("Index du monstre à supprimer : ");
                size_t idx;
                if (scanf("%zu", &idx) != 1) {
                    clear_stdin();
                    break;
                }
                clear_stdin();
                if (delete_entity_in_file(MONSTERS_FILE_NAME, idx))
                    printf("Monstre supprimé\n");
                else
                    printf("Erreur : indice invalide ou suppression impossible\n");
            } break;
            case 0:
                running = false;
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    }
}

int main(int argc, char const *argv[])
{
    
    //Variables génériques
    int i, j, n, m;
    char choix;
    Room tab_Room[14];

    //Title
    printf("CRUD des salles du donjon\n\n");


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
    
    printf("Entrez n (hauteur) : ");
    scanf("%d", &n);
    printf("Entrez m (largeur) : ");
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

        
        
        //int nextX , nextY; 
        // int X = tab_Room[0].width/2;
        // int Y = tab_Room[0].height/2;

        // nextX = tab_Room[0].width/2;
        // nextY = tab_Room[0].height/2;

        tab_Room[0].grid[Y][X] = choice;

        printf("\n");
        show(&tab_Room[0]);
        
        
        printf("\n");
        printf("\n");
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

    /*
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

    */

    run_item_menu();
    run_monster_menu();
    return 0;
}
