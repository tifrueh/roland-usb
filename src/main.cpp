// roland-usb: Manage the renaming of audio files for the Roland FP-30 Digital Piano
// Copyright (C) 2022  Timo Früh

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#define VERSION "1.0.1"

#include <filesystem>
#include <string>
#include <CLI/CLI.hpp>
#include "subcommands.hpp"

int main(int argc, char** argv) {

    CLI::App app = CLI::App("Manage the renaming of audio files for the Roland FP-30 Digital Piano", "roland-usb");

    app.set_version_flag("-v,--version", VERSION, "Print version and exit");

    CLI::App* scmdInit = app.add_subcommand("init", "Initialise target directory");
    CLI::App* scmdEncrypt = app.add_subcommand("encrypt", "Rename .wav files in target directory to FP-30 readable names");
    CLI::App* scmdDecrypt = app.add_subcommand("decrypt", "Rename .wav files in target directory to human readable names");
    app.require_subcommand(1, 1);

    std::string sTargetDirectory;
    app.add_option("directory", sTargetDirectory, "Target directory")->required();

    CLI11_PARSE(app, argc, argv);

    std::filesystem::path targetDirectory = sTargetDirectory;

    if (*scmdInit) {
        scmd::init(targetDirectory);
    }
    else if (*scmdEncrypt) {
        scmd::encrypt(targetDirectory);
    }
    else if (*scmdDecrypt) {
        scmd::decrypt(targetDirectory);
    }
    else {
        throw std::logic_error("no valid subcommand given");
    }

    return 0;
}
