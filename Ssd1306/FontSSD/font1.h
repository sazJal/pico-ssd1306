#include "pico/stdlib.h"

typedef struct FontDef
{
    uint8_t font_width;
    uint8_t font_height;
    const uint16_t *data;
} FontDef_t;

typedef struct FontSize
{
    uint16_t length;
    uint16_t height;
} FontSize_t;

extern FontDef_t Font_7x10;
extern FontDef_t Font_11x18;
extern FontDef_t Font_16x26;
// unsigned char elon[];