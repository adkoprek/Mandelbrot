//  __  __                 _      _ _               _   
// |  \/  |               | |    | | |             | |  
// | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
// | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
// | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
// |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
//        https://github.com/adkoprek/Mandelbrot
//
// This class loades the configuration from a .cfg file
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>

#include "config_parser.h"


// Helper functions
namespace  {
    bool is_number(const std::string& s) {
        return !s.empty() && std::find_if(s.begin(), s.end(), 
            [](unsigned char c) { 
                return !std::isdigit(c) && c != '.' && c != '-'; 
            }) == s.end();
    }
}

/************************************************************
*                       functions
************************************************************/

// Constructor
ConfigParser::ConfigParser(Config* config) {
    m_config = config;
}

// Deconstructor
ConfigParser::~ConfigParser() {
    m_file->close();
    delete m_file;
}

// Open the config file
int ConfigParser::open(std::string file_name) {
    if (!std::filesystem::path(file_name).is_absolute()) {
        std::string executable_dir = std::filesystem::current_path();
        file_name = std::filesystem::canonical(executable_dir + "/" + file_name).string();
    }

    m_file = new std::ifstream();
    m_file->open(file_name, std::ios::in);
    if (!m_file->is_open()) {
        std::cerr << "The configuration file couldn't be opened" << std::endl;
        return -1;
    }

    return 0;
}

// Parse the configuration
int ConfigParser::parse() {
    std::string line;
    while (std::getline(*m_file, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end()); 
        if(line.empty() || line[0] == '#') continue;
        auto delimiter_pos = line.find("=");
        auto key = line.substr(0, delimiter_pos);
        auto value = line.substr(delimiter_pos + 1);
        if (key.empty() || value.empty()) {
            std::cerr << "The key-value group: " << key << "-" << value;
            std::cerr << "Is not completer" << std::endl;
            return -1;
        }

        if (key != "img_path") {
            if (!is_number(value)) {
                std::cerr << "The value for " << key << ", isn't numerical" << std::endl; 
                return -1;
            }
        }

        if (key == "width")
            m_config->width = std::stoi(value);
        else if (key == "height")
            m_config->height = std::stoi(value);
        else if (key == "iter_start")
            m_config->iter_start = std::stoi(value);
        else if (key == "iter_num")
            m_config->iter_num = std::stoi(value);
        else if (key == "x")
            m_config->x = std::stod(value);
        else if (key == "y")
            m_config->y = std::stod(value);
        else if (key == "step")
            m_config->step = std::stod(value);
        else if (key == "img_path") {
            if (!std::filesystem::path(value).is_absolute()) {
                std::cerr << "The directory: " << value << " is not absolute" << std::endl;
                return -1;
            }
            int result = access(value.c_str(), W_OK);
            if (result) {
                std::cerr << "The directory: " << value << " is not writable" << std::endl;
                return -1;
            }
            m_config->img_path = value;
        }
    }

    return 0;
}
