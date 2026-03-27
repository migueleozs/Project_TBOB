# Floor Generation System - FAQ & Troubleshooting

## Frequently Asked Questions

### Q: How do I generate a floor?
**A:** The simplest way is:
```c
#include "salle.h"

generate_and_display_floor(0, "rooms.rtbob", "monstres.mtbob", "items.itbob");
```

### Q: Can I generate multiple floors?
**A:** Yes! Each call generates an independent floor:
```c
for (int floor = 0; floor < 5; ++floor) {
    generate_and_display_floor(floor, "rooms.rtbob", "monstres.mtbob", "items.itbob");
}
```

### Q: What files do I need to provide?
**A:** Three data files are required:
- `rooms.rtbob` - Room templates (provided)
- `monstres.mtbob` - Monster definitions (already in project)
- `items.itbob` - Item definitions (already in project)

### Q: Can I customize room templates?
**A:** Yes! Edit `rooms.rtbob` to add new templates:
```
---
name=MyCustomRoom
height=9
width=15
```

### Q: How do monsters get placed in rooms?
**A:** 
1. Randomly select 0-6 monsters per room
2. Pick max 2 different monster types
3. Place them in random free floor spaces (avoiding walls/doors)
4. 10% of monsters become champions with 2x stats

### Q: What's the difference between M and C?
**A:** 
- `M` = Normal Monster
- `C` = Champion Monster (10% chance, 2x HP and 2x DMG)

### Q: How do I access the generated room data programmatically?
**A:** Use the advanced API:
```c
Room *rooms = NULL;
size_t count = 0;
generate_floor(0, templates, tmpl_count, "monstres.mtbob", "items.itbob", 
               &rooms, &count);

// Access rooms[0] through rooms[13]
// Don't forget to free_rooms(rooms, count);
```

### Q: Can I modify a generated room after creation?
**A:** Yes, the Room structure is fully editable:
```c
rooms[1].grid[4][7] = 'X';  // Place custom marker
```

### Q: How do I integrate this into my main game loop?
**A:** See `FLOOR_GENERATION_EXAMPLES.c` for two different approaches.

### Q: What if a file is missing?
**A:** The function returns false and prints error messages:
```c
if (!generate_and_display_floor(...)) {
    fprintf(stderr, "Floor generation failed!\n");
}
```

### Q: Can I generate different difficulty floors?
**A:** Currently all floors are identical difficulty. Future enhancement:
- Track floor number
- Scale monster HP/DMG by floor
- Increase champion chance by floor

### Q: How much memory does one floor use?
**A:** Approximately 150KB:
- 14 rooms × 9 height × 15 width = 1890 cells
- Plus Entity data structures

## Troubleshooting

### Problem: No monsters appearing in rooms
**Solution:** Check that `monstres.mtbob` exists and is readable:
```bash
ls -la monstres.mtbob
```

### Problem: Compilation errors about undefined functions
**Solution:** Ensure all these files are compiled:
- rooms.c ✓
- salle.c ✓
- items.c ✓
- monsters.c ✓

### Problem: Weird room layout or missing doors
**Solution:** This is normal. The system generates valid rooms. If you see:
- All doors: Standard room ✓
- Some doors: Item/Boss room ✓
- Player 'P': Spawner room ✓

### Problem: Not seeing any champions (C)
**Solution:** Champions appear ~10% of the time. With only 0-6 monsters per room,
they're rare. Generate many floors to see them:
```bash
for i in {0..100}; do ./test_floor > /dev/null; done
grep C *.txt  # If you save output
```

### Problem: Memory leak warnings
**Solution:** Always call free_rooms():
```c
free_rooms(rooms, count);
free_room_templates(templates, template_count);
```

### Problem: Same floor layouts every run
**Solution:** This is normal - random is seeded, so floor N is always identical.
To randomize, modify the seed in `generate_floor()`:
```c
srand((unsigned int)time(NULL));  // More random
```

### Problem: Program crashes when accessing rooms
**Solution:** Ensure proper variable initialization:
```c
Room *rooms = NULL;
size_t count = 0;
generate_floor(..., &rooms, &count);
if (count > 0) {
    // Safe to access rooms
}
```

## Performance Tips

### Speed Up Compilation
```bash
make -f Makefile.floors -j4  # Use 4 parallel jobs
```

### Reduce Output
```c
// Don't call generate_and_display_floor, use generate_floor instead
Room *rooms = NULL;
size_t count = 0;
generate_floor(..., &rooms, &count);
// Process without printing
free_rooms(rooms, count);
```

### Cache Templates
```c
// Load once, reuse
RoomTemplate *templates = NULL;
size_t count = 0;
load_room_templates("rooms.rtbob", &templates, &count);

// Generate many floors
for (int f = 0; f < 100; ++f) {
    generate_floor(f, templates, count, ...);
}

free_room_templates(templates, count);
```

## Common Customizations

### Add More Room Templates
Edit `rooms.rtbob` to include 10+ templates:
```
{10}
---
name=Template1
...
---
name=Template2
...
```

### Change Monster Count Range
In `rooms.c`, modify the line:
```c
int monster_count_in_room = rand() % 7;  // Change 7 for different max
```

### Adjust Champion Probability
In `rooms.c`, find:
```c
bool is_champion = rand() % 100 < 10;  // Change 10 for different percentage
```

### Custom Room Dimensions
In `rooms.c`, modify initialization:
```c
initialize_room(&rooms[room_id], floor_num * 100 + room_id, 12, 20);
```

## Best Practices

1. **Always free resources:**
   ```c
   free_rooms(rooms, count);
   free_room_templates(templates, template_count);
   ```

2. **Check return values:**
   ```c
   if (!generate_floor(...)) {
       handle_error();
   }
   ```

3. **Seed once per game session:**
   ```c
   srand((unsigned int)time(NULL));
   // Then generate all floors for this session
   ```

4. **Validate data files exist:**
   ```bash
   ls *.rtbob *.mtbob *.itbob
   ```

5. **Save generated layouts to file for debugging:**
   ```c
   FILE *f = fopen("floor_debug.txt", "w");
   for (size_t i = 0; i < room_count; ++i) {
       show(&rooms[i]);
   }
   fclose(f);
   ```

## File Format References

### Room Template (.rtbob)
```
{count}
---
name=TemplateName
height=9
width=15
---
name=TemplateName2
height=9
width=15
```

### Monster (.mtbob)
```
{count}
---
name=Goblin
hpMax=120.00
dmg=15.00
shoot=1
---
name=Skeleton
...
```

### Item (.itbob)
```
{count}
---
name=PotatoAmmo
hpMax=1.00
dmg=2.00
---
name=LaunchPolyp
...
```

## Testing Checklist

Before deploying in production:
- ✓ Generate 5+ floors successfully
- ✓ Verify all 14 rooms per floor
- ✓ Check for memory leaks (valgrind)
- ✓ Ensure no crashes with bad input
- ✓ Validate monster placement
- ✓ Test with different room template counts

## Contact Support

For issues, check:
1. `FLOOR_GENERATION.md` - API documentation
2. `IMPLEMENTATION_SUMMARY.md` - Technical details
3. `FLOOR_GENERATION_EXAMPLES.c` - Working examples
4. Source code comments in `rooms.c` and `salle.c`

---

**Last Updated**: March 27, 2026
**Version**: 1.0
