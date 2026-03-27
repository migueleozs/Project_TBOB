# Système de Génération d'Étages (Floor Generation System)

## Overview
Ce système permet de générer aléatoirement une étage complète avec 14 salles, comprenant:
- 1 Spawner (salle de départ vide)
- 10 Salles normales avec monstres aléatoires
- 1 Item Room (salle avec item unique)
- 1 Boss Room (salle du boss vide)
- 1 Bonus Item Room (salle avec item bonus)

## Fichiers Clés

### 1. `rooms.h` / `rooms.c`
Contient les fonctions principales pour charger les templates de salles et générer les étages.

**Fonctions principales:**
```c
// Charger les templates de salles depuis un fichier .rtbob
bool load_room_templates(const char *filename, RoomTemplate **outRooms, size_t *outCount);

// Générer un étage complet
bool generate_floor(int floor_num,
                   const RoomTemplate *room_templates, size_t template_count,
                   const char *monsters_file,
                   const char *items_file,
                   Room **outRooms, size_t *outCount);

// Libérer la mémoire
void free_rooms(Room *rooms, size_t count);
void free_room_templates(RoomTemplate *rooms, size_t count);
```

### 2. `salle.h` / `salle.c`
Contient les fonctions de gestion des salles individuelles et la génération d'étages affichable.

**Fonction principale:**
```c
bool generate_and_display_floor(int floor_num,
                               const char *rooms_template_file,
                               const char *monsters_file,
                               const char *items_file);
```

## Format des Fichiers

### `.rtbob` - Room Templates
```
{5}
---
name=BasicRoom
height=9
width=15
---
name=TreeRoom
height=9
width=15
```

### `.mtbob` - Monstres (Existant)
```
{3}
---
name=Goblin
hpMax=120.00
shoot=1
---
name=MR
hpMax=10.00
shoot=1
```

### `.itbob` - Items (Existant)
```
{4}
---
name=<3
hpMax=1.00
---
name=Snack
hpMax=1.00
```

## Règles de Génération

### Spawner Room
- Salle vide (9x15)
- Joueur positionné au centre ('P')
- Pas de monstres

### Salles Normales (10 salles)
- Dimensions: 9x15
- Portes: tous les 4 côtés (haut, bas, gauche, droite)
- Monstres: 0-6 par salle
- Types de monstres: maximum 2 types différents par salle
- **Champions**: 10% de chance pour chaque monstre
  - 2x HP
  - 2x Dégâts
  - Affiché avec 'C' au lieu de 'M'

### Item Rooms (2 salles)
- Salle normale avec item aléatoire au centre
- Seule porte: entrée unique en haut
- Pas de monstres
- Item affiché avec 'I'

### Boss Room
- Salle vide (9x15)
- Seule porte: entrée unique en haut
- Pas de monstres (boss fourni par le scénario)

## Symboles Affichés

| Symbole | Signification |
|---------|---------------|
| W | Wall (Mur) |
| D | Door (Porte) |
| P | Player start (Point de départ du joueur) |
| M | Monster (Monstre normal) |
| C | Champion (Monstre champion - 2x HP & DMG) |
| I | Item (Objet) |
| (space) | Empty floor (Sol vide) |

## Utilisation

### Générer et Afficher un Étage Complet

```c
#include "salle.h"

int main() {
    // Générer l'étage 0 et l'afficher
    if (generate_and_display_floor(0, "rooms.rtbob", "monstres.mtbob", "items.itbob")) {
        printf("Floor 0 generated successfully!\n");
    } else {
        fprintf(stderr, "Failed to generate floor 0\n");
        return 1;
    }
    return 0;
}
```

### Utilisation Avancée avec Contrôle Manuel

```c
#include "rooms.h"

int main() {
    // Charger les templates
    RoomTemplate *templates = NULL;
    size_t template_count = 0;
    
    if (!load_room_templates("rooms.rtbob", &templates, &template_count)) {
        return 1;
    }

    // Générer l'étage
    Room *rooms = NULL;
    size_t room_count = 0;
    
    if (!generate_floor(5, templates, template_count,
                       "monstres.mtbob", "items.itbob",
                       &rooms, &room_count)) {
        return 1;
    }

    // Traiter les salles...
    // ...
    
    // Libérer la mémoire
    free_rooms(rooms, room_count);
    free_room_templates(templates, template_count);
    
    return 0;
}
```

## Compilation

```bash
gcc -c rooms.c -o rooms.o
gcc -c salle.c -o salle.o
gcc -c items.c -o items.o
gcc -c monsters.c -o monsters.o
gcc -o main main.c salle.o rooms.o items.o monsters.o
```

## Exemple de Sortie

```
========== FLOOR 0 ==========

Total rooms generated: 14

--- Room #0 (SPAWNER) - ID: 0 ---
W W W W W W W D W W W W W W W 
W                           W 
W                           W 
W                           W 
D             P             D 
W                           W 
W                           W 
W                           W 
W W W W W W W D W W W W W W W 

--- Room #1 (Normal) - ID: 1 ---
W W W W W W W D W W W W W W W 
W                           W 
W                           W 
W       M                   W 
D             C             D 
W                           W 
W               M           W 
W                 M         W 
W W W W W W W D W W W W W W W 
...
```

## Notes Techniques

1. **Allocation Mémoire**: Toutes les salles générées doivent être libérées avec `free_rooms()`
2. **Aléatoire**: La graine aléatoire est initialisée avec `time(NULL)` + floor_num pour reproductibilité
3. **Performance**: La génération d'un étage est O(14 * monstres_par_salle * tentatives_de_placement)
4. **Extensibilité**: Les templates de salles peuvent être modifiés pour inclure des obstacles (rochers, pics, etc.)

## Limitations Actuelles et Futures

- Les positions des monstres sont placées aléatoirement dans la salle
- Les items sont toujours au centre pour l'instant
- Les templates ne stockent pas encore de données de grille personnalisées

## Fichiers Modifiés

- `rooms.h` (NOUVEAU)
- `rooms.c` (NOUVEAU)
- `rooms.rtbob` (NOUVEAU)
- `salle.h` (MODIFIÉ)
- `salle.c` (MODIFIÉ)

---

**Auteur**: Generated by GitHub Copilot
**Date**: 2026-03-27
