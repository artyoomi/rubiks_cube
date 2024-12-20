#ifndef RNGENERATOR_H
#define RNGENERATOR_H

#include <random>
#include <algorithm>

class RN_generator
{
public:
    RN_generator(int low, int high)
        : _random_engine{std::random_device{}()},
          _distribution{low, high}
    {}

    int get()
    {
        return _distribution(_random_engine);
    }
private:
    std::mt19937                       _random_engine;
    std::uniform_int_distribution<int> _distribution;
};

#endif // RNGENERATOR_H
