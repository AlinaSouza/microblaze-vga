#ifndef FIT_TIMER_H_
#define FIT_TIMER_H_

void init_fit_timers(XIOModule* gpo1);
void us_tick(void* ref);
void ms_tick(void* ref);
void delay_s(int s);
void delay_ms(int ms);
void delay_20us(int us);

#endif /* FIT_TIMER_H_ */
