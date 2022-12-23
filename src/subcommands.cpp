// Copyright (C) 2022  Timo Früh
// Full copyright notice in main.cpp


#include <filesystem>
#include <iostream>
#include <vector>
#include "subcommands.hpp"
#include "nameconversion.hpp"
#include "usb.hpp"

void scmd::init(const std::filesystem::path& directory) {
    
    try
    {
        std::cout << "Initialising directory ..." << std::endl;
        rusb::initRolandUSB(directory);
        std::cout << "Directory " << directory.string() << " initialised" << std::endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
    }
}

void scmd::encrypt(const std::filesystem::path& directory) {
    
    std::filesystem::path titlesCONF = directory / "titles.conf";

    if (!std::filesystem::is_directory(directory)) {
        std::cerr << "[ERROR]: " << directory.string() << " does not exist or is no directory"<< std::endl;
    }
    else if (!std::filesystem::is_regular_file(titlesCONF)) {
        std::cerr << "[ERROR]: " << directory.string() << " is not initialised";
    }

    std::vector<std::string> titles = rusb::parseTitlesCSV(titlesCONF);
    std::vector<std::string> rolandNames = rnc::createRolandNameVector(1, titles.size());

    rnc::bulkRename(directory, titles, rolandNames);
}

void scmd::decrypt(const std::filesystem::path& directory) {
    return;
}
