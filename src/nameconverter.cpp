// Copyright (C) 2022  Timo Früh
// Full copyright notice in main.cpp


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "nameconverter.hpp"

std::vector<std::string> rnc::parseTitlesCSV(const std::filesystem::path& titlesCSVPath) {
    
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

void rnc::bulkRename(const std::filesystem::path& directory, const std::vector<std::string>& from, const std::vector<std::string>& to) {

    if (!std::filesystem::is_directory(directory)) {
        throw std::invalid_argument(directory.string() + " is not a directory");
    }
    if (from.size() != to.size()) {
        throw std::invalid_argument("both vectors 'from' and 'to' have to be of the same size");
    }

    std::filesystem::path fromPath;
    std::filesystem::path toPath;

    for (int i = 0; i < from.size(); i++) {

        fromPath = directory / from.at(i);

        if (!std::filesystem::is_regular_file(fromPath)) {
            std::cout << fromPath.string() << " not found, skipping ..." << std::endl;
            break;
        }

        toPath = directory / to.at(i);

        std::filesystem::rename(fromPath, toPath);
    }
}

void rnc::initRolandUSB(const std::filesystem::path& directory) {

    if (!std::filesystem::is_directory(directory)) {
        throw std::invalid_argument(directory.string() + " is not a directory");
    }

    std::filesystem::path titlesCONF = directory / "titles.conf";

    if (std::filesystem::is_regular_file(titlesCONF)) {
        throw std::invalid_argument(titlesCONF.string() + " exists already");
    }
    
    std::ofstream ofile;
    ofile.open(titlesCONF);

    for (std::filesystem::path file : std::filesystem::directory_iterator(directory)) {

        std::string filename = file.filename();
        std::string ext = ".wav";

        if (filename.find(ext) != std::string::npos) {
            ofile << filename << std::endl;
        }
    }

    ofile.close();
}
