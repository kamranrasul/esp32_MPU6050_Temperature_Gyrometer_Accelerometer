// Original Code By:    Robbin Law
// Modified for MPU-6050: Kamran R.

#include <Arduino.h>
#include "sensor_readings.h"
#include "TFT_eSPI.h" // ESP32 Hardware-specific library
#include "settings.h" // The order is important!

// ************************** new code **************************
#include <Wire.h>

// I2C address of the MPU-6050
const int MPU_addr = 0x68;

// ************************** new code **************************

// tft is global to this file only
TFT_eSPI tft = TFT_eSPI();

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  // Setup the TFT
  tft.begin();
  tft.setRotation(2);
  tft.setTextColor(fg, bg);
  tft.fillScreen(bg);
  tft.setCursor(0, 0);
  tft.println("Hello!");
  tft.println("Starting MPU-6050 sensor...");
  delay(5000);

  // ************************** new code **************************

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  // ************************** new code **************************

  tft.fillScreen(bg);
}

void loop()
{
  tft.setCursor(50, 50);
  tft.println(millis());
  // passing the bme object by value
  // refresh_readings(bme);
  // Passing the bme and tft objects by reference
  //(a pointer: & means pass the address stored in the bme and tft variables).

  // ************************** new code **************************

  refresh_readings_mpu6050(&tft);

  // ************************** new code **************************
  delay(2000);
}