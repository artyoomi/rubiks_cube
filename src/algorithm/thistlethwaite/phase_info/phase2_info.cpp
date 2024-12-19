#include "phase2_info.h"

bool Phase2_info::solved(const Cube_bg_model& cube) const
{
    // M-slice edges
    ecolour E_FU = cube.colour(eedge::FU);
    ecolour E_FD = cube.colour(eedge::FD);
    ecolour E_BU = cube.colour(eedge::BU);
    ecolour E_BD = cube.colour(eedge::BD);

    ecolour E_UF = cube.colour(eedge::UF);
    ecolour E_DF = cube.colour(eedge::DF);
    ecolour E_UB = cube.colour(eedge::UB);
    ecolour E_DB = cube.colour(eedge::DB);

    // corner facelets from the L/R axis
    ecolour C_LFU = cube.colour(ecorner::LUF);
    ecolour C_LUB = cube.colour(ecorner::LUB);
    ecolour C_LDF = cube.colour(ecorner::LDF);
    ecolour C_LBD = cube.colour(ecorner::LDB);
    ecolour C_RBU = cube.colour(ecorner::RUB);
    ecolour C_RDB = cube.colour(ecorner::RDB);
    ecolour C_RFD = cube.colour(ecorner::RDF);
    ecolour C_RUF = cube.colour(ecorner::RUF);

    return
        // checks that the M-slice edges are in the M-slice
        (E_FU == ecolour::F || E_FU == ecolour::B) && (E_UF == ecolour::U || E_UF == ecolour::D) &&
        (E_FD == ecolour::F || E_FD == ecolour::B) && (E_DF == ecolour::U || E_DF == ecolour::D) &&
        (E_BU == ecolour::F || E_BU == ecolour::B) && (E_UB == ecolour::U || E_UB == ecolour::D) &&
        (E_BD == ecolour::F || E_BD == ecolour::B) && (E_DB == ecolour::U || E_DB == ecolour::D) &&
        // checks that the corners are oriented (their L/R facelet is in the L/R face)
        (C_LFU == ecolour::L || C_LFU == ecolour::R) && (C_LUB == ecolour::L || C_LUB == ecolour::R) &&
        (C_LDF == ecolour::L || C_LDF == ecolour::R) && (C_LBD == ecolour::L || C_LBD == ecolour::R) &&
        (C_RBU == ecolour::L || C_RBU == ecolour::R) && (C_RDB == ecolour::L || C_RDB == ecolour::R) &&
        (C_RFD == ecolour::L || C_RFD == ecolour::R) && (C_RUF == ecolour::L || C_RUF == ecolour::R);
}
