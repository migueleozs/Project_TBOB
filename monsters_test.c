#include "monsters.h"
#include <stdio.h>

int main(void) {
    const char *filename = MONSTERS_FILE_NAME;

    // Create some sample entities
    Entity monster1 = {
        .name = "Goblin",
        .hpMax = 100.0f,
        .dmg = 15.0f,
        .x = 5,
        .y = 3,
        .shoot = true,
        .ss = false,
        .flight = false,
    };

    Entity monster2 = {
        .name = "Dragon",
        .hpMax = 50.0f,
        .dmg = 10.0f,
        .x = 0,
        .y = 0,
        .shoot = false,
        .ss = true,
        .flight = true,
    };

    // Start from a clean file
    overwrite_entities_file(filename, NULL, 0);

    append_entity_to_file(filename, &monster1);
    append_entity_to_file(filename, &monster2);

    printf("After creating entities:\n");
    print_all_entities(filename);

    // Update the first entity
    Entity updated = monster1;
    updated.hpMax = 120.0f;
    updated.dmg = 20.0f;
    update_entity_in_file(filename, 0, &updated);

    printf("\nAfter update:\n");
    print_all_entities(filename);

    // Delete the second entity
    delete_entity_in_file(filename, 1);
    printf("\nAfter delete:\n");
    print_all_entities(filename);

    return 0;
}
