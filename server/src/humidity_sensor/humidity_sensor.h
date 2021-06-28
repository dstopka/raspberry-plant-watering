#ifndef _HUMIDITY_SENSOR_H_
#define _HUMIDITY_SENSOR_H_

#define SENSOR_ADDR 0x48
#define WET_VAL 8506
#define DRY_VAL 32767

void measure_humidity(const int fd);
void init_humidity_sensor(const int fd);
double get_humidity();

#endif