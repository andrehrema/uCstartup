#ifndef USART_H
#define USART_H


	void configure_USART(); // USART configuration
	char * read_USART(); // reading data from USART
	void send_USART (char *frame); //sending data
	uint8_t	all_sent();
#endif
