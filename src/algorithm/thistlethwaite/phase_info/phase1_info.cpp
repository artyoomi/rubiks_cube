#include "phase1_info.h"

bool Phase1_info::solved(const Cube_bg_model& cube) const
{
    ecolour E_UB = cube.colour(eedge::UB);
    ecolour E_UR = cube.colour(eedge::UR);
    ecolour E_UF = cube.colour(eedge::UF);
    ecolour E_UL = cube.colour(eedge::UL);

    ecolour E_LU = cube.colour(eedge::LU);
    ecolour E_LF = cube.colour(eedge::LF);
    ecolour E_LD = cube.colour(eedge::LD);
    ecolour E_LB = cube.colour(eedge::LB);

    ecolour E_FU = cube.colour(eedge::FU);
    ecolour E_FR = cube.colour(eedge::FR);
    ecolour E_FD = cube.colour(eedge::FD);
    ecolour E_FL = cube.colour(eedge::FL);

    ecolour E_RU = cube.colour(eedge::RU);
    ecolour E_RB = cube.colour(eedge::RB);
    ecolour E_RD = cube.colour(eedge::RD);
    ecolour E_RF = cube.colour(eedge::RF);

    ecolour E_BU = cube.colour(eedge::BU);
    ecolour E_BL = cube.colour(eedge::BL);
    ecolour E_BD = cube.colour(eedge::BD);
    ecolour E_BR = cube.colour(eedge::BR);

    ecolour E_DF = cube.colour(eedge::DF);
    ecolour E_DR = cube.colour(eedge::DR);
    ecolour E_DB = cube.colour(eedge::DB);
    ecolour E_DL = cube.colour(eedge::DL);

    // same logic from Cube_bg_model::getEdgeOrientation
    return 
        ((E_FR == ecolour::B || E_FR == ecolour::F) || ((E_FR == ecolour::U || E_FR == ecolour::D) && (E_RF == ecolour::L || E_RF == ecolour::R))) &&
        ((E_FL == ecolour::B || E_FL == ecolour::F) || ((E_FL == ecolour::U || E_FL == ecolour::D) && (E_LF == ecolour::L || E_LF == ecolour::R))) &&
        ((E_FU == ecolour::B || E_FU == ecolour::F) || ((E_FU == ecolour::U || E_FU == ecolour::D) && (E_UF == ecolour::L || E_UF == ecolour::R))) &&
        ((E_FD == ecolour::B || E_FD == ecolour::F) || ((E_FD == ecolour::U || E_FD == ecolour::D) && (E_DF == ecolour::L || E_DF == ecolour::R))) &&

        ((E_BR == ecolour::B || E_BR == ecolour::F) || ((E_BR == ecolour::U || E_BR == ecolour::D) && (E_RB == ecolour::L || E_RB == ecolour::R))) &&
        ((E_BL == ecolour::B || E_BL == ecolour::F) || ((E_BL == ecolour::U || E_BL == ecolour::D) && (E_LB == ecolour::L || E_LB == ecolour::R))) &&
        ((E_BU == ecolour::B || E_BU == ecolour::F) || ((E_BU == ecolour::U || E_BU == ecolour::D) && (E_UB == ecolour::L || E_UB == ecolour::R))) &&
        ((E_BD == ecolour::B || E_BD == ecolour::F) || ((E_BD == ecolour::U || E_BD == ecolour::D) && (E_DB == ecolour::L || E_DB == ecolour::R))) &&

        ((E_RU == ecolour::R || E_RU == ecolour::L) || ((E_RU == ecolour::U || E_RU == ecolour::D) && (E_UR == ecolour::B || E_UR == ecolour::F))) &&
        ((E_RD == ecolour::R || E_RD == ecolour::L) || ((E_RD == ecolour::U || E_RD == ecolour::D) && (E_DR == ecolour::B || E_DR == ecolour::F))) &&
        ((E_LU == ecolour::R || E_LU == ecolour::L) || ((E_LU == ecolour::U || E_LU == ecolour::D) && (E_UL == ecolour::B || E_UL == ecolour::F))) &&
        ((E_LD == ecolour::R || E_LD == ecolour::L) || ((E_LD == ecolour::U || E_LD == ecolour::D) && (E_DL == ecolour::B || E_DL == ecolour::F)));
}
