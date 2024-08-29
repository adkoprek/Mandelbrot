#  __  __                 _      _ _               _   
# |  \/  |               | |    | | |             | |  
# | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
# | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
# | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
# |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
#        https://github.com/adkoprek/Mandelbrot
#
# This CMake file defines the reference path for the
# top level project directory. So they can be build
# by the top level CMake file.

# @Author: Adam Koprek
# @Contributors: -
# @Licence: MIT

set(VIDEO_SRC_FILES 
    src/video/config.h
    src/video/config_parser.cpp
    src/video/config_parser.h
    src/video/zoomer.cpp
    src/video/zoomer.h
    PARENT_SCOPE
)
