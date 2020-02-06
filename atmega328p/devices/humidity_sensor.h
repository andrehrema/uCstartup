#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#define N_SENSORS 2
#define SENSOR_BUFF_LENGTH 10
	typedef struct sensor_humidity humidity;

	struct sensor_humidity{
		char owner_name[15];
		uint8_t PIN_owner;
		int16_t PIN_sensor;
		int16_t buffer[SENSOR_BUFF_LENGTH];
		float mean;
		float standard_deviation;
	}

	void initiate_sensor(humidity *sensor, char *owner, int PIN_owner, int PIN);

#endif
