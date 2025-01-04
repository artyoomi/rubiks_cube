#pragma once

#include <iostream>
#include <string>

#include "database/phase1_database.h"
#include "database/phase2_database.h"
#include "database/phase3_database.h"
#include "database/phase4_database.h"

#include "phase_info/phase1_info.h"
#include "phase_info/phase2_info.h"
#include "phase_info/phase3_info.h"
#include "phase_info/phase4_info.h"

#include "utilities/db_generator.h"

/*
 * Base class for one phase in Thistlethwaite's algorithm
 */
struct Phase {
    // loads the database or generates it if a file is not provided
    void load_db()
    {
        std::cout << "Loading database for " << name << "..." << std::endl;
        if (database->load())
            std::cout << "Loaded database for " << name << " successfully." << std::endl;
        else {
            std::cout << "Failed to load database for " << name << ". generating:" << std::endl;
            __db_generator.generate(*phase_info, *database);
        }
    }

    Database   *database   = nullptr;
    Phase_info *phase_info = nullptr;

    // name of current phase
    std::string name;

protected:
    DB_generator __db_generator;
};

/*
 * Class to correctly create each phase object
 */
template<typename DatabaseType, typename PhaseType>
struct TypedPhase : public Phase {
    TypedPhase()
    {
        database   = &_db;
        phase_info = &_phase_info;
    }

private:
    DatabaseType _db;
    PhaseType    _phase_info;
};
