#include "phase1_info.h"

bool Phase1_info::solved(const Cube_bg_model& cube) const
{
    using ECOLOUR   = Cube_bg_model::ECOLOUR;
    using EEDGE     = Cube_bg_model::EEDGE;

    ECOLOUR E_UB = cube.colour(EEDGE::UB);
    ECOLOUR E_UR = cube.colour(EEDGE::UR);
    ECOLOUR E_UF = cube.colour(EEDGE::UF);
    ECOLOUR E_UL = cube.colour(EEDGE::UL);

    ECOLOUR E_LU = cube.colour(EEDGE::LU);
    ECOLOUR E_LF = cube.colour(EEDGE::LF);
    ECOLOUR E_LD = cube.colour(EEDGE::LD);
    ECOLOUR E_LB = cube.colour(EEDGE::LB);

    ECOLOUR E_FU = cube.colour(EEDGE::FU);
    ECOLOUR E_FR = cube.colour(EEDGE::FR);
    ECOLOUR E_FD = cube.colour(EEDGE::FD);
    ECOLOUR E_FL = cube.colour(EEDGE::FL);

    ECOLOUR E_RU = cube.colour(EEDGE::RU);
    ECOLOUR E_RB = cube.colour(EEDGE::RB);
    ECOLOUR E_RD = cube.colour(EEDGE::RD);
    ECOLOUR E_RF = cube.colour(EEDGE::RF);

    ECOLOUR E_BU = cube.colour(EEDGE::BU);
    ECOLOUR E_BL = cube.colour(EEDGE::BL);
    ECOLOUR E_BD = cube.colour(EEDGE::BD);
    ECOLOUR E_BR = cube.colour(EEDGE::BR);

    ECOLOUR E_DF = cube.colour(EEDGE::DF);
    ECOLOUR E_DR = cube.colour(EEDGE::DR);
    ECOLOUR E_DB = cube.colour(EEDGE::DB);
    ECOLOUR E_DL = cube.colour(EEDGE::DL);

    // same logic from Cube_bg_model::getEdgeOrientation
    return 
        ((E_FR == ECOLOUR::B || E_FR == ECOLOUR::G) || ((E_FR == ECOLOUR::W || E_FR == ECOLOUR::Y) && (E_RF == ECOLOUR::O || E_RF == ECOLOUR::R))) &&
        ((E_FL == ECOLOUR::B || E_FL == ECOLOUR::G) || ((E_FL == ECOLOUR::W || E_FL == ECOLOUR::Y) && (E_LF == ECOLOUR::O || E_LF == ECOLOUR::R))) &&
        ((E_FU == ECOLOUR::B || E_FU == ECOLOUR::G) || ((E_FU == ECOLOUR::W || E_FU == ECOLOUR::Y) && (E_UF == ECOLOUR::O || E_UF == ECOLOUR::R))) &&
        ((E_FD == ECOLOUR::B || E_FD == ECOLOUR::G) || ((E_FD == ECOLOUR::W || E_FD == ECOLOUR::Y) && (E_DF == ECOLOUR::O || E_DF == ECOLOUR::R))) &&

        ((E_BR == ECOLOUR::B || E_BR == ECOLOUR::G) || ((E_BR == ECOLOUR::W || E_BR == ECOLOUR::Y) && (E_RB == ECOLOUR::O || E_RB == ECOLOUR::R))) &&
        ((E_BL == ECOLOUR::B || E_BL == ECOLOUR::G) || ((E_BL == ECOLOUR::W || E_BL == ECOLOUR::Y) && (E_LB == ECOLOUR::O || E_LB == ECOLOUR::R))) &&
        ((E_BU == ECOLOUR::B || E_BU == ECOLOUR::G) || ((E_BU == ECOLOUR::W || E_BU == ECOLOUR::Y) && (E_UB == ECOLOUR::O || E_UB == ECOLOUR::R))) &&
        ((E_BD == ECOLOUR::B || E_BD == ECOLOUR::G) || ((E_BD == ECOLOUR::W || E_BD == ECOLOUR::Y) && (E_DB == ECOLOUR::O || E_DB == ECOLOUR::R))) &&

        ((E_RU == ECOLOUR::R || E_RU == ECOLOUR::O) || ((E_RU == ECOLOUR::W || E_RU == ECOLOUR::Y) && (E_UR == ECOLOUR::B || E_UR == ECOLOUR::G))) &&
        ((E_RD == ECOLOUR::R || E_RD == ECOLOUR::O) || ((E_RD == ECOLOUR::W || E_RD == ECOLOUR::Y) && (E_DR == ECOLOUR::B || E_DR == ECOLOUR::G))) &&
        ((E_LU == ECOLOUR::R || E_LU == ECOLOUR::O) || ((E_LU == ECOLOUR::W || E_LU == ECOLOUR::Y) && (E_UL == ECOLOUR::B || E_UL == ECOLOUR::G))) &&
        ((E_LD == ECOLOUR::R || E_LD == ECOLOUR::O) || ((E_LD == ECOLOUR::W || E_LD == ECOLOUR::Y) && (E_DL == ECOLOUR::B || E_DL == ECOLOUR::G)));
}
