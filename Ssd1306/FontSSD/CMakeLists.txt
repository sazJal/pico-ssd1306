set(font_SOURCES
    ./font1.c
)

add_library(font1306 ${font_SOURCES})
target_link_libraries(font1306 
    pico_stdlib)