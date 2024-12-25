#include "phase2_info.h"

bool Phase2_info::solved(const Cube_bg_model& cube) const
{
    // // M-slice edges
    // ecolor E_FU = cube.color(eedge::FU);
    // ecolor E_FD = cube.color(eedge::FD);
    // ecolor E_BU = cube.color(eedge::BU);
    // ecolor E_BD = cube.color(eedge::BD);

    // ecolor E_UF = cube.color(eedge::UF);
    // ecolor E_DF = cube.color(eedge::DF);
    // ecolor E_UB = cube.color(eedge::UB);
    // ecolor E_DB = cube.color(eedge::DB);

    // // corner facelets from the L/R axis
    // ecolor C_LFU = cube.color(ecorner::LUF);
    // ecolor C_LUB = cube.color(ecorner::LUB);
    // ecolor C_LDF = cube.color(ecorner::LDF);
    // ecolor C_LBD = cube.color(ecorner::LDB);
    // ecolor C_RBU = cube.color(ecorner::RUB);
    // ecolor C_RDB = cube.color(ecorner::RDB);
    // ecolor C_RFD = cube.color(ecorner::RDF);
    // ecolor C_RUF = cube.color(ecorner::RUF);

    // return
    //     // checks that the M-slice edges are in the M-slice
    //     (E_FU == ecolor::F || E_FU == ecolor::B) && (E_UF == ecolor::U || E_UF == ecolor::D) &&
    //     (E_FD == ecolor::F || E_FD == ecolor::B) && (E_DF == ecolor::U || E_DF == ecolor::D) &&
    //     (E_BU == ecolor::F || E_BU == ecolor::B) && (E_UB == ecolor::U || E_UB == ecolor::D) &&
    //     (E_BD == ecolor::F || E_BD == ecolor::B) && (E_DB == ecolor::U || E_DB == ecolor::D) &&
    //     // checks that the corners are oriented (their L/R facelet is in the L/R face)
    //     (C_LFU == ecolor::L || C_LFU == ecolor::R) && (C_LUB == ecolor::L || C_LUB == ecolor::R) &&
    //     (C_LDF == ecolor::L || C_LDF == ecolor::R) && (C_LBD == ecolor::L || C_LBD == ecolor::R) &&
    //     (C_RBU == ecolor::L || C_RBU == ecolor::R) && (C_RDB == ecolor::L || C_RDB == ecolor::R) &&
    //     (C_RFD == ecolor::L || C_RFD == ecolor::R) && (C_RUF == ecolor::L || C_RUF == ecolor::R);

    /*
     * Here we return true only when all corners are oriented
     * (corner is oriented if his L/R colours match with L/R center)
     */
    return cube.edge_orientation(cube.edge(epiece::UF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::UB)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DB)) == 0 &&
           cube.corner_orientation(cube.corner(epiece::ULB)) == 0 &&
           cube.corner_orientation(cube.corner(epiece::ULF)) == 0 &&
           cube.corner_orientation(cube.corner(epiece::DLF)) == 0 &&
           cube.corner_orientation(cube.corner(epiece::DLB)) == 0 &&
           cube.corner_orientation(cube.corner(epiece::DRB)) == 0 &&
           cube.corner_orientation(cube.corner(epiece::DRF)) == 0 &&
           cube.corner_orientation(cube.corner(epiece::URF)) == 0 &&
           cube.corner_orientation(cube.corner(epiece::URB)) == 0;
}
