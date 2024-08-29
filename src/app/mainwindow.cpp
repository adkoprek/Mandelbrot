//  __  __                 _      _ _               _   
// |  \/  |               | |    | | |             | |  
// | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
// | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
// | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
// |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
//        https://github.com/adkoprek/Mandelbrot
//
// The GTK MainWindow that cals the Mandelbrot calculation
// and displays them on a canvas, very simple.
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#include <cstddef>
#include <cstdint>
#include <gdkmm/general.h>
#include <gdkmm/pixbuf.h>

#include "mainwindow.h"
#include "calc.h"


/************************************************************
*                       public
************************************************************/

// Constructor
MainWindow::MainWindow(size_t width, size_t height) : m_drawing_area() {
    m_width = width;
    m_height = height;
    m_calc = new Calc(m_width, m_height);
    set_title("Mandelbrot Set");
    setup_ui();
    calc();
}

// Deconstructor
MainWindow::~MainWindow() {
    delete m_calc;
}

/************************************************************
*                       protected
************************************************************/

// Function that gets called to draw on the drawind area
void MainWindow::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
    uint8_t* colors = m_calc->get_color_array();

    auto pixbuf = Gdk::Pixbuf::create_from_data(
        colors,
        Gdk::Colorspace::RGB,   
        false,                 
        8,                     
        m_width,
        m_height,
        m_width * 3
    );

    Gdk::Cairo::set_source_pixbuf(cr, pixbuf, 0, 0);
    cr->paint();
}

/************************************************************
*                       private
************************************************************/

// Function to setup the UI
void MainWindow::setup_ui() {
    m_drawing_area.set_draw_func(sigc::mem_fun(*this, &MainWindow::on_draw));
    m_drawing_area.set_content_width(m_width);
    m_drawing_area.set_content_height(m_height);
    this->set_child(m_drawing_area);
    this->set_resizable(false);
}

// Function to initialize the calculations
void MainWindow::calc() {
    m_calc->calc_new(-2, 0.47, 1.12, -1.12, 500);
    m_drawing_area.queue_draw();
}
