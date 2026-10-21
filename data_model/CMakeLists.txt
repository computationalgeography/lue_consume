add_executable(lue_consume_data_model
    source/use_lue_data_model.cpp
)

target_link_libraries(lue_consume_data_model
    PRIVATE
        lue::data_model
)
