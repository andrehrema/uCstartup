#ifndef HUMIDITY_SENSOR_H
#define HUMIDITY_SENSOR_H

#define N_SENSORS 2
#define SENSOR_BUFF_LENGTH 4
#define OK 1
#define STABLE 2
#define NOK 3
	typedef struct sensor_map sensor;

	struct sensor_map{
		char owner_name[15];
		uint8_t PIN_owner;
		int16_t PIN_sensor;
		
		int16_t buffer[SENSOR_BUFF_LENGTH];
		
		int8_t index_buf;
		
		float mean;
		float std_dev;

		int8_t state;
	}

	void initiate_sensor(sensor *mapped_sensor, char *owner, int PIN_owner, int PIN);
	void add_data_sensor(sensor *mapped_sensor, int* read_value);
	void calc_std_dev(sensor *mapped_sensor);
	void calc_mean(sensor *mapped_sensor);

#endif
