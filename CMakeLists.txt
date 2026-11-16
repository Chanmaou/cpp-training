cmake_minimum_required(VERSION 3.10)
project(cpp_training_labs LANGUAGES C CXX)

set(EXPERIMENT "4" CACHE STRING "Experiment number (0 to 4)")
set_property(CACHE EXPERIMENT PROPERTY STRINGS 0 1 2 3 4)
if(NOT EXPERIMENT MATCHES "^[0-4]$")
    message(FATAL_ERROR "EXPERIMENT must be a number from 0 to 4")
endif()

enable_testing()
add_subdirectory("experiment${EXPERIMENT}")
