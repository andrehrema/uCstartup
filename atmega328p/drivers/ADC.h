#ifndef ADC_H
#define ADC_H

void configure_ADC();
void start_ADC();
void stop_ADC();
void next_channel();
int read_ADC();
int ready_ADC();
int final_channel();
int ADC_channel();

#endif
