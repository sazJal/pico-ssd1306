#include "ssd1306.h"

void ssd1306_init(i2c_inst_t * i2cx, uint8_t addr)
{
    static uint8_t reg[2];
    sleep_ms(200);
    reg[0] = 0x00; reg[1] = 0xAE; //display off
    i2c_write_blocking(i2cx, addr, reg, 2, false);
    reg[0] = 0x00; reg[1] = 0x20; //Set Memory Addressing Mode 
    i2c_write_blocking(i2cx, addr, reg, 2, false); 
    reg[0] = 0x00; reg[1] = 0x10; //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    i2c_write_blocking(i2cx, addr, reg, 2, false);
    reg[0] = 0x00; reg[1] = 0xB0; //Set Page Start Address for Page Addressing Mode,0-7
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xC8; //Set COM Output Scan Direction
    i2c_write_blocking(i2cx, addr, reg, 2, false); 
    reg[0] = 0x00; reg[1] = 0x00; //---set low column address
    i2c_write_blocking(i2cx, addr, reg, 2, false); 
    reg[0] = 0x00; reg[1] = 0x10; //---set high column address
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0x40;  //--set start line address
    i2c_write_blocking(i2cx, addr, reg, 2, false); 
    reg[0] = 0x00; reg[1] = 0x81; //--set contrast control register
    i2c_write_blocking(i2cx, addr, reg, 2, false); 
    reg[0] = 0x00; reg[1] = 0xFF;
    i2c_write_blocking(i2cx, addr, reg, 2, false); 
    reg[0] = 0x00; reg[1] = 0xA1; //--set segment re-map 0 to 127
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xA6; //--set normal display
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xA8; //--set multiplex ratio(1 to 64)
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0x3F; 
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xA4; //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xD3; //-set display offset
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0x00; //-not offset
    i2c_write_blocking(i2cx, addr, reg, 2, false); 
    reg[0] = 0x00; reg[1] = 0xD5; //--set display clock divide ratio/oscillator frequency
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xF0; //--set divide ratio 
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xD9; //--set pre-charge period
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0x22;
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xDA; //--set com pins hardware configuration
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0x12; 
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xDB; //--set vcomh
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0x20; //0x20,0.77xVcc
    i2c_write_blocking(i2cx, addr, reg, 2, false); 
    reg[0] = 0x00; reg[1] = 0x8D; //--set DC-DC enable
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0x14;
    i2c_write_blocking(i2cx, addr, reg, 2, false);  
    reg[0] = 0x00; reg[1] = 0xAF; //--turn on SSD1306 panel
    i2c_write_blocking(i2cx, addr, reg, 2, false); 
}

void ssd1306_drawPixel(uint8_t *buffer, uint16_t x, uint16_t y, SSD_Color_t color)
{
	/* if the input coordinates are extending the dimension */
	if((x >= SSD1306_WIDTH)||(y>=SSD1306_HEIGHT)){return;}

	/* Set Color */
	if(color == SSD_COLOR_WHITE)
	{
		buffer[x+(y/8) * SSD1306_WIDTH] |= 1 << (y%8);
	} else
	{
		buffer[x+(y/8) * SSD1306_WIDTH] &= ~(1 << (y%8));
	}
}

char ssd1306_putChar(char ch, uint8_t *buffer, FontDef_t* font, SSD_Coordinate_t* coord, SSD_Color_t color)
{
	uint32_t i, b, j;

	/* Check Available space in LCD */
	if((SSD1306_WIDTH <= (coord->currentX + font->font_width))||(SSD1306_HEIGHT <= (coord->currentY + font->font_height))){return 0;}

	/* Go through font */
	for(i=0; i < font->font_height; i++)
	{
		b = font->data[(ch-32) * font->font_height + i];
		for(j=0; j < font->font_width; j++)
		{
			if((b<<j) & 0x8000)
			{
				ssd1306_drawPixel(buffer, coord->currentX + j, (coord->currentY+i), (SSD_Color_t) color);
			}
			else
			{
				ssd1306_drawPixel(buffer, coord->currentX + j, (coord->currentY+i), (SSD_Color_t) !color);
			}
		}
	}

	coord->currentX += font->font_width;

	return ch;
}

char ssd1306_putString(char* str, uint8_t* buffer, FontDef_t* font, SSD_Coordinate_t* coord, SSD_Color_t color)
{
    while(*str)
    {
        if(ssd1306_putChar(*str, buffer, font, coord, color) != *str){
            return *str;
        }

        str++;
    }
    return *str;
}

void ssd1306_drawBitmap(uint8_t *buffer, int16_t x0, int16_t y0, unsigned char* bitmap, int16_t width, int16_t height, SSD_Color_t color)
{
	int16_t byteWidth = (width + 7) >> 3;
	uint8_t byte = 0;

	for(int16_t j=0; j<height; j++, y0++)
	{
		for(int16_t i=0; i<width; i++)
		{
			if(i&7)
			{
				byte <<=1;
			} else
			{
				byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
			}
			if(byte & 0x80)
			{
                ssd1306_drawPixel(buffer, x0+i, y0, color);
			}
		}
	}
}

void ssd1306_update_screen(i2c_inst_t * i2cx, uint8_t addr, uint8_t* data)
{
    static uint8_t buff[2];
    static uint8_t buffer[150];
    static uint8_t ctrlByte = 0x40;

    for (uint8_t m=0; m<8; m++)
    {
        buff[0] = 0x00; buff[1] = 0xB0+m;
        i2c_write_blocking(i2cx, addr, buff, 2, false); 
        buff[1] = 0x00;
        i2c_write_blocking(i2cx, addr, buff, 2, false); 
        buff[1] = 0x10;
        i2c_write_blocking(i2cx, addr, buff, 2, false); 
        
        buffer[0] = ctrlByte;
        for(uint8_t i=0; i<SSD1306_WIDTH;i++)
        {
            buffer[i+1] = (uint8_t) *(data+(SSD1306_WIDTH*m)+i);
        }
        i2c_write_blocking(i2cx, addr, buffer, SSD1306_WIDTH+1, false);
        
    }
}


void ssd1306_fill(uint8_t* buffer, SSD_Color_t color, uint16_t length)
{
    memset(buffer, (color==SSD_COLOR_BLACK)?0x00:0xFF, length);
}