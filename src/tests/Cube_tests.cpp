#include <gtest/gtest.h>

#include "../include/Cube.h"

class CubeTest : public testing::Test {
protected:
    void SetUp() override
    {
        cube = new Cube(); 
    }

    void TearDown() override
    {
        delete cube;
    }

    Cube *cube;
};

bool compare_arrays(uint8_t *arr1, uint8_t *arr2, std::size_t arr_len)
{
    for (std::size_t i = 0; i < arr_len; ++i) {
        if (arr1[i] != arr2[i])
            return false;
    }

    return true;
}

// the test verifies that the array of colors has retained its invariant
TEST_F(CubeTest, shuffle)
{
    // use the first half of counting sort to check counts of colors
    // returns true if there are COLOR_CELLS_PER_SIDE pieces of each color
    auto counts_check = [](uint8_t *arr, std::size_t arr_len)
    {
        const std::size_t total_colors_count = 6;

        // create array with zeroes of size total_colors_count
        std::size_t counts[total_colors_count] = {};

        // fill counts array
        for (std::size_t i = 0; i < arr_len; ++i)
            ++counts[arr[i]];

        // check recieved counts
        for (std::size_t i = 0; i < total_colors_count; ++i) {
            if (counts[i] != COLOR_CELLS_PER_SIDE)
                return false;
        }

        return true;
    };
    
    cube->shuffle();

    uint8_t *cube_data = cube->get_cube_data();
    EXPECT_TRUE(counts_check(cube_data, TOTAL_COLOR_CELLS));

    delete cube_data;
}

TEST_F(CubeTest, rotate)
{
    /*
     * we need to rotate elements on surface and adjacent cells
     * so lets check this
     *
     *     6  7  8            17 14 11 
     *   ----------          ----------
     * 11|18 19 20|27      45|24 21 18| 6
     * 14|21 22 23|30  --> 46|25 22 19| 7
     * 17|24 25 26|33      47|26 23 20| 8
     *   ----------          ----------
     *    45 46 47            33 30 27
     */

    uint8_t *side_front_data         = cube->get_side_data(CubeSide::SIDE_FRONT);
    uint8_t side_front_data_rot_90[] = {24, 21, 18, 25, 22, 19, 26, 23, 20};

    // check only surface of edge
    cube->rotate(CubeSide::SIDE_FRONT, Rotation::ROTATION_90);
    EXPECT_TRUE(compare_arrays(side_front_data, side_front_data_rot_90, COLOR_CELLS_PER_SIDE));

    // check adjecent cells
    uint8_t *cube_data = cube->get_cube_data();
    EXPECT_TRUE(cube_data[17] == 47 && cube_data[14] == 46 && cube_data[11] == 45 &&
                cube_data[ 6] == 17 && cube_data[ 7] == 14 && cube_data[ 8] == 11 &&
                cube_data[27] ==  6 && cube_data[30] ==  7 && cube_data[33] ==  8 &&
                cube_data[47] == 27 && cube_data[46] == 30 && cube_data[45] == 33);

    delete[] side_front_data;
}

TEST_F(CubeTest, get_side_data)
{
    uint8_t *side_up_data    = cube->get_side_data(CubeSide::SIDE_UP);
    // uint8_t *side_left_data  = cube->get_side_data(CubeSide::SIDE_LEFT);
    // uint8_t *side_front_data = cube->get_side_data(CubeSide::SIDE_FRONT);
    // uint8_t *side_right_data = cube->get_side_data(CubeSide::SIDE_RIGHT);
    // uint8_t *side_back_data  = cube->get_side_data(CubeSide::SIDE_BACK);
    uint8_t *side_down_data  = cube->get_side_data(CubeSide::SIDE_DOWN);

    uint8_t side_up_correct_data[]    = { 0,  1,  2,  3,  4,  5,  6,  7,  8};
    // uint8_t side_left_correct_data[]  = { 9, 10, 11, 12, 13, 14, 15, 16, 17};
    // uint8_t side_front_correct_data[] = {18, 19, 20, 21, 22, 23, 24, 25, 26};
    // uint8_t side_right_correct_data[] = {27, 28, 29, 30, 31, 32, 33, 34, 35};
    // uint8_t side_back_correct_data[]  = {36, 37, 38, 39, 40, 41, 42, 43, 44};
    uint8_t side_down_correct_data[]  = {45, 46, 47, 48, 49, 50, 51, 52, 53};
    
    EXPECT_TRUE(compare_arrays(side_up_data, side_up_correct_data, COLOR_CELLS_PER_SIDE));
    // EXPECT_TRUE(compare_arrays(side_left_data, side_left_correct_data, COLOR_CELLS_PER_SIDE));
    // EXPECT_TRUE(compare_arrays(side_front_data, side_front_correct_data, COLOR_CELLS_PER_SIDE));
    // EXPECT_TRUE(compare_arrays(side_right_data, side_right_correct_data, COLOR_CELLS_PER_SIDE));
    // EXPECT_TRUE(compare_arrays(side_back_data, side_back_correct_data, COLOR_CELLS_PER_SIDE));
    EXPECT_TRUE(compare_arrays(side_down_data, side_down_correct_data, COLOR_CELLS_PER_SIDE));

    delete[] side_up_data;
    // delete[] side_left_data;
    // delete[] side_front_data;
    // delete[] side_right_data;
    // delete[] side_back_data;
    delete[] side_down_data;
}

