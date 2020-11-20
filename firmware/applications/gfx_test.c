#include <math.h>
#include <stdlib.h>
#include <xiomodule.h>
#include "platform.h"
#include "bram.h"
#include "gfx.h"

#define MAX_PIXELS (4096*4)
#define BLACK  0
#define RED    1
#define GREEN  2
#define YELLOW 3
#define BLUE   4
#define PURPLE 5
#define WHITE  7
#define CYAN   6

XIOModule gpo1;

void print(char *str);

void blank_screen()
{
	u16 addr = 0;
	for (addr = 0; addr < MAX_PIXELS; addr++)
		write_4bit(BLACK, addr);
}

//void draw_random_line()
//{
//	short x0 = rand() % 128;
//	short y0 = rand() % 128;
//	short x1 = rand() % 128;
//	short y1 = rand() % 128;
//	u8 color = rand() % 8;
//
//	gfx_drawLine(x0, y0, x1, y1, color);
//}

//void draw_random_rect()
//{
//	short x0 = rand() % 128;
//	short y0 = rand() % 128;
//	short w  = rand() % 128;
//	short h  = rand() % 128;
//	u8 color = rand() % 8;
//
//	gfx_drawRect(x0, y0, w, h, color);
//}

//void draw_random_fill_rect()
//{
//	short x0 = rand() % 128;
//	short y0 = rand() % 128;
//	short w  = rand() % 128;
//	short h  = rand() % 128;
//	u8 color = rand() % 8;
//
//	gfx_fillRect(x0, y0, w, h, color);
//}

//void draw_circles()
//{
//	short x = 63;
//	short y = 63;
//	short r = 3;
//	int   i = 0;
//
//	for (i = 0; i < 30; i++)
//	{
//		gfx_drawCircle(x, y, r+(i*2), (i%7)+1);
//	}
//}

void fill_circles()
{
	short x = 63;
	short y = 63;
	short r = 3;
	int   i = 0;

	for (i = 29; i >= 0; i--)
	{
		gfx_fillCircle(x, y, r+(i*2), (i%7)+1);
	}
}

//void draw_triangles()
//{
//	short x0 = rand() % 128;
//	short x1 = rand() % 128;
//	short x2 = rand() % 128;
//	short y0 = rand() % 128;
//	short y1 = rand() % 128;
//	short y2 = rand() % 128;
//	u8 color = rand() % 8;
//	gfx_drawTriangle(x0, y0, x1, y1, x2, y2, color);
//}

void fill_triangles()
{
	short x0 = rand() % 128;
	short x1 = rand() % 128;
	short x2 = rand() % 128;
	short y0 = rand() % 128;
	short y1 = rand() % 128;
	short y2 = rand() % 128;
	u8 color = rand() % 8;
	gfx_fillTriangle(x0, y0, x1, y1, x2, y2, color);
}

//void draw_roundRect()
//{
//	short x0 = rand() % 128;
//	short y0 = rand() % 128;
//	short w  = rand() % 128;
//	short h  = rand() % 128;
//	short r  = rand() % 10;
//	u8 color = rand() % 8;
//
//	gfx_drawRoundRect(x0, y0, w, h, r, color);
//}

//void fill_roundRect()
//{
//	short x0 = rand() % 128;
//	short y0 = rand() % 128;
//	short w  = rand() % 128;
//	short h  = rand() % 128;
//	short r  = rand() % 10;
//	u8 color = rand() % 8;
//
//	gfx_fillRoundRect(x0, y0, w, h, r, color);
//}

int main()
{
    init_platform();
    XIOModule_Initialize(&gpo1, XPAR_IOMODULE_0_DEVICE_ID);
    XIOModule_Start(&gpo1);
    init_bram(&gpo1);
    blank_screen();

    while(1)
    {
    	fill_triangles();
    }

    cleanup_platform();
    return 0;
}
