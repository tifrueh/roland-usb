// Copyright (C) 2022  Timo Früh
// Full copyright notice in src/main.cpp


#include <vector>
#include <string>

// namespace: roland nameconverter
namespace rnc {

    // returns a vector containing all the lines of a titles.csv file
    std::vector<std::string> parseTitlesCSV(const std::string& titlesCSVPath);
}