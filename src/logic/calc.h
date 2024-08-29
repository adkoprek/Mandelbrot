//  __  __                 _      _ _               _   
// |  \/  |               | |    | | |             | |  
// | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
// | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
// | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
// |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
//        https://github.com/adkoprek/Mandelbrot
//
// Class the does the calculation and coloring for the 
// mandelbrot set. It's the heart of the project.
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#pragma once
#include <cstddef>
#include <cstdint>


namespace  {
    typedef long double ldoub;  // Define a shortening for the data type
}

class Calc {
public:
    /************************************************************
    *                       functions
    ************************************************************/

    // Constructor
    // @param number of points on the x axis to cmopute
    // @param number of points on the y axis to cmopute
    Calc(size_t width, size_t height);

    // Decsontructor
    ~Calc();

    // Calc new mandelbrot image
    // @param starting cordinates on x-axis
    // @param ending cordinates on x-axis
    // @param starting cordinates on y-axis
    // @param ending cordinates on y-axis
    // @param number of maxim_iterations to use
    void calc_new(ldoub x_start, ldoub x_end, ldoub y_start, ldoub y_end, int max_iter);

    // Get the pointer to the data bitmap with 3 rgb bytes per pixel 
    // @return pointer to the bitmap
    uint8_t* get_color_array();

private:
    /************************************************************
    *                       functions
    ************************************************************/

    // Create an array with evenly spaced points
    // @param number of points
    // @param pointer to the data array
    // @param starting value
    // @param ending value
    void linspace(int points, ldoub* data, ldoub start, ldoub end);

    // Calculate pixel at give ncordinates
    // @param x point index
    // @param y point index
    // @param x point cordinates
    // @param y point cordinates
    // @param maximum_number of iterations
    void calc_pixel(int x_cor, int y_cor, ldoub x, ldoub y, int max_iter);

    // Set color for a point x - y
    // @param x point index
    // @param y point index
    // @param number of iterations for the given point
    // @param maximum iteration number
    // @param magnitude of the given point
    void set_color(int x, int y, int iterations, int max_iter, ldoub mag);

    /************************************************************
    *                       members
    ************************************************************/

    uint8_t* m_colors;      // The continuous data bitmap of size
                            // width * height * 3 where every pixel
                            // taking three bytes, on byte per color
                            // chanel
    size_t m_width;         // The number of x-points
    size_t m_height;        // The number of y-points
};
