// Example: How to integrate floor generation into your main game loop

#include "salle.h"
#include <stdio.h>
#include <stdlib.h>

/*
// SIMPLE VERSION: Just generate and display a floor

int main() {
    printf("=== TBOB Dungeon Floor Generator ===\n\n");
    
    // Generate floor 0 and display it
    if (!generate_and_display_floor(0, "rooms.rtbob", "monstres.mtbob", "items.itbob")) {
        fprintf(stderr, "Error generating floor!\n");
        return 1;
    }
    
    return 0;
}
*/

// ADVANCED VERSION: Generate multiple floors and process them

#include "rooms.h"

int main() {
    printf("=== TBOB Multi-Floor Generator ===\n\n");
    
    // Load room templates once
    RoomTemplate *templates = NULL;
    size_t template_count = 0;
    
    if (!load_room_templates("rooms.rtbob", &templates, &template_count)) {
        fprintf(stderr, "Failed to load room templates!\n");
        return 1;
    }
    
    printf("Loaded %zu room templates\n\n", template_count);
    
    // Generate multiple floors
    for (int floor = 0; floor < 3; ++floor) {
        printf("\n========== GENERATING FLOOR %d ==========\n", floor);
        
        Room *rooms = NULL;
        size_t room_count = 0;
        
        // Generate this floor
        if (!generate_floor(floor, templates, template_count,
                           "monstres.mtbob", "items.itbob",
                           &rooms, &room_count)) {
            fprintf(stderr, "Error generating floor %d!\n", floor);
            continue;
        }
        
        printf("Generated %zu rooms for floor %d\n", room_count, floor);
        
        // TODO: Process rooms here
        // For example:
        // - Save to file
        // - Display room summary
        // - Initialize game state with these rooms
        // - Setup spawn points, treasure locations, etc.
        
        for (size_t i = 0; i < room_count; ++i) {
            const char *type;
            switch (i) {
                case 0: type = "SPAWNER"; break;
                case 11: type = "ITEM_ROOM"; break;
                case 12: type = "BOSS_ROOM"; break;
                case 13: type = "BONUS_ITEM"; break;
                default: type = "NORMAL";
            }
            printf("  Room %zu (%s): %dx%d\n", i, type, rooms[i].height, rooms[i].width);
        }
        
        // Free rooms for this floor
        free_rooms(rooms, room_count);
    }
    
    // Free templates
    free_room_templates(templates, template_count);
    
    printf("\n========== GENERATION COMPLETE ==========\n");
    
    return 0;
}
