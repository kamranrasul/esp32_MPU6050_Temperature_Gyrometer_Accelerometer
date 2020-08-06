#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <TFT_eSPI.h>
#define SEALEVELPRESSURE_HPA (1013.25)

void refresh_readings_bme280(Adafruit_BME280 *bme, TFT_eSPI *tft);

// ************************** new code **************************

void refresh_readings_mpu6050(TFT_eSPI *tft);

// ************************** new code **************************

#endif
