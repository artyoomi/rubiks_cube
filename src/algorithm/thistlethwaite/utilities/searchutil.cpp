#include "searchutil.h"

bool utilities::redundant(emove curr, emove last)
{
    // moves on the same face are redundant since:
    // L->L     is the same as L2
    // L->L'    cancels each other out
    // L->L2    is the same as L'

    // moves on opposite faces are redundant since:
    // R->L is the same as L->R
    // but since it's impossible to prune both of these, only check for one of the two combinations

    if ((curr == emove::U || curr == emove::Ur || curr == emove::U2) &&
       ((last == emove::U || last == emove::Ur || last == emove::U2) ||
        (last == emove::D || last == emove::Dr || last == emove::D2)))
        return true;

    if ((curr == emove::L || curr == emove::Lr || curr == emove::L2) &&
       ((last == emove::L || last == emove::Lr || last == emove::L2) ||
        (last == emove::R || last == emove::Rr || last == emove::R2)))
        return true;

    if ((curr == emove::F || curr == emove::Fr || curr == emove::F2) &&
       ((last == emove::F || last == emove::Fr || last == emove::F2) ||
        (last == emove::B || last == emove::Br || last == emove::B2)))
        return true;

    if ((curr == emove::R || curr == emove::Rr || curr == emove::R2) &&
        (last == emove::R || last == emove::Rr || last == emove::R2))
        return true;

    if ((curr == emove::B || curr == emove::Br || curr == emove::B2) &&
        (last == emove::B || last == emove::Rr || last == emove::B2))
        return true;

    if ((curr == emove::D || curr == emove::Dr || curr == emove::D2) &&
        (last == emove::D || last == emove::Dr || last == emove::D2))
        return true;

    return false;
}
