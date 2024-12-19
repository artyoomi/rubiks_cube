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
        (E_FU == ecolour::G || E_FU == ecolour::B) && (E_UF == ecolour::W || E_UF == ecolour::Y) &&
        (E_FD == ecolour::G || E_FD == ecolour::B) && (E_DF == ecolour::W || E_DF == ecolour::Y) &&
        (E_BU == ecolour::G || E_BU == ecolour::B) && (E_UB == ecolour::W || E_UB == ecolour::Y) &&
        (E_BD == ecolour::G || E_BD == ecolour::B) && (E_DB == ecolour::W || E_DB == ecolour::Y) &&
        // checks that the corners are oriented (their L/R facelet is in the L/R face)
        (C_LFU == ecolour::O || C_LFU == ecolour::R) && (C_LUB == ecolour::O || C_LUB == ecolour::R) &&
        (C_LDF == ecolour::O || C_LDF == ecolour::R) && (C_LBD == ecolour::O || C_LBD == ecolour::R) &&
        (C_RBU == ecolour::O || C_RBU == ecolour::R) && (C_RDB == ecolour::O || C_RDB == ecolour::R) &&
        (C_RFD == ecolour::O || C_RFD == ecolour::R) && (C_RUF == ecolour::O || C_RUF == ecolour::R);
}
