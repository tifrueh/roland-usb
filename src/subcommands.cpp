// Copyright (C) 2022  Timo Früh
// Full copyright notice in main.cpp


#include <filesystem>
#include <iostream>
#include <vector>
#include "subcommands.hpp"
#include "nameconversion.hpp"
#include "usb.hpp"

void scmd::init(const std::filesystem::path& directory) {

    int rolandState = rusb::getRolandState(directory);

    switch (rolandState) {

    case 0:
        std::cout << "Initialising directory ..." << std::endl;
        rusb::initRolandUSB(directory);
        std::cout << "Directory " << directory.string() << " initialised" << std::endl;
        break;

    case 1:
        std::cout << "Reinitialising directory ..." << std::endl;
        rusb::initRolandUSB(directory);
        std::cout << "Directory " << directory.string() << " initialised" << std::endl;
        break;
    
    case 2:
        std::cerr << "[ERROR]: " << directory.string() << " is encrypted, initialisation not possible" << std::endl;
        break;

    case 3:
        std::cerr << "[ERROR]: " << directory.string() << " is broken (titles.conf and .titles.conf present)" << std::endl;
        break;
    
    case 9:
        std::cerr << "[ERROR]: " << directory.string() << " is no directory, initialisation not possible" << std::endl;
        break;
    }
}

void scmd::encrypt(const std::filesystem::path& directory) {

    std::filesystem::path titlesCONF = directory / "titles.conf";
    std::filesystem::path hiddenTitlesCONF = directory / ".titles.conf";
    std::vector<std::string> titles;
    std::vector<std::string> rolandNames;

    int rolandState = rusb::getRolandState(directory);

    switch (rolandState) {

    case 0:
        std::cerr << "[ERROR]: " << directory.string() << " is not initialised, encryption not possible" << std::endl;
        break;

    case 1:
        titles = rusb::parseTitlesCONF(titlesCONF);
        rolandNames = rnc::createRolandNameVector(1, titles.size());
        rnc::bulkRename(directory, titles, rolandNames);
        std::filesystem::rename(titlesCONF, hiddenTitlesCONF);
        break;
    
    case 2:
        std::cerr << "[ERROR]: " << directory.string() << " is already encrypted" << std::endl;
        break;
    
    case 3:
        std::cerr << "[ERROR]: " << directory.string() << " is broken (titles.conf and .titles.conf present)" << std::endl;
        break;
    
    case 9:
        std::cerr << "[ERROR]: " << directory.string() << " is no directory, encryption not possible" << std::endl;
    }
}

void scmd::decrypt(const std::filesystem::path& directory) {

    std::filesystem::path hiddenTitlesCONF = directory / ".titles.conf";
    std::filesystem::path titlesCONF = directory / "titles.conf";
    std::vector<std::string> titles;
    std::vector<std::string> rolandNames;

    int rolandState = rusb::getRolandState(directory);

    switch (rolandState) {

    case 0:
        std::cerr << "[ERROR]: " << directory.string() << " is not initialised, decryption not possible" << std::endl;
        break;

    case 1:
        std::cerr << "[ERROR]: " << directory.string() << " is already decrypted" << std::endl;
        break;
    
    case 2:
        titles = rusb::parseTitlesCONF(hiddenTitlesCONF);
        rolandNames = rnc::createRolandNameVector(1, titles.size());
        rnc::bulkRename(directory, rolandNames, titles);
        std::filesystem::rename(hiddenTitlesCONF, titlesCONF);

    case 3:
        std::cerr << "[ERROR]: " << directory.string() << " is broken (titles.conf and .titles.conf present)" << std::endl;
        break;

    case 9:
        std::cerr << "[ERROR]: " << directory.string() << " is no directory, decryption not possible" << std::endl;
    }
}
