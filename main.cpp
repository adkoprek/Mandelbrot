//  __  __                 _      _ _               _   
// |  \/  |               | |    | | |             | |  
// | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
// | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
// | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
// |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
//        https://github.com/adkoprek/Mandelbrot
//
// This file contains the main entry point for the GTK 
// application.
//
// The app accepts two parameters -x and -y for the size
// of the window.
//
// @Author: Adam Koprek
// @Contributors: -
// @Licence: MIT

#include "mainwindow.h"

#include <complex.h>
#include <glibmm/optioncontext.h>
#include <gtkmm/application.h>
#include <iostream>


int get_args(int argc, char** argv, int* width, int* height);

int main (int argc, char* argv[]) {
    int width = -1;
    int height = -1;
    int code = get_args(argc, argv, &width, &height);
    if (code) return -1;

    auto app = Gtk::Application::create("org.adkoprek.mandelbrot");
    return app->make_window_and_run<MainWindow>(argc, argv, width, height);
}

int get_args(int argc, char** argv, int* width, int* height) {
    Glib::OptionContext context;
    Glib::OptionGroup group("ui", "UI Setup", "Arguments to customize the UI");

    Glib::OptionEntry width_entry;
    width_entry.set_long_name("width");
    width_entry.set_short_name('x');
    width_entry.set_description("Set the width of the plot");
    width_entry.set_arg_description("pixels");
    group.add_entry(width_entry, *width);

    Glib::OptionEntry height_entry;
    height_entry.set_long_name("height");
    height_entry.set_short_name('y');
    height_entry.set_description("Set the height of th plot");
    height_entry.set_arg_description("pixels");
    group.add_entry(height_entry, *height);

    context.add_group(group);

    try { 
        context.parse(argc, argv); 
        if (*width == -1 || *height == -1) {
            std::cerr << "Option parsing failed: The width and the height have to be set" << std::endl;
            return -1;
        }
    } catch (const Glib::Error& ex) {
        std::cerr << "Option parsing failed: " << ex.what() << std::endl;
        return -1;
    }

    return 0;
}
