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
        ((E_FR == ecolour::B || E_FR == ecolour::G) || ((E_FR == ecolour::W || E_FR == ecolour::Y) && (E_RF == ecolour::O || E_RF == ecolour::R))) &&
        ((E_FL == ecolour::B || E_FL == ecolour::G) || ((E_FL == ecolour::W || E_FL == ecolour::Y) && (E_LF == ecolour::O || E_LF == ecolour::R))) &&
        ((E_FU == ecolour::B || E_FU == ecolour::G) || ((E_FU == ecolour::W || E_FU == ecolour::Y) && (E_UF == ecolour::O || E_UF == ecolour::R))) &&
        ((E_FD == ecolour::B || E_FD == ecolour::G) || ((E_FD == ecolour::W || E_FD == ecolour::Y) && (E_DF == ecolour::O || E_DF == ecolour::R))) &&

        ((E_BR == ecolour::B || E_BR == ecolour::G) || ((E_BR == ecolour::W || E_BR == ecolour::Y) && (E_RB == ecolour::O || E_RB == ecolour::R))) &&
        ((E_BL == ecolour::B || E_BL == ecolour::G) || ((E_BL == ecolour::W || E_BL == ecolour::Y) && (E_LB == ecolour::O || E_LB == ecolour::R))) &&
        ((E_BU == ecolour::B || E_BU == ecolour::G) || ((E_BU == ecolour::W || E_BU == ecolour::Y) && (E_UB == ecolour::O || E_UB == ecolour::R))) &&
        ((E_BD == ecolour::B || E_BD == ecolour::G) || ((E_BD == ecolour::W || E_BD == ecolour::Y) && (E_DB == ecolour::O || E_DB == ecolour::R))) &&

        ((E_RU == ecolour::R || E_RU == ecolour::O) || ((E_RU == ecolour::W || E_RU == ecolour::Y) && (E_UR == ecolour::B || E_UR == ecolour::G))) &&
        ((E_RD == ecolour::R || E_RD == ecolour::O) || ((E_RD == ecolour::W || E_RD == ecolour::Y) && (E_DR == ecolour::B || E_DR == ecolour::G))) &&
        ((E_LU == ecolour::R || E_LU == ecolour::O) || ((E_LU == ecolour::W || E_LU == ecolour::Y) && (E_UL == ecolour::B || E_UL == ecolour::G))) &&
        ((E_LD == ecolour::R || E_LD == ecolour::O) || ((E_LD == ecolour::W || E_LD == ecolour::Y) && (E_DL == ecolour::B || E_DL == ecolour::G)));
}
