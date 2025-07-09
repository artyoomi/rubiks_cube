#pragma once

#include <iostream>
#include <istream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>

#include "../../cube_bg_model.h"
#include "../phase_info/phase_info.h"

/*
 * Base class for each database
 */
class Database {
// PUBLIC FUNCTIONS
public:
    using epiece = Cube_bg_model::epiece;
    using emove  = Cube_bg_model::emove;

    Database(std::size_t capacity, const std::string& fname)
        : _size{0},
          _capacity{capacity},
          _fname{fname},
          _cache_dir_path{"./cache"}
    {
        _data.resize(capacity);
        reset();
    }

    // load db from file
    bool load();

    // save db in file
    void save() const;

    // sets all values to 0xFF and reset current size
    void reset();

    // get depth by index
    uint8_t operator[](uint32_t index) const;
    
    // get depth by cube id
    uint8_t operator[](const Cube_bg_model& cube) const;

    // updates value on given index
    bool set(uint32_t index, uint8_t value);
    bool set(const Cube_bg_model& cube, uint8_t value);

    // returns true if the distance is lower than 0xFF
    bool is_set(uint32_t index) const;
    bool is_set(const Cube_bg_model& cube) const;

    // returns true if all indices are set
    bool full() const;

    // return current size of db
    size_t size() const;
    
    // return capacity or max_size of db
    size_t capacity() const;

// PUBLIC VARIABLES
public:    
    /*
     * Pointer to struct which contains:
     * - function to find id on current phase
     * - current phase allowed moves
     * - is solved function (just curr_phase_id == 0)
     */
    std::shared_ptr<Phase_info> phase_info;

// PRIVATE FUNCTIONS
private:
    std::vector<uint8_t> _data;         // vector with db data
    std::size_t          _size;         // current size of db
    const std::size_t    _capacity;     // max_size of db
    
    const std::string _fname;           // name of db file
    const std::string _cache_dir_path;  // name of cache dir
};
