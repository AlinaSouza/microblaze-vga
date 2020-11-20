#include <xbasic_types.h>
#include <xiomodule.h>
#include "bram.h"

// reference to mblaze IO Module
XIOModule* _io_mod_bram = NULL;

void init_bram(XIOModule* gpo1)
{
	_io_mod_bram = gpo1;
}

void write_4bit(u8 data, u16 addr)
{
	u32 toWrite = (WRITE_ENABLE | (addr & 0x3FFF) << 4 | (data & 0x0F));
	XIOModule_DiscreteWrite(_io_mod_bram, 1, toWrite);
	toWrite = (WRITE_DISABLE | (addr & 0x3FFF) << 4 | 0);
	XIOModule_DiscreteWrite(_io_mod_bram, 1, toWrite);
}

u8 read_4bit (u16 addr)
{
	u32 toWrite = (WRITE_DISABLE | (addr & 0x3FFF) << 4 | 0);
	XIOModule_DiscreteWrite(_io_mod_bram, 1, toWrite);
	u8 readData = XIOModule_DiscreteRead(_io_mod_bram, 1);
	return (readData & 0x0F);
}
