#pragma once

#include <cstdint>

#include <array>

// all rankers require a permutation to be from 0 to N

// 0!.....12! (largest needed factorial is 12!)
static const std::array<uint32_t, 13> factorial = {
            1, // 0!
            1, // 1!
            2, // 2!
            6, // 3!
           24, // 4!
          120, // 5!
          720, // 6!
         5040, // 7!
        40320, // 8!
       362880, // 9!
      3628800, // 10!
     39916800, // 11!
    479001600  // 12!
};


// ranks combinations from 0 to nCk - 1
template<uint8_t K>
struct CombRanker {
    // calculate nCk = n! / (k!(n - k)!)
    uint32_t nCk(uint8_t n, uint8_t k) const
    {
        if (n < k)  return 0;
        if (n == k) return 1;
        return factorial[n] / (factorial[k] * factorial[n - k]);
    }

    // combinations are always assumed to be in a descending order
    uint32_t rank(const std::array<uint8_t, K>& comb) const
    {
        /* 
         * Calculate rank of combination using binomial number system.
         * We can use this number system since: 0 <= comb[0] < comb[1] < comb[2] < ... < comb[K - 1]
         */
        uint32_t rank = 0;

        for (uint8_t k = K; k >= 1; --k)
            rank += nCk(comb[k - 1], k);

        return rank;
    }
};

// ranks permutations from 0 to N! - 1
template<uint8_t N>
struct PermRanker {
    uint32_t rank(const std::array<uint8_t, N>& perm) const
    {
        // calculates lehmer code
        std::array<uint8_t, N> lehmer = perm;
        for (uint8_t i = 1; i < N; ++i) {
            int j = i;
            while (j--) {
                if (perm[j] < perm[i])
                    --lehmer[i];
            }
        }

        uint32_t rank = 0;
        // get rank by lehmer code
        for (uint8_t i = 0, j = N - 1; i < N && j >= 0; ++i, --j)
            rank += lehmer[i] * factorial[j];

        return rank;
    }
};

// ranks partial permutations from 0 to nPk - 1
template<uint8_t N, uint8_t K>
struct PermRankerPartial {
    // calculate nPk = n! / (n - k)!
    uint32_t nPk(uint8_t n, uint8_t k) const
    {
        if (n < k)  return 0;
        if (n == k) return 1;
        return factorial[n] / factorial[n - k];
    }

    uint32_t rank(const std::array<uint8_t, K>& perm) const
    {
        // calculates lehmer code
        std::array<uint8_t, K> lehmer = perm;

        for (uint8_t i = 1; i < K; ++i) {
            int j = i;
            while (j--)
            {
                if (perm[j] < perm[i])
                    --lehmer[i];
            }
        }

        uint32_t rank = 0;

        for (uint8_t i = 0; i < K; ++i)
            rank += lehmer[i] * nPk(N - 1 - i, K - 1 - i);

        return rank;
    }
};