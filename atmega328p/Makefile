CC=avr-gcc

CFLAGS=-Wall -g -Og -mmcu=atmega328p

USART=drivers/USART
TIMER=drivers/TIMER
ADC=drivers/ADC

SENSOR=devices/humidity_sensor

USART_DEPS=drivers/UART.h
TIMER_DEPS=drivers/TIMER.h
ADC_DEPS=drivers/ADC.h

SENSOR_DEPS=devices/humidity_sensor.h

OBJ=main

$(OBJ).hex: $(OBJ).bin
	avr-objcopy -j .text -j .data -O ihex $^ $@

$(OBJ).bin: $(OBJ).o $(ADC).o $(USART).o $(TIMER).o  $(SENSOR).o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ).o: $(OBJ).c $(TIMER_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(SENSOR).o: $(SENSOR).c $(SENSOR_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(USART).o: $(USART).c $(UART_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TIMER).o: $(TIMER).c $(TIMER_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(ADC).o: $(ADC).c $(ADC_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@


clean: $(OBJ).o
	find . -name '*.o' -delete
	find . -name '*.bin' -delete
	find . -name '*.hex' -delete
	find . -name '*.gch' -delete

grava: $(OBJ).hex
	avrdude -p m328p -c avrispmkII -U lfuse:w:0xFF:m -U flash:w:$<:i -F -P usb
