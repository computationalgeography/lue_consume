cmake_minimum_required(
    VERSION 3.26)
project(LUE_CONSUME
    VERSION 0.0.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# LUE useѕ a recent version of FMT. Find FMT before finding LUE so LUE will find our FMT.
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG e69e5f977d458f2650bb346dadf2ad30c5320281  # 10.2.1
    SYSTEM
    FIND_PACKAGE_ARGS 10
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(lue
    GIT_REPOSITORY https://github.com/computationalgeography/lue.git
    # GIT_REPOSITORY file://$ENV{HOME}/development/project/github/computational_geography/lue
    GIT_TAG master
    SYSTEM
)
FetchContent_MakeAvailable(lue)


add_executable(lue_consume_data_model
    use_lue_data_model.cpp
)

target_link_libraries(lue_consume_data_model
    PRIVATE
        lue::data_model
)


add_executable(lue_consume_framework
    use_lue_framework.cpp
)

target_link_libraries(lue_consume_framework
    PRIVATE
        lue::framework_focal_operation
        lue::framework_local_operation
        HPX::wrap_main
)
