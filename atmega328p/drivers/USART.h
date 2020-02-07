#ifndef USART_H
#define USART_H

#include<stdint.h>

#define F_CPU 2000000
#define BAUDRATE 9600
#define PRESCALER ((F_CPU / (BAUDRATE * 16UL)) -1)

#define SENT 1
#define NOTHING_TO_SEND 1
#define SENDING 0

	
	typedef struct buffer_usart usart_buff;

	static volatile usart_buff usart_buff_rx;
	static volatile usart_buff usart_buff_tx;


	void configure_USART(); // USART configuration
	char * read_USART(); // reading data from USART
	void send_USART (char *frame); //sending data
	uint8_t	all_sent();
#endif
