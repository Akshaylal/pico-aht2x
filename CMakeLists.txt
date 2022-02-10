add_library(pico_aht2x
        aht2x.cpp)

target_link_libraries(pico_aht2x
        hardware_i2c
        pico_stdlib
        )
target_include_directories (pico_aht2x PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})