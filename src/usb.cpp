// Copyright (C) 2022  Timo Früh
// Full copyright notice in main.cpp


#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "usb.hpp"

std::vector<std::string> rusb::parseTitlesCONF(const std::filesystem::path& titlesCSVPath) {
    
    std::string line;

    std::ifstream ifile;
    ifile.open(titlesCSVPath);

    std::vector<std::string> titlesVector;

    while (std::getline(ifile, line)) {
        if (line != "") {
            titlesVector.push_back(line);
        }
    }

    ifile.close();

    return titlesVector;
}

void rusb::initRolandUSB(const std::filesystem::path& directory) {

    if (!std::filesystem::is_directory(directory)) {
        throw std::invalid_argument(directory.string() + " does not exist or is no directory");
    }

    std::filesystem::path titlesCONF = directory / "titles.conf";

    std::ofstream ofile;
    ofile.open(titlesCONF, std::ios::trunc);

    for (std::filesystem::path file : std::filesystem::directory_iterator(directory)) {

        std::string filename = file.filename();
        std::string ext = ".wav";

        if (filename.find(ext) != std::string::npos) {
            ofile << filename << std::endl;
        }
    }

    ofile.close();
}
