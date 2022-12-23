// Copyright (C) 2022  Timo Früh
// Full copyright notice in main.cpp


#include <filesystem>
#include <iostream>
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
    return;
}

void scmd::decrypt(const std::filesystem::path& directory) {
    return;
}
