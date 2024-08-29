#  __  __                 _      _ _               _   
# |  \/  |               | |    | | |             | |  
# | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
# | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
# | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
# |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
#        https://github.com/adkoprek/Mandelbrot
#
# This CMake file builds the library
#
# @Author: Adam Koprek
# @Contributors: -
# @Licence: MIT

add_library(libmandelbrot
    calc.cpp
    calc.h
)
