/**
 * Based on Adafruit's gfx library available at
 * https://github.com/adafruit/Adafruit-GFX-Library
 * see license.txt for details.
 */

#include <xbasic_types.h>
#include <xiomodule.h>
#include "gfx.h"
#include "bram.h"
#include "font.h"

void gfx_drawPixel(short x, short y, u8 color)
{
	if (x < 0 || y < 0)
		return;

	u16 addr = (y << 7) | (x & 0x7F);
	write_4bit(color, addr);
}

void gfx_drawLine(short x0, short y0, short x1, short y1, u8 color)
{
	short steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep)
	{
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1)
	{
		swap(x0, x1);
		swap(y0, y1);
	}

	short dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	short err = dx / 2;
	short ystep;

	if (y0 < y1)
	{
		ystep = 1;
	} else
	{
		ystep = -1;
	}

	for (; x0<=x1; x0++)
	{
		if (steep)
		{
			gfx_drawPixel(y0, x0, color);
		} else
		{
			gfx_drawPixel(x0, y0, color);
		}
		err -= dy;
		if (err < 0)
		{
			y0 += ystep;
			err += dx;
		}
	}
}

void gfx_drawFastVLine(short x, short y, short h, u8 color)
{
//	gfx_drawLine(x, y, x, y+h-1, color);
	int k = 0;
	if (h == 0)
		return;

	if (h < 0)
	{
		y -= h;
		h = -h;
	}

	for (k = 0; k < h; ++k)
		gfx_drawPixel(x, y+k, color);
}

void gfx_drawFastHLine(short x, short y, short w, u8 color)
{
//	gfx_drawLine(x, y, x+w-1, y, color);
	int k = 0;
	if (w == 0)
		return;

	if (w < 0)
	{
		x -= w;
		w = -w;
	}

	for (k = 0; k < w; ++k)
		gfx_drawPixel(x+k, y, color);
}

void gfx_drawRect(short x, short y, short w, short h, u8 color)
{
	gfx_drawFastHLine(x, y, w, color);
	gfx_drawFastHLine(x, y+h-1, w, color);
	gfx_drawFastVLine(x, y, h, color);
	gfx_drawFastVLine(x+w-1, y, h, color);
}

void gfx_fillRect(short x, short y, short w, short h, u8 color)
{
	short i = x;
	for (; i < x + w; i++)
		gfx_drawFastVLine(i, y, h, color);
}

void gfx_fillScreen(u8 color)
{
	gfx_fillRect(0, 0, WIDTH, HEIGHT, color);
}

void gfx_drawCircle(short x0, short y0, short r, u8 color)
{
	short f = 1 - r;
	short ddF_x = 1;
	short ddF_y = -2 * r;
	short x = 0;
	short y = r;

	gfx_drawPixel(x0  , y0+r, color);
	gfx_drawPixel(x0  , y0-r, color);
	gfx_drawPixel(x0+r, y0  , color);
	gfx_drawPixel(x0-r, y0  , color);

	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		gfx_drawPixel(x0 + x, y0 + y, color);
		gfx_drawPixel(x0 - x, y0 + y, color);
		gfx_drawPixel(x0 + x, y0 - y, color);
		gfx_drawPixel(x0 - x, y0 - y, color);
		gfx_drawPixel(x0 + y, y0 + x, color);
		gfx_drawPixel(x0 - y, y0 + x, color);
		gfx_drawPixel(x0 + y, y0 - x, color);
		gfx_drawPixel(x0 - y, y0 - x, color);
	}
}

void gfx_drawCircleHelper( short x0, short y0, short r, u8 cornername,
		u8 color)
{
	short f     = 1 - r;
	short ddF_x = 1;
	short ddF_y = -2 * r;
	short x     = 0;
	short y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;
		if (cornername & 0x4)
		{
			gfx_drawPixel(x0 + x, y0 + y, color);
			gfx_drawPixel(x0 + y, y0 + x, color);
		}
		if (cornername & 0x2)
		{
			gfx_drawPixel(x0 + x, y0 - y, color);
			gfx_drawPixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8)
		{
			gfx_drawPixel(x0 - y, y0 + x, color);
			gfx_drawPixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1)
		{
			gfx_drawPixel(x0 - y, y0 - x, color);
			gfx_drawPixel(x0 - x, y0 - y, color);
		}
	}
}

void gfx_fillCircle(short x0, short y0, short r, u8 color)
{
	gfx_drawFastVLine(x0, y0-r, 2*r+1, color);
	gfx_fillCircleHelper(x0, y0, r, 3, 0, color);
}

// Used to do circles and roundrects
void gfx_fillCircleHelper(short x0, short y0, short r, u8 cornername,
		short delta, u8 color)
{
	short f     = 1 - r;
	short ddF_x = 1;
	short ddF_y = -2 * r;
	short x     = 0;
	short y     = r;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f     += ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;

		if (cornername & 0x1)
		{
			gfx_drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
			gfx_drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
		}
		if (cornername & 0x2)
		{
			gfx_drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
			gfx_drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
		}
	}
}

void gfx_drawTriangle(short x0, short y0, short x1, short y1, short x2,
		short y2, u8 color)
{
	gfx_drawLine(x0, y0, x1, y1, color);
	gfx_drawLine(x1, y1, x2, y2, color);
	gfx_drawLine(x2, y2, x0, y0, color);
}

void gfx_fillTriangle ( short x0, short y0, short x1, short y1,
		short x2, short y2, u8 color)
{
	short a, b, y, last;

	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1)
	{
		swap(y0, y1); swap(x0, x1);
	}
	if (y1 > y2)
	{
		swap(y2, y1); swap(x2, x1);
	}
	if (y0 > y1)
	{
		swap(y0, y1); swap(x0, x1);
	}

	if(y0 == y2)
	{ // Handle awkward all-on-same-line case as its own thing
		a = b = x0;
		if(x1 < a)      a = x1;
		else if(x1 > b) b = x1;
		if(x2 < a)      a = x2;
		else if(x2 > b) b = x2;
		gfx_drawFastHLine(a, y0, b-a+1, color);
		return;
	}

	short
	dx01 = x1 - x0,
	dy01 = y1 - y0,
	dx02 = x2 - x0,
	dy02 = y2 - y0,
	dx12 = x2 - x1,
	dy12 = y2 - y1;

	int sa = 0, sb = 0;

	// For upper part of triangle, find scanline crossings for segments
	// 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
	// is included here (and second loop will be skipped, avoiding a /0
	// error there), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// (flat-topped triangle).
	if(y1 == y2) last = y1;   // Include y1 scanline
	else         last = y1-1; // Skip it

	for(y=y0; y<=last; y++)
	{
		a   = x0 + sa / dy01;
		b   = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;
		/* longhand:
    	a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    	b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		 */
		if(a > b) swap(a,b);
		gfx_drawFastHLine(a, y, b-a+1, color);
	}

	// For lower part of triangle, find scanline crossings for segments
	// 0-2 and 1-2.  This loop is skipped if y1=y2.
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++)
	{
		a   = x1 + sa / dy12;
		b   = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;
		/* longhand:
    	a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    	b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
		 */
		if(a > b) swap(a,b);
		gfx_drawFastHLine(a, y, b-a+1, color);
	}
}

void gfx_drawRoundRect(short x, short y, short w, short h, short r, u8 color)
{
	// smarter version
	gfx_drawFastHLine(x+r  , y    , w-2*r, color); // Top
	gfx_drawFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
	gfx_drawFastVLine(x    , y+r  , h-2*r, color); // Left
	gfx_drawFastVLine(x+w-1, y+r  , h-2*r, color); // Right
	// draw four corners
	gfx_drawCircleHelper(x+r    , y+r    , r, 1, color);
	gfx_drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
	gfx_drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	gfx_drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}

void gfx_fillRoundRect(short x, short y, short w, short h, short r, u8 color)
{
	// smarter version
	gfx_fillRect(x+r, y, w-2*r, h, color);

	// draw four corners
	gfx_fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	gfx_fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}

// Draw a character
void gfx_drawChar(short x, short y, unsigned char c, u8 color, u8 bg, u8 size)
{
	u8 i = 0;
	u8 j = 0;

	if		((x >= WIDTH)           || // Clip right
			(y >= HEIGHT)           || // Clip bottom
			((x + 6 * size - 1) < 0) || // Clip left
			((y + 8 * size - 1) < 0))   // Clip top
		return;

	for (i=0; i<6; i++ )
	{
		u8 line;
		if (i == 5)
			line = 0x0;
		else
			line = pgm_read_byte(font+(c*5)+i);

		for (j = 0; j<8; j++)
		{
			if (line & 0x1)
			{
				if (size == 1) // default size
					gfx_drawPixel(x+i, y+j, color);

				else  // big size
					gfx_fillRect(x+(i*size), y+(j*size), size, size, color);

			} else if (bg != color)
			{

				if (size == 1) // default size
					gfx_drawPixel(x+i, y+j, bg);

				else  // big size
					gfx_fillRect(x+i*size, y+j*size, size, size, bg);

			}
			line >>= 1;
		}
	}
}

