//  __  __                 _      _ _               _   
// |  \/  |               | |    | | |             | |  
// | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
// | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
// | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
// |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
//        https://github.com/adkoprek/Mandelbrot
//
// This file contains the main entry point for the 
// mandelbrot zoom video frame calculator
//
// The app needs to be passed a configuration file. Use
// the template mandelbrot-video.cfg
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#include <iostream>
#include <string>
#include <unistd.h>

#include "config.h"
#include "config_parser.h"
#include "zoomer.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Run the programm with <Programm Command> <.cfg file>" << std::endl;
        return  0;
    }

    std::string file_name(argv[1]);
    Config* config = new Config();
    auto config_parser = new ConfigParser(config);
    if (config_parser->open(file_name)) return -1;
    if (config_parser->parse()) return -1;
    delete config_parser;

    auto zoomer = new Zoomer(config);
    zoomer->run();
    delete zoomer;
}

