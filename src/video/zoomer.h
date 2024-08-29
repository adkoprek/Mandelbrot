//  __  __                 _      _ _               _   
// |  \/  |               | |    | | |             | |  
// | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
// | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
// | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
// |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
//        https://github.com/adkoprek/Mandelbrot
//
// This class manages te zoom for the mandelbrot set 
// video it is the core part of the video maker.
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#pragma once
#include <cstdint>

#include "calc.h"
#include "config.h"


class Zoomer {
public:
    /************************************************************
    *                       functions
    ************************************************************/

    // Constructor
    // @param pointer to the config struct
    Zoomer(Config* config);

    // Deconstructor
    ~Zoomer();

    // Run the calculations
    void run();

private:
    /************************************************************
    *                       functions
    ************************************************************/

    // Move the current mandelbrot set to the desired cordinates
    void move();

    // Zoom to on the current cordinates by the step factor
    void zoom();

    // Save the last image
    void save_image();

    // Calc tbe zoom factor
    uint64_t calc_zoom_factor();

    /************************************************************
    *                       members
    ************************************************************/

    int m_counter = 0;  // Counter of the current iteration
    Config* m_config;   // Pointer to the config struct
    Calc* m_calc;       // Pointer to the instance of the Calc class

    // Set when the image is on the desired x and y cordinates
    bool m_move_complete = false;

    // The cordinates for wich to render the mandelbrot set
    double m_x_min = -2.0;
    double m_x_max =  0.48;
    double m_y_max =  1.24;
    double m_y_min = -1.24;

    // Save the initial width to calc the zoom factor
    const double m_initial_width = m_x_max - m_x_min; 
};
