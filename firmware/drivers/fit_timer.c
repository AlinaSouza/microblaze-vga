#include <xbasic_types.h>
#include <xiomodule.h>
#include "fit_timer.h"

volatile u16 _us_ct = 0;
volatile u8 _us_flag = 1;

volatile u16 _ms_ct = 0;
volatile u8 _ms_flag = 0;

void init_fit_timers(XIOModule* gpo1)
{
   // register primary interrupt handler for the IO driver.
   microblaze_register_handler(XIOModule_DeviceInterruptHandler, XPAR_IOMODULE_0_DEVICE_ID);

   // enable interrupts
   microblaze_enable_interrupts();

   // initialize IO driver instance
   XIOModule_Initialize(gpo1, XPAR_IOMODULE_0_DEVICE_ID);

   // registers a user application interrupt handler to the FIT1 interrupt
   XIOModule_Connect(gpo1, XIN_IOMODULE_FIT_1_INTERRUPT_INTR, ms_tick, NULL);

   // registers a user application interrupt handler to the FIT2 interrupt
   XIOModule_Connect(gpo1, XIN_IOMODULE_FIT_2_INTERRUPT_INTR, us_tick, NULL);

   // Start the IO module
   XIOModule_Start(gpo1);

   // enable the FIT1 interrupt source
   XIOModule_Enable(gpo1,XIN_IOMODULE_FIT_1_INTERRUPT_INTR);

   // enable the FIT2 interrupt source
   XIOModule_Enable(gpo1,XIN_IOMODULE_FIT_2_INTERRUPT_INTR);
}

void us_tick(void* ref)
{
	if (_us_flag)
		_us_ct++;
}

void ms_tick(void* ref)
{
	if (_ms_flag)
		_ms_ct++;
}

void delay_s(int s)
{
	delay_ms(1000*s);
}

void delay_ms(int ms)
{
	_ms_flag = 1;
	while (_ms_ct != ms ) {}
	_ms_flag = 0;
	_ms_ct   = 0;
}

void delay_20us(int us)
{
	_us_flag = 1;
	while (_us_ct != us ) {}
	_us_flag = 0;
	_us_ct   = 0;
}
