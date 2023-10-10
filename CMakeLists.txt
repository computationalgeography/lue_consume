cmake_minimum_required(
    VERSION 3.26)
project(LUE_CONSUME
    VERSION 0.3.8
    LANGUAGES CXX)


include(FetchContent)

FetchContent_Declare(lue
    # GIT_REPOSITORY https://github.com/computationalgeography/lue.git
    GIT_REPOSITORY file://$ENV{HOME}/development/project/github/computational_geography/lue
    GIT_TAG gh446  # TODO Update to master branch
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


add_executable(lue_consume_framework
    use_lue_framework.cpp
)

target_link_libraries(lue_consume_framework
    PRIVATE
        lue::framework_algorithm
)
