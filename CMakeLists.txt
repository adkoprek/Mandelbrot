#  __  __                 _      _ _               _   
# |  \/  |               | |    | | |             | |  
# | \  / | __ _ _ __   __| | ___| | |__  _ __ ___ | |_ 
# | |\/| |/ _` | '_ \ / _` |/ _ \ | '_ \| '__/ _ \| __|
# | |  | | (_| | | | | (_| |  __/ | |_) | | | (_) | |_ 
# |_|  |_|\__,_|_| |_|\__,_|\___|_|_.__/|_|  \___/ \__|
#        https://github.com/adkoprek/Mandelbrot
#
# This is the top level CMake file. Following packages
# are required:
#   - GTK4
#   - GLIB2
#   - TBB
#
# @Author: Adam Koprek
# @Contributors: -
# @Licence: MIT

# Project setup
cmake_minimum_required(VERSION 3.16)
project(mandelbrot VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Remove the lib prefix from libs, adding it manualy
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# Profiles
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
endif()

# Creates the compile_commands.json file for your LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create symlink for compile_commands.json in root dir for lsp
execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)

# Output path
set(OutputDirectory "${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OutputDirectory}/obj")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OutputDirectory}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OutputDirectory}")

# Find TBB - Package
find_package(TBB REQUIRED)

# Find GTK
find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)
pkg_check_modules(GLIB glib-2.0)

# Add the GTK includes & link directories
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})
include_directories(${TBB_INCLUDE_DIRS})

# Add custom includes
include_directories(include)

# Add the subdirectories
add_subdirectory(src/app)
add_subdirectory(src/logic)
add_subdirectory(src/video)

# Build the GTK app
add_executable(mandelbrot
    ${APP_SRC_FILES}
    main.cpp
)

# Build the GTK video
add_executable(mandelbrot_video
    ${VIDEO_SRC_FILES}
    video.cpp
)

# Add the include files to avoid relative paths
target_include_directories(mandelbrot PRIVATE src/app)
target_include_directories(mandelbrot PRIVATE src/logic)

target_include_directories(mandelbrot_video PRIVATE src/video)
target_include_directories(mandelbrot_video PRIVATE src/logic)

# Link necessery libraires
target_link_libraries(libmandelbrot PRIVATE TBB::tbb)

target_link_libraries(mandelbrot PRIVATE libmandelbrot)
target_link_libraries(mandelbrot PRIVATE ${GTKMM_LIBRARIES})

target_link_libraries(mandelbrot_video PRIVATE libmandelbrot)
