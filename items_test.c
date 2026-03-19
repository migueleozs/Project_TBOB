#include "items.h"
#include <stdio.h>

int main(void) {
    const char *filename = ITEMS_FILE_NAME;

    // Create some sample items
    Item sword = {
        .name = "Sword",
        .hpMax = 0.0f,
        .shield = 0,
        .dmg = 12.5f,
        .ps = false,
        .ss = false,
        .flight = false,
    };

    Item bow = {
        .name = "Bow",
        .hpMax = 0.0f,
        .shield = 0,
        .dmg = 8.0f,
        .ps = true,
        .ss = false,
        .flight = false,
    };

    // Start from a clean file
    overwrite_items_file(filename, NULL, 0);

    append_item_to_file(filename, &sword);
    append_item_to_file(filename, &bow);

    printf("After creating items:\n");
    print_all_items(filename);

    // Update the first item
    Item greatSword = sword;
    snprintf(greatSword.name, sizeof(greatSword.name), "Great Sword");
    greatSword.dmg = 18.0f;
    update_item_in_file(filename, 0, &greatSword);

    printf("\nAfter update:\n");
    print_all_items(filename);

    // Delete the second item
    delete_item_in_file(filename, 1);
    printf("\nAfter delete:\n");
    print_all_items(filename);

    return 0;
}
