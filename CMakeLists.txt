cmake_minimum_required(VERSION 3.12.0)
project(rubik VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# for Debug
set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
else()
    message(STATUS "Building in Release mode")
endif()

# to autofetch glfw
include(FetchContent)

# Check if GLFW is already installed
find_package(glfw3 QUIET)

if ((NOT glfw3_FOUND) AND MINGW)
    message(WARNING "GLFW not found. Fetching and building GLFW locally. Its better to install GLFW system-wide first.")
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )
    FetchContent_MakeAvailable(glfw)
else()
    message(STATUS "GLFW found.")
endif()

find_package(OpenGL REQUIRED)

# include_directories(src src/algorithm)

# Find all model subdirectory sources
file(GLOB_RECURSE MODEL_SOURCES
    "${PROJECT_SOURCE_DIR}/src/model/*.cpp"
)

# Find all view subdirectory sources
file(GLOB_RECURSE VIEW_SOURCES
    "${PROJECT_SOURCE_DIR}/src/view/*.cpp"
)

# Find all controller subdirectory sources
file(GLOB_RECURSE CONTROLLER_SOURCES
    "${PROJECT_SOURCE_DIR}/src/controller/*.cpp"
)

# Find all Thistlethwaite algo sources
file(GLOB_RECURSE THISTLETHWAITE_SOURCES
    "${PROJECT_SOURCE_DIR}/src/algorithm/thistlethwaite/*.cpp"
)

add_executable(Rubiks_cube
    src/main.cpp 
    src/glad.c
    ${MODEL_SOURCES}
    ${VIEW_SOURCES}
    ${CONTROLLER_SOURCES}
    src/stb_image.cpp
    src/algorithm/cube_bg_model.cpp
    
    # Human algo
    src/algorithm/human_algorithm/human_algo.cpp

    ${THISTLETHWAITE_SOURCES}
)

target_link_libraries(Rubiks_cube
    glfw
    OpenGL::GL 
)

enable_testing()

add_executable(Cube_bg_model_test src/tests/cube_bg_model_tests.cpp src/algorithm/cube_bg_model.cpp)
target_link_libraries(Cube_bg_model_test gtest_main gtest)

include(GoogleTest)
gtest_discover_tests(Cube_bg_model_test)