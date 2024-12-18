#ifndef GROUPS_H
#define GROUPS_H

#include <iostream>
#include <string>

#include "database/phase1_database.h"
#include "database/phase2_database.h"
#include "database/phase3_database.h"
#include "database/phase4_database.h"

#include "Goals/G0_G1_goal.h"
#include "Goals/G1_G2_goal.h"
#include "Goals/G2_G3_goal.h"
#include "Goals/G3_G4_goal.h"

#include "thistlethwaite/utilities/db_generator.h"

// base class for the 4 groups in Thistlethwaite's algorithm
struct Group {
    // loads the database or generates it if a file is not provided
    void load_db()
    {
        std::cout << "Loading database for " << name << "..." << std::endl;
        if (database->load())
        {
            std::cout << "Loaded database for " << name << " successfully." << std::endl;
        }
        else
        {
            std::cout << "Failed to load database for " << name << ". generating:" << std::endl;
            databaseGen.generate(*goal, *database);
        }
    }

    bool        useDatabase = false;
    Database*   database    = nullptr;
    Goal*       goal        = nullptr;
    std::string name;

protected:
    DB_generator databaseGen;
};

template<typename DatabaseType, typename GoalType>
struct TypedGroup : public Group
{
    TypedGroup()
    {
        database = &m_database;
        goal	 = &m_goal;
    }

private:
    DatabaseType m_database;
    GoalType m_goal;
};

#endif // GROUPS_H
