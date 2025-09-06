#include "database.h"

bool Database::load()
{
    // Add '/' between cache folder and phase_db name if not added
    std::ifstream ifs(
        (_cache_dir_path.back() == '/') ? (_cache_dir_path + _fname)
                                        : (_cache_dir_path + '/' + _fname)
    );

    if (ifs) {
        std::size_t tmp;
        for (size_t i = 0; i < _capacity; ++i) {
            ifs >> tmp;
            _data[i] = (uint8_t)tmp;

            if (_data[i] == 0xFF) {
                std::cout << "Database doesn't match " << _fname << ". Failed to load." << std::endl;
                reset();
                return false;
            }
            ++_size;
        }
    } else {
        std::cout << "Failed to open database file \"" << _fname << "\"." << std::endl;
        return false;
    }

    ifs.close();
    return this->full();
}

void Database::save() const
{
    // Check the existence of the directory and create it if necessary
    if (!std::filesystem::exists(std::filesystem::path(this->_cache_dir_path)))
        std::filesystem::create_directory(std::filesystem::path(this->_cache_dir_path));

    // File with same name as _cache_dir_path was already exists and it it not a directory
    if (!std::filesystem::is_directory(this->_cache_dir_path))
        throw std::runtime_error("Error: Cannot use non-directory file to store phases cache!");
    
    // open file
    std::ofstream ofs(std::filesystem::path(_cache_dir_path) / std::filesystem::path(_fname));

    // check if file is open
    if (!ofs.is_open())
        throw std::runtime_error("Database::save: Can't open file for write!");

    // write database data to file
    for (std::size_t i = 0; i < _capacity; ++i)
        ofs << (std::size_t)_data[i] << std::endl;
    
    ofs.close();
}

bool Database::set(uint32_t index, uint8_t value)
{
    if (_data[index] > value) {
        if (_data[index] == 0xFF)
            ++_size;

        _data[index] = value;
        return true;
    }

    return false;
}

bool Database::set(const Cube_bg_model& cube, uint8_t value)
    {return set(phase_info->id(cube), value);}

bool Database::is_set(uint32_t index) const
    {return (_data[index] != 0xFF);}

bool Database::is_set(const Cube_bg_model& cube) const
    {return is_set(phase_info->id(cube));}

bool Database::full() const
    {return (_size == _capacity);}

std::size_t Database::size() const
    {return _size;}

void Database::reset()
{
    // fills the data with 0xFF (= unset)
    std::fill(_data.begin(), _data.end(), 0xFF);
    _size = 0;
}

std::size_t Database::capacity() const
    {return _capacity;}

uint8_t Database::operator [](uint32_t index) const
    {return _data[index];}

uint8_t Database::operator [](const Cube_bg_model& cube) const
    {return _data[phase_info->id(cube)];}
