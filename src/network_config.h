#include <Arduino.h>

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.

#define IO_USERNAME  "YOUR USERNAME"
#define IO_KEY       "YOUR IO KEY"

// wifi credentials
#define WIFI_SSID       "YOUR SSID"
#define WIFI_PASS       "YOUR PASSWORD"

#include "AdafruitIO_WiFi.h"   
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
