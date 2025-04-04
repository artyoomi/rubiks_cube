#include "cube_bg_model.h"

Cube_bg_model::Cube_bg_model()
{
    reset();
}

bool Cube_bg_model::operator==(const Cube_bg_model& lhs)
{
    for (std::size_t i = 0; i < TOTAL_COLOR_CELLS; ++i) {
        if (_cube_data[i] != lhs._cube_data[i])
            return false;
    }

    return true;
}

Cube_bg_model& Cube_bg_model::operator=(const Cube_bg_model& lhs)
{
    for (std::size_t i = 0; i < TOTAL_COLOR_CELLS; ++i)
        _cube_data[i] = lhs._cube_data[i];
    
    return *this;
}

void Cube_bg_model::reset()
{
    for (std::size_t i = 0;  i < 1 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ecolor::U; }
    for (std::size_t i = 9;  i < 2 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ecolor::L; }
    for (std::size_t i = 18; i < 3 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ecolor::F; }
    for (std::size_t i = 27; i < 4 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ecolor::R; }
    for (std::size_t i = 36; i < 5 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ecolor::B; }
    for (std::size_t i = 45; i < 6 * COLORS_PER_SIDE; ++i) { _cube_data[i] = ecolor::D; }
}

bool Cube_bg_model::solved() const
{
    Cube_bg_model solved_cube;
    for (std::size_t i = 0; i < TOTAL_COLOR_CELLS; ++i) {
        if (_cube_data[i] != solved_cube._cube_data[i])
            return false;
    }

    return true;
}

std::array<Cube_bg_model::ecolor, COLORS_PER_SIDE> Cube_bg_model::get_side(ecolor side) const
{
    std::size_t first_i = static_cast<std::size_t>(side) * 9;

    std::array<ecolor, COLORS_PER_SIDE> result;
    for (std::size_t i = 0; i < 9; ++i)
        result[i] = _cube_data[first_i + i];

    return result;
}

std::array<Cube_bg_model::ecolor, COLORS_PER_SIDE> Cube_bg_model::get_side(rotation_side side) const
{
    return get_side(static_cast<ecolor>((static_cast<std::size_t>(side))));
}

std::array<Cube_bg_model::ecolor, TOTAL_COLOR_CELLS> Cube_bg_model::get_data() const
{
    return _cube_data;
}

Cube_bg_model::ecolor Cube_bg_model::operator[](unsigned index)
{
    if(index >= TOTAL_COLOR_CELLS)
        throw std::invalid_argument("Wrong index" + std::to_string(index));

    return _cube_data[index];
}

void Cube_bg_model::rotate(rotation_side side, rotation_type rot)
{
    int n = (rot == rotation_type::ROTATION_R) ? 1 : 3;
    for(int i = 0; i < n; i++) {
        // rotate selected side
        _rotate_side(side);

        // swap elements in the adjacent sides
        _rotate_adjacent(side);
    }
}

void Cube_bg_model::rotate(emove move)
{
    switch (move) {
    // upper
    case emove::U:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        break;
    case emove::Ur:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_L);
        break;
    case emove::U2:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        break;
    
    // left
    case emove::L:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        break;
    case emove::Lr:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_L);
        break;
    case emove::L2:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        break;
    
    // front
    case emove::F:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        break;
    case emove::Fr:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_L);
        break;
    case emove::F2:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        break;
    
    // right
    case emove::R:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        break;
    case emove::Rr:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_L);
        break;
    case emove::R2:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        break;
    
    // back
    case emove::B:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_R);
        break;
    case emove::Br:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_L);
        break;
    case emove::B2:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_R);
        break;
    
    // down
    case emove::D:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        break;
    case emove::Dr:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_L);
        break;
    case emove::D2:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        break;
    
    case emove::NO_MOVE:
        break;
    
    default:
        std::string value = std::to_string((int)move);
        throw std::logic_error("Cube_bg_modelCube::rotate Invalid enum value: " + value);
    }
}

void Cube_bg_model::revert_rotate(emove move)
{
    // make inverse move to given
    switch (move) {
    // upper
    case emove::U:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_L);
        break;
    case emove::Ur:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        break;
    case emove::U2:
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_U, rotation_type::ROTATION_R);
        break;
    
    // left
    case emove::L:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_L);
        break;
    case emove::Lr:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        break;
    case emove::L2:
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_L, rotation_type::ROTATION_R);
        break;
    
    // front
    case emove::F:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_L);
        break;
    case emove::Fr:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        break;
    case emove::F2:
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_F, rotation_type::ROTATION_R);
        break;
    
    // right
    case emove::R:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_L);
        break;
    case emove::Rr:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        break;
    case emove::R2:
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_R, rotation_type::ROTATION_R);
        break;
    
    // back
    case emove::B:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_L);
        break;
    case emove::Br:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_R);
        break;
    case emove::B2:
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_L);
        rotate(rotation_side::SIDE_B, rotation_type::ROTATION_L);
        break;
    
    // down
    case emove::D:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_L);
        break;
    case emove::Dr:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        break;
    case emove::D2:
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        rotate(rotation_side::SIDE_D, rotation_type::ROTATION_R);
        break;

    case emove::NO_MOVE:
        break;
    
    default:
        std::string value = std::to_string((int)move);
        throw std::logic_error("Cube_bg_modelCube::revert_rotate Invalid enum value: " + value);
    }
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
void Cube_bg_model::_rotate_side(rotation_side side)
{
    std::size_t first_i = static_cast<std::size_t>(side) * 9;

    ecolor new_side_data[9] = {
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
    for (std::size_t i = 0; i < 9; ++i) {
        _cube_data[first_i + i] = new_side_data[i];
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
 void Cube_bg_model::_rotate_adjacent(rotation_side side)
 {
     // a lot of swapping here...
     // (God pls trust me with the diagrams below...)
     ecolor tmp1, tmp2, tmp3; // for swapping
     switch(side) {
         case rotation_side::SIDE_U:
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
         case rotation_side::SIDE_L:
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
         case rotation_side::SIDE_F:
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
         case rotation_side::SIDE_R:
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
         case rotation_side::SIDE_B:
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
         case rotation_side::SIDE_D:
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

Cube_bg_model::ecolor Cube_bg_model::color(ecorner index) const
{
    return _cube_data[(uint8_t)index];
}

Cube_bg_model::ecolor Cube_bg_model::color(eedge index) const
{
    return _cube_data[(uint8_t)index];
}

/*
 * Checks if a facelet has one of the colors from the F/B axis, if 
 * not, checks if it's from the U/D axis and that the adjacent edge facelet
 * has a color from the R/L axis
 * Source: https://www.jaapsch.net/puzzles/thistle.htm#p2
 */
uint8_t Cube_bg_model::edge_orientation(const edge_t& edge) const
{
    /*
     * Conditions ("BAD" orinetation):
     * 
     * 1. Before ||: on first index in edge_t stored color from L/R or U/D side, so if
     * we have F/B color on this sides it have "BAD" orinetation
     * 
     * 2. After ||: if we have U/D color on L/R side or U/D side we have this cases:
     * 
     * Case 1: F/B color on R/L face and R/L color on U/D face => "BAD"
     * 
     * Case 2: F/B color on R/L face and R/L color on F/B face => "BAD"
     * 
     * Case 3: F/B color on U/D face and R/L color on F/B face => "BAD"
     * 
     * Otherwise (if result is false), orientation is "GOOD"
     */
    return (( edge[0] == ecolor::F || edge[0] == ecolor::B) ||
            ((edge[0] == ecolor::U || edge[0] == ecolor::D) &&
             (edge[1] == ecolor::R || edge[1] == ecolor::L)));
}

/*
 * Counts, how manu times we need to rotate corner piece clockwise, 
 * to match L/R piece facelet with L/R piece color
 * Source: https://www.ryanheise.com/cube/cube_laws.html
 */
uint8_t Cube_bg_model::corner_orientation(const corner_t& corner, epiece corner_piece) const
{
    // If corner from even tetrad, rotate logic must be different
    bool is_even_tetrad = false;

    if (corner_piece == epiece::ULB || corner_piece == epiece::DLF ||
        corner_piece == epiece::DRB || corner_piece == epiece::URF) {
        is_even_tetrad = true;
    }

    if (!is_even_tetrad) {
        if (corner[0] == ecolor::R || corner[0] == ecolor::L)
            return 0;
        if (corner[1] == ecolor::R || corner[1] == ecolor::L)
            return 1;
        if (corner[2] == ecolor::R || corner[2] == ecolor::L)
            return 2;
    } else {
        if (corner[0] == ecolor::R || corner[0] == ecolor::L)
            return 0;
        if (corner[1] == ecolor::R || corner[1] == ecolor::L)
            return 2;
        if (corner[2] == ecolor::R || corner[2] == ecolor::L)
            return 1;
    }

    throw std::logic_error("Cube_bg_model::corner_orientation unable to get orientation, corner must have a R / O facelet");
}

uint8_t Cube_bg_model::edge_index(const edge_t& edge) const
{ 
    // unique index based on color combinations
    uint8_t index = ((1 << (uint8_t)edge[0]) +
                     (1 << (uint8_t)edge[1]));

    /* The dependence of the obtained value at (1 << color[i]) on the base side of the color
     * U = 0 => 1
     * L = 1 => 2
     * F = 2 => 4
     * R = 3 => 8
     * B = 4 => 16
     * D = 5 => 32
     */

    switch (index) {
    case  3: // LU
        return 0;
    case 34: // LD
        return 1;
    case 40: // RD
        return 2;
    case  9: // RU
        return 3;
    case  6: // LF
        return 4;
    case 18: // LB
        return 5;
    case 12: // FR
        return 6;
    case 24: // RB
        return 7;
    case  5: // UF
        return 8;
    case 36: // DF
        return 9;
    case 48: // DB
        return 10;
    case 17: // UB
        return 11;
    default:
        std::string colors = color_name(edge[0]) + color_name(edge[1]);
        throw std::logic_error("Cube_bg_model::corner_index invalid combination of edge colors: " + colors);
    }
}

uint8_t Cube_bg_model::corner_index(const corner_t& corner) const
{
    // unique index based on color combinations
    uint8_t index = ((1 << (uint8_t)corner[0]) + 
                     (1 << (uint8_t)corner[1]) + 
                     (1 << (uint8_t)corner[2]));

    /* The dependence of the obtained value at (1 << color[i]) on the base side of the color
     * U = 0 => 1
     * L = 1 => 2
     * F = 2 => 4
     * R = 3 => 8
     * B = 4 => 16
     * D = 5 => 32
     */

    switch (index) {
    case 19: // LUB
        return 0;
    case  7: // LUF
        return 1;
    case 38: // LDF
        return 2;
    case 50: // LDB
        return 3;
    case 56: // RDB
        return 4;
    case 44: // RDF
        return 5;
    case 13: // RUF
        return 6;
    case 25: // RUB
        return 7;
    default:
        std::string colors = color_name(corner[0]) + color_name(corner[1]) + color_name(corner[2]);
        throw std::logic_error("Cube_bg_model::corner_index invalid combination of edge colors:" + colors);
    }
}

uint8_t Cube_bg_model::piece_index(epiece piece) const
{
    switch (piece) {
    case epiece::UL:
        return edge_index({color(eedge::UL), color(eedge::LU)});
    case epiece::DL:
        return edge_index({color(eedge::DL), color(eedge::LD)});
    case epiece::DR:
        return edge_index({color(eedge::DR), color(eedge::RD)});
    case epiece::UR:
        return edge_index({color(eedge::UR), color(eedge::RU)});
    case epiece::LF:
        return edge_index({color(eedge::LF), color(eedge::FL)});
    case epiece::LB:
        return edge_index({color(eedge::LB), color(eedge::BL)});
    case epiece::RF:
        return edge_index({color(eedge::RF), color(eedge::FR)});
    case epiece::RB:
        return edge_index({color(eedge::RB), color(eedge::BR)});
    case epiece::UF:
        return edge_index({color(eedge::UF), color(eedge::FU)});
    case epiece::DF:
        return edge_index({color(eedge::DF), color(eedge::FD)});
    case epiece::DB:
        return edge_index({color(eedge::DB), color(eedge::BD)});
    case epiece::UB:
        return edge_index({color(eedge::UB), color(eedge::BU)});
    case epiece::ULB:
        return corner_index({color(ecorner::LUB), color(ecorner::ULB), color(ecorner::BLU)});
    case epiece::ULF:
        return corner_index({color(ecorner::LUF), color(ecorner::ULF), color(ecorner::FLU)});
    case epiece::DLF:
        return corner_index({color(ecorner::LDF), color(ecorner::DLF), color(ecorner::FLD)});
    case epiece::DLB:
        return corner_index({color(ecorner::LDB), color(ecorner::DLB), color(ecorner::BLD)});
    case epiece::DRB:
        return corner_index({color(ecorner::RDB), color(ecorner::DRB), color(ecorner::BRD)});
    case epiece::DRF:
        return corner_index({color(ecorner::RDF), color(ecorner::DRF), color(ecorner::FRD)});
    case epiece::URF:
        return corner_index({color(ecorner::RUF), color(ecorner::URF), color(ecorner::FRU)});
    case epiece::URB:
        return corner_index({color(ecorner::RUB), color(ecorner::URB), color(ecorner::BRU)});
    default:
        std::string value = std::to_string((int)piece);
        throw std::logic_error("Cube_bg_model::piece_index invalid enum value: " + value);
    }
}

Cube_bg_model::edge_t Cube_bg_model::edge(epiece piece) const
{
    switch (piece) {
    case epiece::UL:
        return {color(eedge::LU), color(eedge::UL)};
    case epiece::DL:
        return {color(eedge::LD), color(eedge::DL)};
    case epiece::DR:
        return {color(eedge::RD), color(eedge::DR)};
    case epiece::UR:
        return {color(eedge::RU), color(eedge::UR)};
    case epiece::LF:
        return {color(eedge::LF), color(eedge::FL)};
    case epiece::LB:
        return {color(eedge::LB), color(eedge::BL)};
    case epiece::RF:
        return {color(eedge::RF), color(eedge::FR)};
    case epiece::RB:
        return {color(eedge::RB), color(eedge::BR)};
    case epiece::UF:
        return {color(eedge::UF), color(eedge::FU)};
    case epiece::DF:
        return {color(eedge::DF), color(eedge::FD)};
    case epiece::DB:
        return {color(eedge::DB), color(eedge::BD)};
    case epiece::UB:
        return {color(eedge::UB), color(eedge::BU)};
    default:
        std::string value = std::to_string((int)piece);
        throw std::logic_error("Cube_bg_model::edge invalid enum value: " + value);
    }
}

Cube_bg_model::corner_t Cube_bg_model::corner(epiece piece) const
{
    /*
     * Facelets in returning array:
     * 1. L/R
     * 2. U/D
     * 3. F/B
     */
    switch (piece) {
    case epiece::ULB:
        return {color(ecorner::LUB), color(ecorner::ULB), color(ecorner::BLU)};
    case epiece::ULF:
        return {color(ecorner::LUF), color(ecorner::ULF), color(ecorner::FLU)};
    case epiece::DLF:
        return {color(ecorner::LDF), color(ecorner::DLF), color(ecorner::FLD)};
    case epiece::DLB:
        return {color(ecorner::LDB), color(ecorner::DLB), color(ecorner::BLD)};
    case epiece::DRB:
        return {color(ecorner::RDB), color(ecorner::DRB), color(ecorner::BRD)};
    case epiece::DRF:
        return {color(ecorner::RDF), color(ecorner::DRF), color(ecorner::FRD)};
    case epiece::URF:
        return {color(ecorner::RUF), color(ecorner::URF), color(ecorner::FRU)};
    case epiece::URB:
        return {color(ecorner::RUB), color(ecorner::URB), color(ecorner::BRU)};
    default:
        throw std::logic_error("Cube_bg_model::corner invalid enum value: " + std::to_string((int)piece));
    }
}

std::string Cube_bg_model::color_name(ecolor color)
{
    switch (color) {
    case ecolor::U:
        return "W";
    case ecolor::L:
        return "G";
    case ecolor::F:
        return "R";
    case ecolor::R:
        return "B";
    case ecolor::B:
        return "O";
    case ecolor::D:
        return "Y";
    default:
        throw std::logic_error("Cube_bg_model::color_name invalid enum value: " + std::to_string((int)color));
    }
}

std::string Cube_bg_model::move_name(emove move)
{
    switch (move) {
    case emove::U:
        return "U";
    case emove::Ur:
        return "U'";
    case emove::U2:
        return "U2";
    case emove::L:
        return "L";
    case emove::Lr:
        return "L'";
    case emove::L2:
        return "L2";
    case emove::F:
        return "F";
    case emove::Fr:
        return "F'";
    case emove::F2:
        return "F2";
    case emove::R:
        return "R";
    case emove::Rr:
        return "R'";
    case emove::R2:
        return "R2";
    case emove::B:
        return "B";
    case emove::Br:
        return "B'";
    case emove::B2:
        return "B2";
    case emove::D:
        return "D";
    case emove::Dr:
        return "D'";
    case emove::D2:
        return "D2";
    case emove::NO_MOVE:
        return "";
    default:
        throw std::logic_error("Cube_bg_model::move_name invalid enum value: " + std::to_string((int)move));
    }
}
