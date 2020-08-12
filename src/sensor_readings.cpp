#include <Arduino.h>
#include <Wire.h>
#include "sensor_readings.h"
#include "AdafruitIO_Feed.h"

// Passing the bme and tft objects by reference
// the * means that the parameter called bme will contain an address to the object of type Adafruit_BME280
// For those students using the MCU-6050 this code inside "refresh_readings"
// will be completely different than for the Adafruit_BME280.
void refresh_readings_bme280(Adafruit_BME280 *bme,
                             TFT_eSPI *tft,
                             AdafruitIO_Feed *temp,
                             AdafruitIO_Feed *hum,
                             AdafruitIO_Feed *bar,
                             AdafruitIO_Feed *alt)
{
  float f_temperature;
  float f_humidity;
  float f_pressure;
  float f_altitude;

  // If you set this, the TFT will not work!!!
  //digitalWrite(LED_BUILTIN, HIGH);

  uint16_t bg = TFT_BLACK;
  uint16_t fg = TFT_WHITE;

  // the -> symbol means to de-reference the pointer.
  tft->setCursor(5, 5);
  tft->setTextColor(fg, bg);
  // Create TTF fonts using instructions at https://pages.uoregon.edu/park/Processing/process5.html
  tft->loadFont("SansSerif-36");
  tft->println("Right now...");

  f_temperature = bme->readTemperature();
  f_humidity = bme->readHumidity();
  f_pressure = bme->readPressure() / 100.0F;
  f_altitude = bme->readAltitude(SEALEVELPRESSURE_HPA);

  tft->setTextColor(TFT_YELLOW, bg);

  // Temperature
  Serial.print(f_temperature);
  Serial.println(" °C");
  tft->fillRect(5, 50, 140, 30, bg);
  tft->setCursor(5, 50);
  tft->print(" Temperature: ");
  tft->print(f_temperature);
  tft->println(" °C");

  // Humidity
  Serial.print(f_humidity);
  Serial.println(" %");
  tft->fillRect(5, 90, 130, 30, bg);
  tft->setCursor(5, 90);
  tft->print(" Humidity:    ");
  tft->print(f_humidity);
  tft->println(" %");

  // Pressure
  Serial.print(f_pressure);
  Serial.println(" hPa");
  tft->fillRect(5, 130, 200, 30, bg);
  tft->setCursor(5, 130);
  tft->print(" Pressure:    ");
  tft->print(f_pressure);
  tft->println(" hPa");

  // Appx altitude
  Serial.print(f_altitude);
  Serial.println(" m");
  tft->fillRect(5, 170, 200, 30, bg);
  tft->setCursor(5, 170);
  tft->print(" Altitude:    ");
  tft->print(f_altitude);
  tft->println(" m");

  // Send data to Adafruit.IO
  temp->save(f_temperature);
  hum->save(f_humidity);
  bar->save(f_pressure);
  alt->save(f_altitude);

  //digitalWrite(LED_BUILTIN, LOW);
  Serial.println("-----v3----");
}

// ************************** new code **************************

// I2C address of the MPU-6050
const int MPU_addr = 0x68;

// variable for storing the register Tmp
int16_t Tmp;
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

// using for conversion from raw to degree C
float temp;

// Passing the bme and tft objects by reference
// the * means that the parameter called bme will contain an address to the object of type Adafruit_BME280
void refresh_readings_mpu6050(TFT_eSPI *tft,
                              AdafruitIO_Feed *temper,
                              AdafruitIO_Feed *acx,
                              AdafruitIO_Feed *acy,
                              AdafruitIO_Feed *acz,
                              AdafruitIO_Feed *gyx,
                              AdafruitIO_Feed *gyy,
                              AdafruitIO_Feed *gyz)
{
  // If you set this, the TFT will not work!!!
  //digitalWrite(LED_BUILTIN, HIGH);

  uint16_t bg = TFT_BLACK;
  uint16_t fg = TFT_WHITE;

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, 1); // request a total of 14 registers

  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  // converting to from raw to engineering Tmp
  temp = Tmp / 340.0 + 36.53;

  // displaying on the serial output
  Serial.printf("Temperature: %.2f °C or %.2f °F", temp, (temp * 1.8) + 32);
  Serial.println();

  Serial.println("\nAccelerometer Values:");
  Serial.print("  AcX: ");
  Serial.println(AcX);
  Serial.print("  AcY: ");
  Serial.println(AcY);
  Serial.print("  AcZ: ");
  Serial.println(AcZ);

  Serial.print("\nGyroscope Values:\n");
  Serial.print("  GyX: ");
  Serial.println(GyX);
  Serial.print("  GyY: ");
  Serial.println(GyY);
  Serial.print("  GyZ: ");
  Serial.println(GyZ);

  // the -> symbol means to de-reference the pointer.
  tft->setCursor(5, 5);
  tft->setTextColor(fg, bg);
  tft->loadFont("NotoSansBold14");
  tft->println("Right now...");
  tft->setTextColor(TFT_YELLOW, bg);

  // Temperature
  tft->fillRect(5, 50, 200, 30, bg);
  tft->setCursor(5, 50);
  tft->print(temp);
  tft->println(" degree C");

  // Accelerometer and Gyroscope
  tft->fillRect(5, 90, 200, 30, bg);
  tft->setCursor(5, 90);

  tft->println("Accelerometer Values:");
  tft->fillRect(5, 120, 200, 30, bg);
  tft->print("  AcX: ");
  tft->println(AcX);

  tft->fillRect(5, 160, 200, 30, bg);
  tft->print("  AcY: ");
  tft->println(AcY);

  tft->fillRect(5, 190, 200, 30, bg);
  tft->print("  AcZ: ");
  tft->println(AcZ);

  tft->fillRect(5, 220, 200, 30, bg);
  tft->println("Gyroscope Values:");
  tft->print("  GyX: ");
  tft->println(GyX);

  tft->fillRect(5, 250, 200, 30, bg);
  tft->print("  GyY: ");
  tft->println(GyY);

  tft->fillRect(5, 280, 200, 200, bg);
  tft->print("  GyZ: ");
  tft->println(GyZ);

  //Send data to Adafruit.IO
  temper->save(temp);
  acx->save(AcX);
  acy->save(AcY);
  acz->save(AcZ);
  gyx->save(GyX);
  gyy->save(GyY);
  gyz->save(GyZ);

  Serial.println("-----v1----");
}

// ************************** new code **************************
