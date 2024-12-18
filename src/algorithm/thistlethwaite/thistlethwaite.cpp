#include "thistlethwaite.h"

Thistlethwaite::Thistlethwaite()
{
    // init groups
    m_G0G1.useDatabase = true;
    m_G1G2.useDatabase = true;
    m_G2G3.useDatabase = true;
    m_G3G4.useDatabase = true;

    m_G0G1.name = "G0->G1";
    m_G1G2.name = "G1->G2";
    m_G2G3.name = "G2->G3";
    m_G3G4.name = "G3->G4";

    m_groups = {
        &m_G0G1,
        &m_G1G2,
        &m_G2G3,
        &m_G3G4
    };
    
    for (auto& group : m_groups)
    {
        if (group->useDatabase)
        {
            group->load_db();
        }
    }
}

std::vector<std::pair<rotation_side, rotation_type>> Thistlethwaite::emove_to_rot(std::vector<EMOVE> moves) const
{
    std::vector<std::pair<rotation_side, rotation_type>> result;

    for (const EMOVE& move : moves) {
        switch (move)
        {
        case EMOVE::U:
            result.push_back(std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R));
            break;
        case EMOVE::Up:
            result.push_back(std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_L));
            break;
        case EMOVE::U2:
            result.push_back(std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R));
            result.push_back(std::make_pair(rotation_side::SIDE_U, rotation_type::ROTATION_R));
            break;
        case EMOVE::L:
            result.push_back(std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_R));
            break;
        case EMOVE::Lp:
            result.push_back(std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_L));
            break;
        case EMOVE::L2:
            result.push_back(std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_R));
            result.push_back(std::make_pair(rotation_side::SIDE_L, rotation_type::ROTATION_R));
            break;
        case EMOVE::F:
            result.push_back(std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R));
            break;
        case EMOVE::Fp:
            result.push_back(std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_L));
            break;
        case EMOVE::F2:
            result.push_back(std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R));
            result.push_back(std::make_pair(rotation_side::SIDE_F, rotation_type::ROTATION_R));
            break;
        case EMOVE::R:
            result.push_back(std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R));
            break;
        case EMOVE::Rp:
            result.push_back(std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_L));
            break;
        case EMOVE::R2:
            result.push_back(std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R));
            result.push_back(std::make_pair(rotation_side::SIDE_R, rotation_type::ROTATION_R));
            break;
        case EMOVE::B:
            result.push_back(std::make_pair(rotation_side::SIDE_B, rotation_type::ROTATION_R));
            break;
        case EMOVE::Bp:
            result.push_back(std::make_pair(rotation_side::SIDE_B, rotation_type::ROTATION_L));
            break;
        case EMOVE::B2:
            result.push_back(std::make_pair(rotation_side::SIDE_B, rotation_type::ROTATION_R));
            result.push_back(std::make_pair(rotation_side::SIDE_B, rotation_type::ROTATION_R));
            break;
        case EMOVE::D:
            result.push_back(std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R));
            break;
        case EMOVE::Dp:
            result.push_back(std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_L));
            break;
        case EMOVE::D2:
            result.push_back(std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R));
            result.push_back(std::make_pair(rotation_side::SIDE_D, rotation_type::ROTATION_R));
            break;
        case EMOVE::NO_MOVE:
            break;
        default:
            std::string value = std::to_string((int)move);
            throw std::logic_error("Thistlethwaite::emove_to_rot invalid enum value: " + value);
        }
    }

    return result;
}

std::vector<std::pair<rotation_side, rotation_type>> Thistlethwaite::solve(const Cube_bg_model &cube) const
{
    Timer              timer;
    Cube_bg_model      cubeState = cube;
    std::vector<EMOVE> result;
    double             combinedSolveTime = 0;

    std::cout << "Thistlethwaite's algorithm:" << std::endl;

    for (const auto& group : m_groups)
    {
        timer.set();

        std::cout << group->name << ": ";

        // partial group solution
        std::vector<EMOVE> groupResult;
        AStar astar;

        groupResult = astar.search(cubeState, *group->goal, *group->database);

        // add partial solution to the end result
        result.insert(result.end(), groupResult.begin(), groupResult.end());
        // perform the partial group solution to pass the new state to the next group
        for (const EMOVE move : groupResult)
            cubeState.rotate(move);

        // group solve statistics
        double groupSolveTime = timer.get();

        std::cout << "Elapsed time: " << groupSolveTime << "ms, ";
        std::cout << "Moves: " << groupResult.size() << std::endl;
        combinedSolveTime += groupSolveTime;
    }

    // overall solve statistics
    std::cout << std::endl;
    std::cout << "Solved in: " << (int)combinedSolveTime / 1000 << " seconds " << "(" << combinedSolveTime << "ms)." << std::endl;
    std::cout << "Moves(" << result.size() << "): ";
    for (const auto& move : result)
    {
        std::cout << cube.move_name(move);
    }
    std::cout << std::endl;

    auto new_result = emove_to_rot(result);

    return new_result;
}
