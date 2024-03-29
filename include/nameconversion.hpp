// Copyright (C) 2022  Timo Früh
// Full copyright notice in src/main.cpp


#include <vector>
#include <string>
#include <filesystem>

// namespace: roland nameconversion
namespace rnc {

    // returns a name based on a number which the FP-30 can understand
    std::string createRolandName(const int& index);

    // returns a vector containing Roland names spanning a given range
    std::vector<std::string> createRolandNameVector(const int& start, const int& end);

    // rename multiple files based on two vectors
    void bulkRename(const std::filesystem::path& directory, 
                    const std::vector<std::string>& from, 
                    const std::vector<std::string>& to);
}
