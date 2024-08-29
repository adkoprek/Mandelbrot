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

#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "calc.h"
#include "config.h"
#include "zoomer.h"


/************************************************************
*                       public
************************************************************/

// Constructor
Zoomer::Zoomer(Config* config) {
    m_config = config;
    m_calc = new Calc(config->width, config->height);
}

// Deconstructor
Zoomer::~Zoomer() {
    delete m_calc;
}

// Run the calculations
void Zoomer::run() {
    while (m_counter < m_config->iter_num) {
        
        // If current index is under the start just move and
        // zoom the cordinates iterativlity. Not most performant 
        // but in comparison to the main calculation not a big deal.
        if (m_counter >= m_config->iter_start) {

            // Ideal max iteration would be with a factor of 10 but
            // on average cpu with a big zoom 10 is too much
            int max_iter = 2 * std::sqrt(calc_zoom_factor()) + 100;

            m_calc->calc_new(m_x_min, m_x_max, m_y_max, m_y_min, max_iter);
            save_image();
        }
        move();
        zoom();
        m_counter++;
    }
}

/************************************************************
*                       private
************************************************************/

// Move the current mandelbrot set to the desired cordinates
void Zoomer::move() {
    if (m_move_complete) return;
    double x = m_x_min + (m_x_max - m_x_min) / 2;
    double y = m_y_min + (m_y_max - m_y_min) / 2;
    double x_step = m_config->step;
    double y_step = m_config->step;
    int factor = 1;

    if (fabs(x - m_config->x) < m_config->step) x_step = fabs(x - m_config->x);
    if (fabs(y - m_config->y) < m_config->step) y_step = fabs(y - m_config->y);

    if (x > m_config->x) factor = -1;
    m_x_max += factor * x_step;
    m_x_min += factor * x_step;

    factor = 1;
    if (y > m_config->y) factor = -1;
    m_y_max += factor * y_step;
    m_y_min += factor * y_step;

    if (x_step < 1e-10 && y_step < 1e-10) m_move_complete = true;
}

// Zoom to on the current cordinates by the step factor
void Zoomer::zoom() {
    if (!m_move_complete) return;   // First move then zoom

    double old_width = m_x_max - m_x_min;
    double old_height = m_x_max - m_x_min;
    double calc_step = m_config->step * old_width;
    double step = calc_step > m_config->step ? m_config->step : calc_step;
    double new_width = old_width - step;
    double new_height = old_width / old_height * new_width;
    double x = m_x_min + old_width / 2;
    double y = m_y_min + old_height / 2;

    m_x_min = x - new_width / 2;
    m_x_max = x + new_width / 2;
    m_y_min = y - new_height / 2;
    m_y_max = y + new_height / 2;
}

// Save the last image
void Zoomer::save_image() {
    std::string file_name = m_config->img_path + "/" + std::to_string(m_counter) + ".png";
    std::ofstream file;
    file.open(file_name, std::ofstream::binary);
    // Savin in a P6 .ppm format is the most easiest. The data is optimized later in the
    // video maker python script
    file << "P6\n" << m_config->width << " " << m_config->height << "\n255\n";
    file.write(reinterpret_cast<const char*>(m_calc->get_color_array()), m_config->width * m_config->height * 3);
    file.close();
    std::cout << "Saved: " << file_name << std::endl;
}

// Calc tbe zoom factor
uint64_t Zoomer::calc_zoom_factor() {
    long double width = m_x_max - m_x_min;
    return m_initial_width / width;
}
