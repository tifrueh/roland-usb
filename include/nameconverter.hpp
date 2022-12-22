// Copyright (C) 2022  Timo Früh
// Full copyright notice in src/main.cpp


#include <vector>
#include <string>

// namespace: roland nameconverter
namespace rnc {

    // returns a vector containing all the lines of a titles.csv file
    std::vector<std::string> parseTitlesCSV(const std::filesystem::path& titlesCSVPath);

    // returns a name based on a number which the FP-30 can understand
    std::string createRolandName(const int& index);

    // returns a vector containing Roland names spanning a given range
    std::vector<std::string> createRolandNameVector(const int& start, const int& end);
}
