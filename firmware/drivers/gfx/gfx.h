/**
 * Based on Adafruit's gfx library available at
 * https://github.com/adafruit/Adafruit-GFX-Library
 * see license.txt for details.
 */

#ifndef GFX_H_
#define GFX_H_

#define swap(a, b) { short t = a; a = b; b = t; }
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define WIDTH  128
#define HEIGHT 128

void gfx_drawPixel(short x, short y, u8 color);
void gfx_drawLine(short x0, short y0, short x1, short y1, u8 color);
void gfx_drawFastVLine(short x, short y, short h, u8 color);
void gfx_drawFastHLine(short x, short y, short w, u8 color);
void gfx_drawRect(short x, short y, short w, short h, u8 color);
void gfx_fillRect(short x, short y, short w, short h, u8 color);
void gfx_fillScreen(u8 color);

////void invertDisplay(boolean i);

void gfx_drawCircle(short x0, short y0, short r, u8 color);
void gfx_drawCircleHelper( short x0, short y0, short r,
		u8 cornername, u8 color);
void gfx_fillCircle(short x0, short y0, short r, u8 color);
void gfx_fillCircleHelper(short x0, short y0, short r, u8 cornername,
		short delta, u8 color);
void gfx_drawTriangle(short x0, short y0, short x1, short y1, short x2,
		short y2, u8 color);
void gfx_fillTriangle ( short x0, short y0, short x1, short y1,
		short x2, short y2, u8 color);
void gfx_drawRoundRect(short x, short y, short w, short h, short r, u8 color);
void gfx_fillRoundRect(short x, short y, short w, short h, short r, u8 color);

//void drawBitmap(u8 x, u8 y, const u8 *bitmap,
//      u8 w, u8 h, u8 color);
//void drawBitmap(u8 x, u8 y, const u8 *bitmap,
//      u8 w, u8 h, u8 color, u8 bg);
//void drawXBitmap(u8 x, u8 y, const u8 *bitmap,
//      u8 w, u8 h, u8 color);

void gfx_drawChar(short x, short y, unsigned char c, u8 color, u8 bg, u8 size);
//void setCursor(u8 x, u8 y);
//void setTextColor(u8 c);
//void setTextColor(u8 c, u8 bg);
//void setTextSize(u8 s);
//void setTextWrap(boolean w);
//void setRotation(u8 r);

//  void gfx_height(void);
//  void gfx_width(void);
//  void gfx_getRotation(void);


#endif /* GFX_H_ */
