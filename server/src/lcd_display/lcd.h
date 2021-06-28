#ifndef _LCD_H_
#define _LCD_H_

#define LCD_ADDR          0x20
#define LCD_WRITE_DELAY     50
#define BACKLIGHT         0x08
#define DATA_REGISTER     0x01
#define FIRST_LINE        0x80
#define SECOND_LINE       0xC0

int LCM_write_command(int handle, unsigned char val);
int LCM_write_data(int handle, unsigned char val);
void init_lcd(const int fd);

#endif