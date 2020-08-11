#include <Arduino.h>
#include "sensor_readings.h"
#include "SPIFFS.h"
#include "settings.h" // The order is important!
#include "bmp_functions.h"
#include "TaskScheduler.h"
#include "WiFi.h"
#include "network_config.h"
#include <Wire.h>

void sensor_readings_update();
void clock_update();

// bme is global to this file only
Adafruit_BME280 bme;
// tft is global to this file only
TFT_eSPI tft = TFT_eSPI();
// Setup the clock

Timezone edmontonTZ;

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

// Setup tasks for the task scheduler
// The third argument taks a pointer to a function, but cannot have parameters.
Task t1_bme280(2000, TASK_FOREVER, &sensor_readings_update);
Task t2_clock(1000, TASK_FOREVER, &clock_update);

// Create the scheduler
Scheduler runner;

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
  Serial.begin(9600);
  initSPIFFS();

  // Setup the TFT
  tft.begin();
  tft.setRotation(3);
  tft.loadFont("NotoSansBold20");
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
  // ************************** new code **************************

  // Connect to Wifi
  io.connect();

  // Setup the clock
  waitForSync();

  // setting the time zone
  edmontonTZ.setLocation("America/Edmonton");

  // Start the task scheduler
  runner.init();

  // Add the task to the scheduler
  runner.addTask(t1_bme280);
  runner.addTask(t2_clock);
  
  // Enable the task
  t1_bme280.enable();
  t2_clock.enable();

  tft.fillScreen(bg);
  drawBmp("/te.bmp", 160, 198, &tft);
}

void loop()
{
  // Execute the scheduler runner
  runner.execute();
}

void sensor_readings_update()
{
  // ************************** new code **************************
  if (foundBME)
  {
    refresh_readings_bme280(&bme, &tft);
  }
  if (foundMPU6050)
  {
    refresh_readings_mpu6050(&tft);
  }
  // ************************** new code **************************
}

void clock_update()
{
  refresh_clock(&tft, &edmontonTZ);
}