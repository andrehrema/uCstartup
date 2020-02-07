CC=avr-gcc

CFLAGS=-

USART=drivers/USART
TIMER=driver/TIMER
ADC=driver/ADC

SENSOR=devices/humidity_sensor

USART_DEPS=driver/UART.h
TIMER_DEPS=driver/TIMER.h
ADC_DEPS=driver/ADC.h

SENSOR_DEPS=devices/humidity_sensor.h

OBJ=main

$(OBJ).hex: $(OBJ).bin
	avr-objcopy -j .text -j .data -O ihex $^ $@

$(OBJ).bin: $(OBJ) $(USART).o $(TIMER.o) $(ADC).o $(SENSOR).o
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ).o: $(OBJ).c
	$(CC) $(CFLAGS) -c $< -o $@

$(SENSOR).o = $(SENSOR).c $(SENSOR_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(USART).o = $(USART).c $(UART_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@


$(TIMER).o = $(TIMER).o $(TIMER_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(ADC).o = $(ADC).o $(ADC_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@


clean: $(OBJ)
	find . -name '*.o' -delete
	find . -name '*.bin' -delete
	find . -name '*.hex' -delete
	find . -name '*.gch' -delete

grava: $(OBJ).hex
	avrdude -p m328p -c avrispmkII -U lfuse:w:0xFF:m -U flash:w:$<:i -F -P usb
