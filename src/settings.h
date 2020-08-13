#ifndef SETTINGS_H
#define SETTINGS_H
#include "Arduino.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "SPIFFS.h"
#include "FS.h"
#include <TFT_eSPI.h>
#include "AdafruitIO_WiFi.h"
#include "ezTime.h"
#include "AdafruitIO_Feed.h"
#include "EEPROM.h"
//#include "aux_functions.h"      // Helpful functions
//#include "EEPROM.h"
//#include "esp_system.h"  // To implement the watchdog
//#include "mqtt_controller.h"
// uint16_t bg = TFT_BLACK;
// uint16_t fg = TFT_WHITE;
//#define LED_PIN            17
//#define IFTTT_PIN          16
#define EEPROM_SIZE 4
// We'll use 1 byte in the EEPROM to store the max number of POSTs
// MQTT posts where completed in the current power cycle
//#define EEPROM_SIZE 1

#endif

#ifdef DEBUGLOG
#define DEBUGPRINT(x) Serial.print(x)
#define DEBUGPRINTDEC(x) Serial.print(x, DEC)
#define DEBUGPRINTLN(x) Serial.println(x)
#else
#define DEBUGPRINT(x)
#define DEBUGPRINTDEC(x)
#define DEBUGPRINTLN(x)
#endif