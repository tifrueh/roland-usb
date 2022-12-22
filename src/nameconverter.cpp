// Copyright (C) 2022  Timo Früh
// Full copyright notice in main.cpp


#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "nameconverter.hpp"

std::vector<std::string> rnc::parseTitlesCSV(const std::string& titlesCSVPath) {
    
    std::string line;

    std::ifstream ifile;
    ifile.open(titlesCSVPath);

    std::vector<std::string> titlesVector;

    while (std::getline(ifile, line)) {
            titlesVector.push_back(line);
    }

    ifile.close();

    return titlesVector;
}

std::string rnc::createRolandName(const int& index) {
    
    int insertionPos;
    std::string name;
    std::string sIndex;
    std::string insertionCharacter;
    
    std::string nameTemplates[3] = { "R068_%.wav", "R068_0%.wav" , "R068_00%.wav" };

    if (index > 99) {
        name = nameTemplates[0];
    }
    else if (index > 9) {
        name = nameTemplates[1];
    }
    else if (index > 0) {
        name = nameTemplates[2];
    } 
    else {
        throw std::invalid_argument("Roland name index must be between 1 and 999");
    } 

    insertionCharacter = "%";
    sIndex = std::to_string(index);

    insertionPos = name.find(insertionCharacter);

    name.replace(insertionPos, 1, sIndex);

    return name;
}
