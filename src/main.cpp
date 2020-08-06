// Original Code By:    Robbin Law
// Modified for MPU-6050: Kamran R.

#include <Arduino.h>
#include "sensor_readings.h"
#include "TFT_eSPI.h" // ESP32 Hardware-specific library
#include "settings.h" // The order is important!

#include <Wire.h> // for I2C generic devices

#define LED_ONBOARD_PIN 2

// bme is global to this file only
Adafruit_BME280 bme;
// tft is global to this file only
TFT_eSPI tft = TFT_eSPI();

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

// LED
struct Led
{
  uint8_t pin;
  bool on;

  void update()
  {
    digitalWrite(pin, on ? HIGH : LOW);
  }
};

// Global Variables
Led onboard_led = {LED_ONBOARD_PIN, false};

void initSPIFFS()
{
  if (!SPIFFS.begin())
  {
    Serial.println("Cannot mount SPIFFS volume...");
    while (1)
      ; // infinite loop
  }
  else
  {
    Serial.println("SPIFFS volume mounted properly");
  }
}

// ************************** new code **************************

// I2C address of the MPU-6050
const int MPU_addr = 0x68;

// sensor flags
bool foundBME = false;
bool foundMPU6050 = false;

// ************************** new code **************************

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
  tft.println("Searching for the sensor...");
  delay(5000);

  // ************************** new code **************************

  foundBME = bme.begin(0x76);

  if (foundBME)
  {
    Serial.println("Found a valid BME280 sensor");
  }
  else
  {
    Wire.begin();
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);    // set to zero (wakes up the MPU-6050)
    if (Wire.endTransmission(true) == 0)
    {
      Serial.println("Found a valid MPU6050 sensor");
      foundMPU6050 = true;
    }
  }

  if (!foundBME && !foundMPU6050)
  {
    Serial.println("Could not find a valid sensor, check wiring!");
    while (1)
      ; // Infinite loop
  }

  delay(2000);

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
  if (foundBME)
  {
    refresh_readings_bme280(&bme, &tft);
  }
  delay(2000);
  if (foundMPU6050)
  {
    refresh_readings_mpu6050(&tft);
  }
  // ************************** new code **************************
  delay(2000);
}