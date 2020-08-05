#include <Arduino.h>
#include <Wire.h>
#include "sensor_readings.h"

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
void refresh_readings_mpu6050(TFT_eSPI *tft)
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
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

  Serial.println("Accelerometer Values: \n");
  Serial.print("  AcX: ");
  Serial.println(AcX);
  Serial.print("\n  AcY: ");
  Serial.println(AcY);
  Serial.print("\n  AcZ: ");
  Serial.println(AcZ);
  Serial.print("\nTemperature: ");
  Serial.println(temp);
  Serial.print("\nGyroscope Values: \n");
  Serial.print("  GyX: ");
  Serial.println(GyX);
  Serial.print("\n  GyY: ");
  Serial.println(GyY);
  Serial.print("\n  GyZ: ");
  Serial.println(GyZ);
  Serial.print("\n");

   // If you set this, the TFT will not work!!!
  //digitalWrite(LED_BUILTIN, HIGH);

  uint16_t bg = TFT_BLACK;
  uint16_t fg = TFT_WHITE;

  // the -> symbol means to de-reference the pointer.
  tft->setCursor(5, 5);
  tft->setTextColor(fg, bg);
  tft->println("Right now...");

  tft->setTextColor(TFT_YELLOW, bg);

  // Temperature
  tft->fillRect(5, 50, 140, 30, bg);
  tft->setCursor(5, 50);
  tft->print(temp);
  tft->println(" degree C");

  // Accelerometer and Gyroscope
  tft->fillRect(5, 90, 130, 30, bg);
  tft->setCursor(5, 90);

  tft->println("Accelerometer Values: \n");
  tft->print("  AcX: ");
  tft->println(AcX);

  tft->print("\n  AcY: ");
  tft->println(AcY);

  tft->print("\n  AcZ: ");
  tft->println(AcZ);

  tft->println("\nGyroscope Values: \n");
  tft->print("  GyX: ");
  tft->println(GyX);

  tft->print("\n  GyY: ");
  tft->println(GyY);

  tft->print("\n  GyZ: ");
  tft->println(GyZ);

  //digitalWrite(LED_BUILTIN, LOW);
  Serial.println("-----v3----");
}

// ************************** new code **************************
