#include<avr/io.h>
#include<stdlib.h>
#include<string.h>

#include"USART.h"
#include<avr/interrupt.h>


volatile static volatile uint8_t all_data_sent;
volatile static uint8_t index_tx;
volatile static char buffer_tx[50];

ISR(USART_RX_vect){ // receiving ISR
        

	UCSR0B &= ~(1<<TXCIE0); //disabling TX interruption
	PORTB^=2;

        UCSR0B |= (1<<TXCIE0); //reabilitando instrução por transmissão
}

ISR(USART_TX_vect){ // transmitting IST

	if (buffer_tx[index_tx] == '!'){
		all_data_sent = SENT;
		index_tx = 0;
	}
	else{
		index_tx++;
		all_data_sent = SENDING;
	}
}


void configure_USART(){

        //one stop bit
        UBRR0H = (uint8_t) ((PRESCALER >> 8) & 0x0F); //baud rate = 9600
        UBRR0L = (uint8_t) PRESCALER; // baud rate = 9600

        UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0); //enabling RX and TX, enabling RX and TX interruption
        UCSR0C |= (0x26); // even parity, 8 data bits

	all_data_sent = NOTHING_TO_SEND; //buffer_tx empty
	index_tx = 0; //initiating the index of tx
}

char * read_USART(){

	return &value;
}

void USART_write(char *frame){ //write in usart tx buffer
	
	strcpy(buffer_tx, frame); //coping the frame to buffer_tx 

	index_tx = 0;
	UDR0 = buffer_tx[index_tx];
	
}

void next_USART(){ //send next buffer's character

	UDR0 = buffer_tx[index_tx];
}

uint8_t all_sent(){ //all buffer has been sent
	return all_data_sent;
}
