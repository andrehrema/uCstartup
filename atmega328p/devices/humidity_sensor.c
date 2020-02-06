#include<stdint.h>


void initiate_sensor(humidity *sensor, char *owner, int PIN_owner, int PIN){

	sensor->owner = owner;
	sensor->PIN_owner = PIN_owner;
	sensor->PIN = PIN;

	for (int i=0; i<SENSOR_BUFF_LENGTH; i++){
	
		sensor->value[i] = 0;
	}
	sensor->mean = 0;
	sensor->standard_deviation = 0;
}
