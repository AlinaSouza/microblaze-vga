#ifndef BRAM_H_
#define BRAM_H_

#define ADDR_HI 16383
#define ADDR_LO 0

#define WRITE_ENABLE (1<<18)
#define WRITE_DISABLE 0

void init_bram(XIOModule* gpo1);
void write_4bit(u8 data, u16 addr);
u8 read_4bit (u16 addr);

#endif /* BRAM_H_ */
