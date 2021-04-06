
set(FONT_PATH ${CMAKE_CURRENT_LIST_DIR}/FontSSD)
set(SSD1306_PATH ${CMAKE_CURRENT_LIST_DIR}/Ssd1306)

set(ssd1306_SOURCES
    ./ssd1306.c
    ./ssd1306.h
)

add_subdirectory(FontSSD)

# include_directories(
#     ${CMAKE_SOURCE_DIR}/FontSSD
# )

add_library(ssd1306 ${ssd1306_SOURCES})

# include_directories(${CMAKE_CURRENT_LIST_DIR}/Font)
# link_directories(${CMAKE_CURRENT_LIST_DIR}/Font)


# target_include_directories(ssd1306 PUBLIC ${FONT_PATH})

target_link_libraries(ssd1306 
    pico_stdlib    
    hardware_i2c
    font1306
)

