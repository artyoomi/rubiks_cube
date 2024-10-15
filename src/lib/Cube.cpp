#include "../include/Cube.h"
#include <cstdlib>
#include <ctime>

Cube::Cube()
{
    // seed random generator with current time
    std::srand(std::time(nullptr));
    
    // fill cube with some colors (fully assembled)
    for(std::size_t i = 0;  i < 9;  i++) { _cube_data[i] = 0; }
    for(std::size_t i = 9;  i < 18; i++) { _cube_data[i] = 1; }
    for(std::size_t i = 18; i < 27; i++) { _cube_data[i] = 2; }
    for(std::size_t i = 27; i < 36; i++) { _cube_data[i] = 3; }
    for(std::size_t i = 36; i < 45; i++) { _cube_data[i] = 4; }
    for(std::size_t i = 45; i < 54; i++) { _cube_data[i] = 5; }
}

void Cube::shuffle()
{
    // select random side
    cube_side side = static_cast<cube_side>((std::rand() % 6) * 9);
    // select random rotation
    rotation rot = static_cast<rotation>((std::rand() % 3) + 1);

    // take action
    rotate(side, rot);
}

void Cube::rotate(cube_side side, rotation rot)
{
    for(std::size_t i = 0; i < static_cast<std::size_t>(rot); i++) {
        // rotate selected side
        _rotate_side(side);

        // swap elements in the adjacent sides
        _rotate_adjacent(side);
    }
}

uint8_t *Cube::get_side(cube_side side)
{
    std::size_t first_i = static_cast<std::size_t>(side);

    uint8_t *result = new uint8_t[9];
    for(std::size_t i = 0; i < 9; i++) {
        result[i] = _cube_data[first_i + i];
    }

    return result;
}

/*
 * Action of the function:
 * 0 1 2    cw    6 3 0
 * 3 4 5   ---->  7 4 1
 * 6 7 8          8 5 2
 *
 * Or in the array form:
 * {0, 1, 2, 3, 4, 5, 6, 7, 8}
 *              |
 * {6, 3, 0, 7, 4, 1, 8, 5, 2}
 */
void Cube::_rotate_side(cube_side side)
{
    std::size_t first_i = static_cast<std::size_t>(side);

    // reorder
    uint8_t new_side[9] = {
        _cube_data[first_i + 6],
        _cube_data[first_i + 3],
        _cube_data[first_i + 0],
        _cube_data[first_i + 7],
        _cube_data[first_i + 4],
        _cube_data[first_i + 1],
        _cube_data[first_i + 8],
        _cube_data[first_i + 5],
        _cube_data[first_i + 2]
    };

    // insert reodered data back into the _cube_data
    for(std::size_t i = 0; i < 9; i++) {
        _cube_data[first_i + i] = new_side[i];
    }
}

/*
 * Action of the function:
 *          a0 a1 a2                           a0 a1 a2         
 *          a3 a4 a5                           a3 a4 a5         
 *          a6 a7 a8                           b8 b5 b2         
 *         ----------                         ----------        
 * b0 b1 b2|[] [] []|c0 c1 c2   cw    b0 b1 d0|[] [] []|a6 c1 c2
 * b3 b4 b5|[] [] []|c3 c4 c5  ---->  b3 b4 d1|[] [] []|a7 c4 c5
 * b6 b7 b8|[] [] []|c6 c7 c8         b6 b7 d2|[] [] []|a8 c7 c8
 *         ----------                         ----------        
 *          d0 d1 d2                           c6 c3 c0         
 *          d3 d4 d5                           d3 d4 d5         
 *          d6 d7 d8                           d6 d7 d8         
 */

 void Cube::_rotate_adjacent(cube_side side)
 {
     // a lot of swapping here...
     // (God pls trust me with the diagrams below...)
     uint8_t tmp1, tmp2, tmp3; // for swapping
     switch(side) {
         case cube_side::SIDE_UP:
             /* BEFORE:
              *    38 37 36
              *   ----------
              * 9 |[] [] []|29
              * 10|[] [] []|28
              * 11|[] [] []|27
              *   ----------
              *    18 19 20
              */
             tmp1 = _cube_data[38];
             tmp2 = _cube_data[37];
             tmp3 = _cube_data[36];
             // top
             _cube_data[38] = _cube_data[11];
             _cube_data[37] = _cube_data[10];
             _cube_data[36] = _cube_data[9 ];
             // left
             _cube_data[11] = _cube_data[20];
             _cube_data[10] = _cube_data[19];
             _cube_data[9 ] = _cube_data[18];
             // bottom
             _cube_data[20] = _cube_data[29];
             _cube_data[19] = _cube_data[28];
             _cube_data[18] = _cube_data[27];
             // right
             _cube_data[29] = tmp1;
             _cube_data[28] = tmp2;
             _cube_data[27] = tmp3;
             break;
         case cube_side::SIDE_LEFT:
             /* BEFORE:
              *    0  3  6
              *   ----------
              * 38|[] [] []|18
              * 41|[] [] []|21
              * 44|[] [] []|24
              *   ----------
              *    51 48 45
              */
             tmp1 = _cube_data[0];
             tmp2 = _cube_data[3];
             tmp3 = _cube_data[6];
             // top
             _cube_data[0] = _cube_data[44];
             _cube_data[3] = _cube_data[41];
             _cube_data[6] = _cube_data[38];
             // left
             _cube_data[44] = _cube_data[45];
             _cube_data[41] = _cube_data[48];
             _cube_data[38] = _cube_data[51];
             // bottom
             _cube_data[45] = _cube_data[18];
             _cube_data[48] = _cube_data[21];
             _cube_data[51] = _cube_data[24];
             // right
             _cube_data[18] = tmp1;
             _cube_data[21] = tmp2;
             _cube_data[24] = tmp3;
             break;
         case cube_side::SIDE_FRONT:
             /* BEFORE:
              *    6  7  8
              *   ----------
              * 11|[] [] []|27
              * 14|[] [] []|30
              * 17|[] [] []|33
              *   ----------
              *    45 46 47
              */
             tmp1 = _cube_data[6];
             tmp2 = _cube_data[7];
             tmp3 = _cube_data[8];
             // top
             _cube_data[6] = _cube_data[17];
             _cube_data[7] = _cube_data[14];
             _cube_data[8] = _cube_data[11];
             // left
             _cube_data[17] = _cube_data[47];
             _cube_data[14] = _cube_data[46];
             _cube_data[11] = _cube_data[45];
             // bottom
             _cube_data[47] = _cube_data[27];
             _cube_data[46] = _cube_data[30];
             _cube_data[45] = _cube_data[33];
             // right
             _cube_data[27] = tmp1;
             _cube_data[30] = tmp2;
             _cube_data[33] = tmp3;
             break;
         case cube_side::SIDE_RIGHT:
             /* BEFORE:
              *    8  5  2
              *   ----------
              * 20|[] [] []|36
              * 23|[] [] []|39
              * 26|[] [] []|42
              *   ----------
              *    47 50 53
              */
             tmp1 = _cube_data[8];
             tmp2 = _cube_data[5];
             tmp3 = _cube_data[2];
             // top
             _cube_data[8] = _cube_data[26];
             _cube_data[5] = _cube_data[23];
             _cube_data[2] = _cube_data[20];
             // left
             _cube_data[26] = _cube_data[53];
             _cube_data[23] = _cube_data[50];
             _cube_data[20] = _cube_data[47];
             // bottom
             _cube_data[53] = _cube_data[36];
             _cube_data[50] = _cube_data[39];
             _cube_data[47] = _cube_data[42];
             // right
             _cube_data[36] = tmp1;
             _cube_data[39] = tmp2;
             _cube_data[42] = tmp3;
             break;
         case cube_side::SIDE_BACK:
             /* BEFORE:
              *    2  1  0
              *   ----------
              * 29|[] [] []|9
              * 32|[] [] []|12
              * 35|[] [] []|15
              *   ----------
              *    53 52 51
              */
             tmp1 = _cube_data[2];
             tmp2 = _cube_data[1];
             tmp3 = _cube_data[0];
             // top
             _cube_data[2] = _cube_data[35];
             _cube_data[1] = _cube_data[32];
             _cube_data[0] = _cube_data[29];
             // left
             _cube_data[35] = _cube_data[51];
             _cube_data[32] = _cube_data[52];
             _cube_data[29] = _cube_data[53];
             // bottom
             _cube_data[51] = _cube_data[9 ];
             _cube_data[52] = _cube_data[12];
             _cube_data[53] = _cube_data[15];
             // right
             _cube_data[9 ] = tmp1;
             _cube_data[12] = tmp2;
             _cube_data[15] = tmp3;
             break;
         case cube_side::SIDE_DOWN:
             /* BEFORE:
              *    24 25 26
              *   ----------
              * 17|[] [] []|33
              * 16|[] [] []|34
              * 15|[] [] []|35
              *   ----------
              *    44 43 42
              */
             tmp1 = _cube_data[24];
             tmp2 = _cube_data[25];
             tmp3 = _cube_data[26];
             // top
             _cube_data[24] = _cube_data[15];
             _cube_data[25] = _cube_data[16];
             _cube_data[26] = _cube_data[17];
             // left
             _cube_data[15] = _cube_data[42];
             _cube_data[16] = _cube_data[43];
             _cube_data[17] = _cube_data[44];
             // bottom
             _cube_data[42] = _cube_data[33];
             _cube_data[43] = _cube_data[34];
             _cube_data[44] = _cube_data[35];
             // right
             _cube_data[33] = tmp1;
             _cube_data[34] = tmp2;
             _cube_data[35] = tmp3;
             break;
     }
 }
