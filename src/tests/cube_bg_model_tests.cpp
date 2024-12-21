#include <gtest/gtest.h>

#include "../algorithm/cube_bg_model.h"

#include <array>

using ecolor = Cube_bg_model::ecolor;
using emove  = Cube_bg_model::emove;

class CubeTest : public testing::Test {
protected:
    void SetUp() override
    {
        cube = new Cube_bg_model(); 
    }

    void TearDown() override
    {
        delete cube;
    }

    Cube_bg_model *cube;
};

bool compare_arrays(ecolor* arr1, ecolor* arr2, std::size_t arr_size)
{
    for (std::size_t i = 0; i < arr_size; ++i) {
        if (arr1[i] != arr2[i])
            return false;
    }

    return true;
}

// the test verifies that the array of colors has retained its invariant
// TEST_F(CubeTest, shuffle)
// {
//     // use the first half of counting sort to check counts of colors
//     // returns true if there are COLOR_CELLS_PER_SIDE pieces of each color
//     auto counts_check = [](std::array<ecolour, TOTAL_COLOR_CELLS> arr)
//     {
//         const std::size_t total_colors_count = 6;

//         // create array with zeroes of size total_colors_count
//         std::size_t counts[total_colors_count] = {};

//         // fill counts array
//         for (std::size_t i = 0; i < arr.size(); ++i)
//             ++counts[arr[i]];

//         // check recieved counts
//         for (std::size_t i = 0; i < total_colors_count; ++i) {
//             if (counts[i] != COLORS_PER_SIDE)
//                 return false;
//         }

//         return true;
//     };
    
//     cube->shuffle();

//     uint8_t *cube_data = cube->get_cube_data();
//     EXPECT_TRUE(counts_check(cube_data, TOTAL_COLOR_CELLS));

//     delete cube_data;
// }

TEST_F(CubeTest, rotate)
{
    /*
     * we need to rotate elements on surface and adjacent cells
     * so lets check this
     *
     *   0 0 0          0 0 0 
     *  -------        -------
     * 1|2 2 2|3      2|3 3 3|4
     * 1|2 2 2|3  --> 1|2 2 2|3
     * 1|2 2 2|3      1|2 2 2|3
     *  -------        -------
     *   5 5 5          5 5 5
     */

    cube->rotate(emove::U);
    
    std::array<ecolor, COLORS_PER_SIDE> side_front_data_rot_90 = cube->get_side(ecolor::F);
    std::array<ecolor, COLORS_PER_SIDE> correct_side_front_data_rot_90 = {
        ecolor::R,
        ecolor::R,
        ecolor::R,
        ecolor::F,
        ecolor::F,
        ecolor::F,
        ecolor::F,
        ecolor::F,
        ecolor::F
    };
    
    // check only surface of edge
    EXPECT_TRUE(compare_arrays(side_front_data_rot_90.data(),
                               correct_side_front_data_rot_90.data(),
                               COLORS_PER_SIDE));

    // check adjecent cells
    std::array<ecolor, TOTAL_COLOR_CELLS> cube_data = cube->get_data();
    EXPECT_TRUE(cube_data[17] == ecolor::L && cube_data[14] == ecolor::L && cube_data[11] == ecolor::F &&
                cube_data[ 6] == ecolor::U && cube_data[ 7] == ecolor::U && cube_data[ 8] == ecolor::U &&
                cube_data[27] == ecolor::B && cube_data[30] == ecolor::R && cube_data[33] == ecolor::R &&
                cube_data[47] == ecolor::D && cube_data[46] == ecolor::D && cube_data[45] == ecolor::D);
}

TEST_F(CubeTest, get_side_data)
{
    std::array<ecolor, COLORS_PER_SIDE> side_up_data    = cube->get_side(ecolor::U);
    std::array<ecolor, COLORS_PER_SIDE> side_left_data  = cube->get_side(ecolor::L);
    std::array<ecolor, COLORS_PER_SIDE> side_front_data = cube->get_side(ecolor::F);
    std::array<ecolor, COLORS_PER_SIDE> side_right_data = cube->get_side(ecolor::R);
    std::array<ecolor, COLORS_PER_SIDE> side_back_data  = cube->get_side(ecolor::B);
    std::array<ecolor, COLORS_PER_SIDE> side_down_data  = cube->get_side(ecolor::D);

    std::array<ecolor, COLORS_PER_SIDE> side_up_correct_data;
    for (std::size_t i = 0; i < COLORS_PER_SIDE; ++i) side_up_correct_data[i] = ecolor::U;
    std::array<ecolor, COLORS_PER_SIDE> side_left_correct_data;
    for (std::size_t i = 0; i < COLORS_PER_SIDE; ++i) side_left_correct_data[i] = ecolor::L;
    std::array<ecolor, COLORS_PER_SIDE> side_front_correct_data;
    for (std::size_t i = 0; i < COLORS_PER_SIDE; ++i) side_front_correct_data[i] = ecolor::F;
    std::array<ecolor, COLORS_PER_SIDE> side_right_correct_data;
    for (std::size_t i = 0; i < COLORS_PER_SIDE; ++i) side_right_correct_data[i] = ecolor::R;
    std::array<ecolor, COLORS_PER_SIDE> side_back_correct_data;
    for (std::size_t i = 0; i < COLORS_PER_SIDE; ++i) side_back_correct_data[i] = ecolor::B;
    std::array<ecolor, COLORS_PER_SIDE> side_down_correct_data;
    for (std::size_t i = 0; i < COLORS_PER_SIDE; ++i) side_down_correct_data[i] = ecolor::D;
    
    EXPECT_TRUE(compare_arrays(side_up_data.data(), side_up_correct_data.data(), COLORS_PER_SIDE));
    EXPECT_TRUE(compare_arrays(side_left_data.data(), side_left_correct_data.data(), COLORS_PER_SIDE));
    EXPECT_TRUE(compare_arrays(side_front_data.data(), side_front_correct_data.data(), COLORS_PER_SIDE));
    EXPECT_TRUE(compare_arrays(side_right_data.data(), side_right_correct_data.data(), COLORS_PER_SIDE));
    EXPECT_TRUE(compare_arrays(side_back_data.data(), side_back_correct_data.data(), COLORS_PER_SIDE));
    EXPECT_TRUE(compare_arrays(side_down_data.data(), side_down_correct_data.data(), COLORS_PER_SIDE));
}

