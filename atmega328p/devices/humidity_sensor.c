#include<stdint.h>


void initiate_sensor(sensor *mapped_sensor, char *owner, int PIN_owner, int PIN){

	mapped_sensor->owner = owner;
	mapped_sensor->PIN_owner = PIN_owner;
	mapped_sensor->PIN = PIN;

	for (int i=0; i<SENSOR_BUFF_LENGTH; i++){
	
		mapped_sensor->value[i] = 0;
	}
	mapped_sensor->mean = 0.0;
	mapped_sensor->standard_deviation = 0.0;
}

void add_data_sensor(sensor *mapped_sensor, int16_t *read_value){
	
	mapped_sensor->index_buf++;

	if (mapped_sensor->index > SENSOR_BUFF_LENGTH){
		mapped_sensor->index = 0;
	}
	float lower_limit = mapped_sensor->mean - 0.1* mapped_sensor->std_dev;
	float upper_limit = mapped_sensor->mean + 0.1* mapped_sensor->std_dev;
	if((*read_value > upper_limit) || (*read_value < lower_limit))
		mapped_sensor->buffer[mapped_sensor->index_buf] = *read_value;
	else 
		mapped_sensor->state = STABLE;

}

void calc_std_dev(sensor *mapped_sensor){

	float std_dev=0.0;
	
	for (int i=0; i<SENSOR_BUFF_LEN; i++){
		std_dev += pow((mapped_sensor->mean - mapped_sensor->buffer[i]),2); // (u - xi) ^2
	}

	mapped_sensor->std_dev = sqrt(std_dev / SENSOR_BUFF_LEN);
}

void calc_mean(mapped_sensor *sensor){
	mapped_sensor->mean=0.0;
	for (int i=0; i<SENSOR_BUFF_LEN;i++){
		mapped_sensor->mean += mapped_sensor->buffer[i];
	}
	mapped_sensor->mean/=SENSOR_BUFF_LEN;
}

