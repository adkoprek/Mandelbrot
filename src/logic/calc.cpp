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

#include <cmath>
#include <complex.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <tbb/blocked_range.h>
#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>

#include "rgb.h"
#include "calc.h"

#define SQUARE(x) ((x) * (x)) 
typedef long double ldoub;


/************************************************************
*                       public
************************************************************/

// Constructor
Calc::Calc(size_t width, size_t height) {
    m_colors = (uint8_t*)malloc(width * height * 3);
    m_width = width;
    m_height = height;
}

// Decsontructor
Calc::~Calc() {
    delete m_colors;
}

// Calc new mandelbrot image
void Calc::calc_new(ldoub x_start, ldoub x_end, ldoub y_start, ldoub y_end, int max_iter) {
    ldoub x_points[m_width];
    ldoub y_points[m_height];
    linspace(m_width,  x_points, x_start, x_end);
    linspace(m_height, y_points, y_start, y_end);

    // The operations are parallelised with the intel tbb library
    tbb::parallel_for(tbb::blocked_range2d<size_t, size_t>(0, m_width, 0, m_height),
        [&](const tbb::blocked_range2d<size_t, size_t>& r) {
            const tbb::blocked_range<size_t>& rows = r.rows();
            const tbb::blocked_range<size_t>& cols = r.cols();

            for (size_t y = cols.begin(); y != cols.end(); ++y) {
                for (size_t x = rows.begin(); x != rows.end(); ++x) {
                    // Reset every pixel to black
                    *(m_colors + 3 * y * m_width + 3 * x + 0) = 0x00;
                    *(m_colors + 3 * y * m_width + 3 * x + 1) = 0x00;
                    *(m_colors + 3 * y * m_width + 3 * x + 2) = 0x00;

                    // Calc new pixel
                    calc_pixel(x, y, x_points[x], y_points[y], max_iter);
                }
            }
        }
    );
}

// Get the pointer to the data bitmap with 3 rgb bytes per pixel 
uint8_t* Calc::get_color_array() { return m_colors; }

/************************************************************
*                       private
************************************************************/

// Create an array with evenly spaced points
void Calc::linspace(int points, ldoub* data, ldoub start, ldoub end) {
    ldoub step = (end - start) / m_width;
    ldoub current = start;
    for (int i = 0; i < m_width; i++) {
        data[i] = current;
        current += step;
    }
}

// Calculate pixel at give ncordinates
void Calc::calc_pixel(int x_cor, int y_cor, ldoub x, ldoub y, int max_iter) {
    ldoub real_2 = 0;
    ldoub imag_2 = 0;
    ldoub real = 0;
    ldoub imag = 0;

    for (int i = 0; i < max_iter; i++) {
        if ((real_2 + imag_2) > 256) {
            set_color(x_cor, y_cor, i, max_iter, (real_2 + imag_2));
            break;
        }

        imag = 2 * real * imag + y; 
        real = real_2 - imag_2 + x;
        real_2 = SQUARE(real);
        imag_2 = SQUARE(imag);
    }
}

// Set color for a point x - y
void Calc::set_color(int x, int y, int iterations, int max_iter, ldoub mag) {
#ifndef GAUSS_COLOR
    // This is a smoothen way of coloring the mandelbrot set inspired by
    // https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set
    
    double smoothed = std::log2(std::log2(mag) / 2);
    int index = (int)(std::sqrt(iterations + 10 - smoothed) * 256) % 2048;
    const unsigned char* color = rgb[index];

    *(m_colors + 3 * y * m_width + 3 * x + 0) = color[0];
    *(m_colors + 3 * y * m_width + 3 * x + 1) = color[1];
    *(m_colors + 3 * y * m_width + 3 * x + 2) = color[2];
#endif // !GAUSS_COLOR
#ifdef GAUSS_COLOR
    // My own coloring way with Gauss functions

    double factor_r = 0;
    double factor_g = 0;
    double factor_b = 0;

    iterations /= max_iter / 100;

    if (iterations < 10) factor_r = 1;
    else if (iterations < 40) {
        factor_r = std::exp(-(std::pow(iterations - 10, 2) / 625));
        factor_g = 1; 
    }
    else {
        factor_g = std::exp(-(std::pow(iterations - 40, 2) / 1764));
        factor_b = 1;
    }

    *(m_colors + 3 * y * m_width + 3 * x + 0) = factor_r * iterations * 22.5;
    *(m_colors + 3 * y * m_width + 3 * x + 1) = factor_g * iterations * 5.625;
    *(m_colors + 3 * y * m_width + 3 * x + 2) = factor_b * iterations * 2.25;
#endif // GAUSS
}
