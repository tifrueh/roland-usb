// Copyright (C) 2022  Timo Früh
// Full copyright notice in main.cpp


#include <vector>
#include <string>
#include <fstream>
#include "nameconverter.hpp"

std::vector<std::string> rnc::parseTitlesCSV(const std::string& titlesCsvPath) {
    
    std::string line;

    std::ifstream ifile;
    ifile.open(titlesCsvPath);

    std::vector<std::string> titlesVector;

    while (std::getline(ifile, line)) {
            titlesVector.push_back(line);
    }

    return titlesVector;
}