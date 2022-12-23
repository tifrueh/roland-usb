// Copyright (C) 2022  Timo Früh
// Full copyright notice in src/main.cpp


#include <vector>
#include <string>
#include <filesystem>

namespace rusb {
    
    // returns a vector containing all the lines of a titles.conf file
    std::vector<std::string> parseTitlesCONF(const std::filesystem::path& titlesCSVPath);

    // initialise folder with a titles.conf file
    void initRolandUSB(const std::filesystem::path& directory);

    /* 
    get the state of a folder
    0: not initialised
    1: decrypted
    2: encrypted
    3: broken (titles.conf and .titles.conf present)
    9: no directory
    */
   int getRolandState(const std::filesystem::path& directory);
}
