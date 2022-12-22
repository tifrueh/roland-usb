// Copyright (C) 2022  Timo Früh
// Full copyright notice in main.cpp


#include <vector>
#include <string>
#include <fstream>
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

    const std::string sIndex = std::to_string(index);
    const std::string insertionCharacter = "%";
    const std::string nameTemplates[3] = { "R068_%.wav", "R068_0%.wav" , "R068_00%.wav" };

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

    insertionPos = name.find(insertionCharacter);

    name.replace(insertionPos, 1, sIndex);

    return name;
}

std::vector<std::string> rnc::createRolandNameVector(const int& start, const int& end) {
    
    std::vector<std::string> nameVector;

    for (int i = start; i <= end; i++) {
        nameVector.push_back(rnc::createRolandName(i));
    }

    return nameVector;
}
