//  __  __                 _      _ _               _   
// |  \/  |               | |    | | |             | |  
// | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
// | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
// | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
// |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
//        https://github.com/adkoprek/Mandelbrot
//
// This Struct gets config for a video from the .cfg files
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#pragma once
#include <cstddef>
#include <string>


typedef struct Config {
    size_t width = 512;                 // Width of the images
    size_t height = 512;                // Height of the images
    int iter_start = 0;                 // What iteration to sturt calculating
    int iter_num = 0;                   // Until wich iteration to calculate
    double x = -2;                      // X-Axis zoom cordiantes
    double y = 0.0;                     // Y-Axis zoom cordinates
    double step = 0.1;                  // The step size
    std::string img_path = "./images";  // The path wehre to store the images
} Config;
