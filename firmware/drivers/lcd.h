/**
 * This LCD library is based on the Arduino LiquidCrystal library
 * available at github.com/arduino-libraries/LiquidCrystal
 */

#ifndef LCD_H_
#define LCD_H_

// dimensions
#define LCD_NROWS 0x02
#define LCD_NCOLS 0x10

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// Arduino API
void clear();
void home();
void setCursor(u8 position);

void noDisplay();
void display();
void noBlink();
void blink();
void noCursor();
void cursor();

void scrollDisplayLeft();
void scrollDisplayRight();
void leftToRight();
void rightToLeft();
void autoscroll();
void noAutoscroll();

void createChar(u8 location, u8* charmap);
void print_ASCII(char* msg);

void init_lcd(XIOModule* gpo1);
void config_lcd();
void command(u8 cmd);
void write(u8 data);
void _pulse_lcd_e(u8 val);
void _generic_write_4bit(u8 isData, u8 arg);

#endif /* LCD_H_ */
