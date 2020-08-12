#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <TFT_eSPI.h>
#include "AdafruitIO_Feed.h"
#define SEALEVELPRESSURE_HPA (1013.25)

void refresh_readings_bme280(Adafruit_BME280 *bme,
                             TFT_eSPI *tft,
                             AdafruitIO_Feed *temp,
                             AdafruitIO_Feed *hum,
                             AdafruitIO_Feed *bar,
                             AdafruitIO_Feed *alt);

// ************************** new code **************************

void refresh_readings_mpu6050(TFT_eSPI *tft,
                              AdafruitIO_Feed *temp,
                              AdafruitIO_Feed *acx,
                              AdafruitIO_Feed *acy,
                              AdafruitIO_Feed *acz,
                              AdafruitIO_Feed *gyx,
                              AdafruitIO_Feed *gyy,
                              AdafruitIO_Feed *gyz);

// ************************** new code **************************

#endif
