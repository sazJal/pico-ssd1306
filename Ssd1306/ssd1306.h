#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "FontSSD/font1.h"

#define I2C_PORT i2c0
#define SSD1306_WIDTH		128
#define SSD1306_HEIGHT		64

typedef enum SSD_Color{
    SSD_COLOR_BLACK,
    SSD_COLOR_WHITE
} SSD_Color_t;

typedef struct SSD_Coordinate
{
	uint16_t currentX;
	uint16_t currentY;
} SSD_Coordinate_t;

void ssd1306_init(i2c_inst_t * i2cx, uint8_t addr);
void ssd1306_fill(uint8_t* buffer, SSD_Color_t color, uint16_t length);
void ssd1306_drawPixel(uint8_t *buffer, uint16_t x, uint16_t y, SSD_Color_t color);
void ssd1306_drawBitmap(uint8_t *buffer, int16_t x0, int16_t y0, unsigned char* bitmap, int16_t width, int16_t height, SSD_Color_t color);
char ssd1306_putChar(char ch, uint8_t *buffer, FontDef_t* font, SSD_Coordinate_t* coord, SSD_Color_t color);
char ssd1306_putString(char* str, uint8_t*buffer, FontDef_t* font, SSD_Coordinate_t* coord, SSD_Color_t color);
void ssd1306_update_screen(i2c_inst_t * i2cx, uint8_t addr, uint8_t* data);
// void ssd1306_update_screen(i2c_inst_t * i2cx, uint8_t* data);