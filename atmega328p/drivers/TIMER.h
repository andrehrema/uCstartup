#ifndef TIMER_H
#define TIMER_H

#define CLOCK_DIVIDER 128
#define FINAL_CLOCK (2000000/clock_divider)
#define OCR_VALUE 125
#define TIMER_COUNTER_VALUE (FINAL_CLOCK/OCR_VALUE)

	void configure_timer();

#endif
