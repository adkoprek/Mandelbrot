//  __  __                 _      _ _               _   
// |  \/  |               | |    | | |             | |  
// | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
// | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
// | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
// |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
//        https://github.com/adkoprek/Mandelbrot
//
// This class loades the configuration from a .cfg file.
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#pragma once
#include <fstream>
#include <string>

#include "config.h"


class ConfigParser {
public:
    /************************************************************
    *                       functions
    ************************************************************/

    // Constructor
    // @param pointer to the configuration struct where to write the data
    ConfigParser(Config* config);

    // Deconstructor
    ~ConfigParser();

    // Open the config file
    // @param file path
    // @return error code, successful if 0
    int open(std::string file);

    // Parse the configuration
    // @return error code, successful if 0
    int parse();

private:
    /************************************************************
    *                       members
    ************************************************************/

    std::ifstream* m_file;      // Pointer the the opened file
    Config* m_config;           // Function where to the destination struct
};
