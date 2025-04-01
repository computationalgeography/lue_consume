cmake_minimum_required(
    VERSION 3.30)
project(LUE_CONSUME
    VERSION 0.0.0
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN TRUE)

include(FetchContent)

FetchContent_Declare(lue
    GIT_REPOSITORY https://github.com/computationalgeography/lue.git
    # GIT_REPOSITORY file://$ENV{HOME}/development/project/github/computational_geography/lue
    GIT_TAG master
    SYSTEM
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(lue)


add_executable(lue_consume_data_model
    use_lue_data_model.cpp
)

target_link_libraries(lue_consume_data_model
    PRIVATE
        lue::data_model
)


add_executable(lue_consume_framework_algorithm
    use_lue_framework_algorithm.cpp
)

target_link_libraries(lue_consume_framework_algorithm
    PRIVATE
        lue::framework_focal_operation
        lue::framework_local_operation
        HPX::wrap_main
)


add_executable(lue_consume_framework_io
    use_lue_framework_io.cpp
)

target_link_libraries(lue_consume_framework_io
    PRIVATE
        lue::framework_io
        lue::framework_local_operation
        HPX::wrap_main
)
