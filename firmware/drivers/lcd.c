/**
 * This LCD driver is based on the Arduino LiquidCrystal library
 * available at github.com/arduino-libraries/LiquidCrystal
 */

#include <xbasic_types.h>
#include <xiomodule.h>
#include "lcd.h"
#include "fit_timer.h"

// State keeping variables, useful for config functions.
u8 _displayfunction = 0;
u8 _displaycontrol = 0;
u8 _displaymode = 0;
u8 _initialized = 0;

// reference to mblaze IO Module
XIOModule* _io_mod_lcd = NULL;

void clear()
{
	command(LCD_CLEARDISPLAY);
	delay_20us(110);
}

void home()
{
	command(LCD_RETURNHOME);
	delay_20us(110);
}

/**
 * Upper nibble defines row and lower nibble defines column.
 */
void setCursor(u8 position)
{
	u8 upper = (position & 0xF0);
	u8 col   = (position & 0x0F);
	u8 row   = ((upper > 0x10) ? 0x28 : 0x00);
	command(LCD_SETDDRAMADDR | (row | col));
}

/*
 * DISPLAY CONTROL COMMANDS
 */
void noDisplay()
{
	_displaycontrol &= ~LCD_DISPLAYON;
	command(_displaycontrol);
}

void display()
{
	_displaycontrol |= LCD_DISPLAYON;
	command(_displaycontrol);
}

void noCursor()
{
	_displaycontrol &= ~LCD_CURSORON;
	command(_displaycontrol);
}

void cursor()
{
	_displaycontrol |= LCD_CURSORON;
	command(_displaycontrol);
}

void noBlink()
{
	_displaycontrol &= ~LCD_BLINKON;
	command(_displaycontrol);
}

void blink()
{
	_displaycontrol |= LCD_BLINKON;
	command(_displaycontrol);
}

// These commands scroll the display without changing the RAM
void scrollDisplayLeft(void)
{
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void scrollDisplayRight(void)
{
	command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void leftToRight(void)
{
	_displaymode |= LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void rightToLeft(void)
{
	_displaymode &= ~LCD_ENTRYLEFT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void autoscroll(void)
{
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void noAutoscroll(void)
{
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void createChar(u8 location, u8* charmap)
{
	int i = 0;
	location &= 0x7; // we only have 8 locations 0-7
	command(LCD_SETCGRAMADDR | (location << 3));
	for (i = 0; i < 8; i++)
	{
		write(charmap[i]);
	}
}

void print_ASCII(char* msg)
{
	while (*msg)
		write(*msg++);
}

void command(u8 cmd)
{
	_generic_write_4bit(0, cmd);
}

void write(u8 data)
{
	_generic_write_4bit(1, data);
}

void _generic_write_4bit(u8 isData, u8 arg)
{
	u8 base  = isData ? 32 : 0;
	u8 upper = ((arg & 240)>>4) | base;
	u8 lower = ((arg & 15)) | base;

	// write upper nibble
	_pulse_lcd_e(upper);
	delay_20us(1);

	// write lower nibble
	_pulse_lcd_e(lower);
	delay_20us(3);
}

void _pulse_lcd_e(u8 val)
{
	u8 data = val | 16;
	XIOModule_DiscreteWrite(_io_mod_lcd, 2, data);
	delay_20us(1);
	data = val ;
	XIOModule_DiscreteWrite(_io_mod_lcd, 2, data);
}

void init_lcd(XIOModule* gpo1)
{
	// initialize reference to mblaze IO module.
	_io_mod_lcd = gpo1;

	// wait 15ms
	delay_ms(15);

	// write 0x3 and pulse LCD_E for 12 cycles
	_pulse_lcd_e(0x03);

	// wait 4.1 ms or longer
	delay_ms(5);

	// write 0x3 and pulse LCD_E for 12 cycles
	_pulse_lcd_e(0x03);

	// wait 100 us or longer
	delay_20us(5);

	// write 0x3 and pulse LCD_E for 12 cycles
	_pulse_lcd_e(0x03);

	// wait 40 us or longer
	delay_20us(3);

	// write 0x2 and pulse LCD_E for 12 cycles
	_pulse_lcd_e(0x02);

	// wait 40 us or longer
	delay_20us(3);

	// flag initialized display
	_initialized = 1;
}

/**
 * Set default LCD module configuration.
 *
 * 4bit mode, 2 lines, 5x8 characters, visible cursor, left-to-right writing,
 * auto increment pointer, cursor at (0,0).
 */
void config_lcd()
{
	_displayfunction = LCD_FUNCTIONSET | LCD_2LINE | LCD_4BITMODE | LCD_5x8DOTS;
	command(_displayfunction);

	_displaymode = LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	command(_displaymode);

	_displaycontrol = LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSORON | LCD_BLINKOFF;
	command(_displaycontrol);

	clear();
}
