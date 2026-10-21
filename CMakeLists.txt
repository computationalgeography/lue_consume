cmake_minimum_required(
    VERSION 3.31)
project(LUE_CONSUME
    VERSION 0.0.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)
set(CMAKE_CXX_SCAN_FOR_MODULES FALSE)

include(FetchContent)

find_package(lue)

add_subdirectory(data_model)
add_subdirectory(framework)
