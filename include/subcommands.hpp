// Copyright (C) 2022  Timo Früh
// Full copyright notice in src/main.cpp


#include <filesystem>

namespace scmd {

    // initialise folder with a titles.conf file
    void init(const std::filesystem::path& directory);

    // encrypt files; rename them to FP-30 readable names
    void encrypt(const std::filesystem::path& directory);

    // decrypt files; rename them to human readable names
    void decrypt(const std::filesystem::path& directory);
}
