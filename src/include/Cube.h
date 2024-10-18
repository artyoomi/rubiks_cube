#ifndef CUBE_H
#define CUBE_H

#include <cstdint>
#include <cstddef>

/*
 * We need some way to store the cube sides data, right?
 * Here goes the format:
 * Value_Type = uint8_t (there're only 6 colors, so why more?)
 * Let's visualize cube sides using the indicies of the corresponding
 * elements in the data array:
 *          0  1  2
 *          3  4  5
 *          6  7  8
 *         ----------
 * 9  10 11|18 19 20|27 28 29|36 37 38
 * 12 13 14|21 22 23|30 31 32|39 40 41
 * 15 16 17|24 25 26|33 34 35|42 43 44
 *         ----------
 *          45 46 47
 *          48 49 50
 *          51 52 53
 *
 * And names of the sides:
 *        (U)p
 *       ---------
 * (L)eft|(F)ront|(R)ight|(B)ack
 *       ---------
 *        (D)own
 *
 * Now let's define rotations - each side can be rotated to 90, 180, 270 deg clockwise
 * To do that rotation, call rotate(side, rotation).
 *
 * Note: this header doesn't define any colors - they are represented as uint8_t in range [0, 5]
 */

// amount of color cells on whole cube
#define TOTAL_COLOR_CELLS 54
#define COLOR_CELLS_PER_SIDE 9
#define SHUFFLE_SEED 40

// can be static_cast'ed to the offset of the first element
enum class CubeSide : uint8_t {
    SIDE_UP    = 0,
    SIDE_LEFT  = 9,
    SIDE_FRONT = 18,
    SIDE_RIGHT = 27,
    SIDE_BACK  = 36,
    SIDE_DOWN  = 45
};

// can be static_cast'ed to the number of clockwise turns
enum class Rotation : uint8_t {
    ROTATION_90  = 1,
    ROTATION_180 = 2,
    ROTATION_270 = 3
};

class Cube
{
public:
    // normal constructor
    Cube();

    // do one random rotation
    void shuffle();

    // rotate selected side
    void rotate(CubeSide side, Rotation rot);

    // get side colors
    // returned as uint8_t[COLOR_CELLS_PER_SIDE] array:
    // 0 1 2
    // 3 4 5
    // 6 7 8
    // NOTE: dynamically allocates memory!
    uint8_t *get_side_data(CubeSide side);
    // uint8_t *get_adjacent_data(CubeSide side);
    
    // returns array of all values on cube
    // NOTE: dynamically allocates memory!
    uint8_t *get_cube_data();
private:
    // rotate one side (doesn't affect adjacent side)
    void _rotate_side(CubeSide side);

    // rotate adjacent elements
    void _rotate_adjacent(CubeSide side);
    uint8_t _cube_data[TOTAL_COLOR_CELLS];
};

#endif
