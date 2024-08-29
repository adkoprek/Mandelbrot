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

#pragma once
#include <cstddef>
#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>

#include "calc.h"


class MainWindow : public Gtk::Window {
public:
    /************************************************************
    *                       functions
    ************************************************************/

    // Constructor
    // @param the width of the window
    // @param the height of the window
    MainWindow(size_t width, size_t height);

    // Deconstructor
    virtual ~MainWindow();
    
protected:
    /************************************************************
    *                       functions
    ************************************************************/

    // Function that gets called to draw on the drawind area
    // @param context of the drawind area
    // @param new width
    // @param new height
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

    /************************************************************
    *                       members
    ************************************************************/

    Gtk::DrawingArea m_drawing_area;    // The instance of the GTK DrawindArea

private:
    /************************************************************
    *                       functions
    ************************************************************/

    // Function to setup the UI
    void setup_ui();

    // Function to initialize the calculations
    void calc();

    /************************************************************
    *                       members
    ************************************************************/

    size_t m_width;                     // The width of the window
    size_t m_height;                    // The height of the window
    Calc* m_calc;                       // Instance of the Calc class
};
