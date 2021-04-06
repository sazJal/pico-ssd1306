cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(joss)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    isquaredc.c
)

add_subdirectory(Ssd1306)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_i2c
    ssd1306
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})