// Copyright (C) 2022  Timo Früh
// Full copyright notice in src/main.cpp


#include <vector>
#include <string>
#include <filesystem>

namespace rusb {
    
    // returns a vector containing all the lines of a titles.csv file
    std::vector<std::string> parseTitlesCSV(const std::filesystem::path& titlesCSVPath);

    // initialise folder with a titles.conf file
    void initRolandUSB(const std::filesystem::path& directory);
}
