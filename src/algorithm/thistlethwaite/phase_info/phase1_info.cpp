#include "phase1_info.h"

bool Phase1_info::solved(const Cube_bg_model& cube) const
{
    // ecolor E_UB = cube.color(eedge::UB);
    // ecolor E_UR = cube.color(eedge::UR);
    // ecolor E_UF = cube.color(eedge::UF);
    // ecolor E_UL = cube.color(eedge::UL);

    // ecolor E_LU = cube.color(eedge::LU);
    // ecolor E_LF = cube.color(eedge::LF);
    // ecolor E_LD = cube.color(eedge::LD);
    // ecolor E_LB = cube.color(eedge::LB);

    // ecolor E_FU = cube.color(eedge::FU);
    // ecolor E_FR = cube.color(eedge::FR);
    // ecolor E_FD = cube.color(eedge::FD);
    // ecolor E_FL = cube.color(eedge::FL);

    // ecolor E_RU = cube.color(eedge::RU);
    // ecolor E_RB = cube.color(eedge::RB);
    // ecolor E_RD = cube.color(eedge::RD);
    // ecolor E_RF = cube.color(eedge::RF);

    // ecolor E_BU = cube.color(eedge::BU);
    // ecolor E_BL = cube.color(eedge::BL);
    // ecolor E_BD = cube.color(eedge::BD);
    // ecolor E_BR = cube.color(eedge::BR);

    // ecolor E_DF = cube.color(eedge::DF);
    // ecolor E_DR = cube.color(eedge::DR);
    // ecolor E_DB = cube.color(eedge::DB);
    // ecolor E_DL = cube.color(eedge::DL);

    // same logic from Cube_bg_model::getEdgeOrientation
    // return 
    //     ((E_FR == ecolor::B || E_FR == ecolor::F) || ((E_FR == ecolor::U || E_FR == ecolor::D) && (E_RF == ecolor::L || E_RF == ecolor::R))) &&
    //     ((E_FL == ecolor::B || E_FL == ecolor::F) || ((E_FL == ecolor::U || E_FL == ecolor::D) && (E_LF == ecolor::L || E_LF == ecolor::R))) &&
    //     ((E_FU == ecolor::B || E_FU == ecolor::F) || ((E_FU == ecolor::U || E_FU == ecolor::D) && (E_UF == ecolor::L || E_UF == ecolor::R))) &&
    //     ((E_FD == ecolor::B || E_FD == ecolor::F) || ((E_FD == ecolor::U || E_FD == ecolor::D) && (E_DF == ecolor::L || E_DF == ecolor::R))) &&

    //     ((E_BR == ecolor::B || E_BR == ecolor::F) || ((E_BR == ecolor::U || E_BR == ecolor::D) && (E_RB == ecolor::L || E_RB == ecolor::R))) &&
    //     ((E_BL == ecolor::B || E_BL == ecolor::F) || ((E_BL == ecolor::U || E_BL == ecolor::D) && (E_LB == ecolor::L || E_LB == ecolor::R))) &&
    //     ((E_BU == ecolor::B || E_BU == ecolor::F) || ((E_BU == ecolor::U || E_BU == ecolor::D) && (E_UB == ecolor::L || E_UB == ecolor::R))) &&
    //     ((E_BD == ecolor::B || E_BD == ecolor::F) || ((E_BD == ecolor::U || E_BD == ecolor::D) && (E_DB == ecolor::L || E_DB == ecolor::R))) &&

    //     ((E_RU == ecolor::R || E_RU == ecolor::L) || ((E_RU == ecolor::U || E_RU == ecolor::D) && (E_UR == ecolor::B || E_UR == ecolor::F))) &&
    //     ((E_RD == ecolor::R || E_RD == ecolor::L) || ((E_RD == ecolor::U || E_RD == ecolor::D) && (E_DR == ecolor::B || E_DR == ecolor::F))) &&
    //     ((E_LU == ecolor::R || E_LU == ecolor::L) || ((E_LU == ecolor::U || E_LU == ecolor::D) && (E_UL == ecolor::B || E_UL == ecolor::F))) &&
    //     ((E_LD == ecolor::R || E_LD == ecolor::L) || ((E_LD == ecolor::U || E_LD == ecolor::D) && (E_DL == ecolor::B || E_DL == ecolor::F)));
    
    return cube.edge_orientation(cube.edge(epiece::UL)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DL)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DR)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::UR)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::LF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::LB)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::RF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::RB)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::UF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DF)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::DB)) == 0 &&
           cube.edge_orientation(cube.edge(epiece::UB)) == 0;
}
