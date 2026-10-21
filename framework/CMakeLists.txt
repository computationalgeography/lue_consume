add_executable(lue_consume_framework_algorithm
    source/use_lue_framework_algorithm.cpp
)

target_link_libraries(lue_consume_framework_algorithm
    PRIVATE
        lue::framework_focal_operation
        lue::framework_local_operation
        lue::framework_miscellaneous_operation
        HPX::wrap_main
)


add_executable(lue_consume_framework_io
    source/use_lue_framework_io.cpp
)

target_link_libraries(lue_consume_framework_io
    PRIVATE
        lue::framework_io
        lue::framework_local_operation
        lue::framework_miscellaneous_operation
        HPX::wrap_main
)
