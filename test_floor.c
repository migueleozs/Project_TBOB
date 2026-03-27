#include "salle.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("=== FLOOR GENERATION TEST ===\n\n");

    // Test floor generation
    if (generate_and_display_floor(0, "rooms.rtbob", "monstres.mtbob", "items.itbob")) {
        printf("\nFloor 0 generated successfully!\n");
    } else {
        fprintf(stderr, "Failed to generate floor 0\n");
        return 1;
    }

    printf("\n=== TEST COMPLETE ===\n");
    return 0;
}
