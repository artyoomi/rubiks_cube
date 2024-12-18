#include "thistlethwaite.h"

Thistlethwaite::Thistlethwaite()
{
    // give name to each phase
    _phase1.name = "Phase 1. G0->G1";
    _phase2.name = "Phase 2. G1->G2";
    _phase3.name = "Phase 3. G2->G3";
    _phase4.name = "Phase 4. G3->G4";

    // combine phases in one vector
    _phases = {&_phase1, &_phase2, &_phase3, &_phase4};
    
    // load database for each phase before start solving
    for (auto& phase : _phases)
        phase->load_db();
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

std::vector<std::pair<rotation_side, rotation_type>> Thistlethwaite::solve(const Cube_bg_model &const_cube) const
{
    // vector with all moves to solve cube
    std::vector<EMOVE> result;

    // get copy of given cube
    Cube_bg_model cube = const_cube;

    // initialize timer to get solve time
    Timer  timer;
    double full_solve_time = 0;

    // create A* searcher object
    AStar astar;

    std::cout << "Thistlethwaite's algorithm:" << std::endl;

    for (const auto& phase : _phases) {
        // start timer
        timer.set();

        std::cout << phase->name << ": ";

        // get partial group solution
        std::vector<EMOVE> phase_result = astar.search(cube, *phase->phase_info, *phase->database);

        // add partial solution to the end result
        result.insert(result.end(), phase_result.begin(), phase_result.end());

        // perform the partial group solution to pass the new state to the next group
        for (const EMOVE move : phase_result)
            cube.rotate(move);

        // group solve statistics
        double phase_solve_time = timer.get();

        std::cout << "Elapsed time: " << phase_solve_time << "ms, ";
        std::cout << "Moves: " << phase_result.size() << std::endl;
        full_solve_time += phase_solve_time;
    }

    // overall solve statistics
    std::cout << std::endl;
    std::cout << "Solved in: " << (int)full_solve_time / 1000 << " seconds " << "(" << full_solve_time << "ms)." << std::endl;
    std::cout << "Moves(" << result.size() << "): ";
    for (const auto& move : result)
        std::cout << cube.move_name(move);
    std::cout << std::endl;

    // convert emove to rot notation
    auto new_result = emove_to_rot(result);

    return new_result;
}
