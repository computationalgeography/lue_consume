cmake_minimum_required(
    VERSION 3.26)
project(LUE_CONSUME
    VERSION 0.3.8
    LANGUAGES CXX)

cmake_policy(SET CMP0144 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(lue
    GIT_REPOSITORY https://github.com/computationalgeography/lue.git
    # GIT_REPOSITORY file://$ENV{HOME}/development/project/github/computational_geography/lue
    GIT_TAG master
    SYSTEM
    FIND_PACKAGE_ARGS 0.3.8
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
