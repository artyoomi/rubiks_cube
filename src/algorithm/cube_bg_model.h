#pragma once

#include <cstdint>
#include <cstring>
#include <ctime>

#include <iostream>
#include <vector>
#include <array>
#include <string>

#define TOTAL_COLOR_CELLS 54
#define COLORS_PER_SIDE   9

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
 *           (U)p[0]
 *          ------------
 * (L)eft[1]|(F)ront[2]|(R)ight[3]|(B)ack[4]
 *          ------------
 *           (D)own[5]
 *
 * Now let's define rotations - each side can be rotated to 90, 180, 270 deg clockwise
 * To do that rotation, call rotate(side, rotation).
 *
 * Note: this header doesn't define any colors - they are represented as uint8_t in range [0, 5]
 */

// can be static_cast'ed to offset of the first element using multiplication by 9
enum class rotation_side {
    SIDE_U = 0,
    SIDE_L = 1,
    SIDE_F = 2,
    SIDE_R = 3,
    SIDE_B = 4,
    SIDE_D = 5
};

enum class rotation_type {
    ROTATION_R = 0,
    ROTATION_L = 1,
};

class Cube_bg_model {
public:
    // cube colors enum a.k.a. side enum
    enum class ecolor : uint8_t {U = 0, L = 1, F = 2, R = 3, B = 4, D = 5};

    // all cube cubies enum
    enum class epiece : uint8_t {
        UL,  DL,  DR,  UR,  LF,  LB,  RF,  RB,  UF,  DF,  DB,  UB,
        ULB, ULF, DLF, DLB, DRB, DRF, URF, URB
    };
    
    // all cube edges enum
    enum class eedge : uint8_t {
        UB = 1 ,    UR = 5 ,    UF = 7 ,    UL = 3,
        LU = 10,    LF = 14,    LD = 16,    LB = 12,
        FU = 19,    FR = 23,    FD = 25,    FL = 21,
        RU = 28,    RB = 32,    RD = 34,    RF = 30,
        BU = 37,    BL = 41,    BD = 43,    BR = 39,
        DF = 46,    DR = 50,    DB = 52,    DL = 48,
    };

    // all cube corners enum
    enum class ecorner : uint8_t {
        ULB = 0 ,   URB = 2 ,   URF = 8 ,   ULF = 6 ,
        LUB = 9 ,   LUF = 11,   LDF = 17,   LDB = 15,
        FLU = 18,   FRU = 20,   FRD = 26,   FLD = 24,
        RUF = 27,   RUB = 29,   RDB = 35,   RDF = 33,
        BRU = 36,   BLU = 38,   BLD = 44,   BRD = 42,
        DLF = 45,   DRF = 47,   DRB = 53,   DLB = 51,
    };

    // all cube moves enum
    enum class emove : uint8_t {
        NO_MOVE,
        U, Ur, U2,
        L, Lr, L2,
        F, Fr, F2,
        R, Rr, R2,
        B, Br, B2,
        D, Dr, D2,
    };

    /* Determine edge as two colors array:
     * (P.S. Example: LR-slice is cubies between L and R facelets)
     * For FB-slice:
     * 0) facelet on the R/L face
     * 1) facelet on the U/D face
     * 
     * For UD-slice:
     * 0) facelet on the R/L face
     * 1) facelet on the F/B face
     * 
     * For LR-slice:
     * 0) facelet on the U/D face
     * 1) facelet on the F/B face
     */
    using edge_t = std::array<ecolor, 2>;

    /* Determine corner as three colors array (the following is ordered by indexes):
     * 0) facelet on the R/L face
     * 1) facelet on the U/D face
     * 2) facelet on the F/B face
     */
    using corner_t = std::array<ecolor, 3>;

    // constructor
    Cube_bg_model();

    // copy constructor
    Cube_bg_model& operator=(const Cube_bg_model& lhs);

    bool operator==(const Cube_bg_model& lhs);

    // get color name by enum value
    static std::string color_name(ecolor colour);

    // get move name by enum value
    static std::string move_name(emove move);

    // get side colors in array view
    std::array<ecolor, COLORS_PER_SIDE> get_side(ecolor side) const;
    std::array<ecolor, COLORS_PER_SIDE> get_side(rotation_side side) const;
    std::array<ecolor, TOTAL_COLOR_CELLS> get_data() const;

    // get color directly by the index
    Cube_bg_model::ecolor operator[](unsigned index);

    // reset cube sides
    void reset();

    // determine if cube is solved
    bool solved() const;

    // rotate selected side
    void rotate(rotation_side side, rotation_type rot);

    // get first edge/corner facelet colour by index in cube
    // example: UFL gives U on return
    ecolor color(eedge index) const;
    ecolor color(ecorner index) const;

    // get edge orinetation
    uint8_t edge_orientation(const edge_t& edge) const;

    // output: first index is the facelet on the R/L face
    uint8_t corner_orientation(const corner_t& corner, epiece corner_piece) const;

    // unique index of edge by edge facelets colors
    uint8_t edge_index(const edge_t& edge) const;

    // unique index of corner by corner facelets colors
    uint8_t corner_index(const corner_t& edge) const;

    // unique index of piece by piece facelets colors    
    uint8_t piece_index(epiece piece) const;

    // get corner_t by piece enum
    corner_t corner(epiece piece) const;

    // get edge_t by piece enum
    edge_t edge(epiece piece) const;

    // make move according to enum value
    void rotate(emove move);
    
    // make move according to enum value
    void revert_rotate(emove move);

// PRIVATE METHODS
private:
    // rotate one side (doesn't affect adjacent side)
    void _rotate_side(rotation_side side);

    // rotate adjacent elements
    void _rotate_adjacent(rotation_side side);

// PRIVATE FIELDS
private:
    std::array<ecolor, 54> _cube_data;
};
