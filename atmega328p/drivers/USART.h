#ifndef USART_H
#define USART_H
#define F_CPU 2000000
#define BAUDRATE 9600
#define PRESCALER ((F_CPU / (BAUDRATE * 16UL)) -1)


#define SENT 1
#define NOTHING_TO_SEND 1
#define SENDING 0

#define N_SENSORS 3
#define SENSOR_BUFF_LENGTH 4
#define OK 1
#define STABLE 2
#define NOK 3


	void configure_USART(); // USART configuration
	char * read_USART(); // reading data from USART
	void send_USART (char *frame); //sending data
	uint8_t	all_sent();
#endif
