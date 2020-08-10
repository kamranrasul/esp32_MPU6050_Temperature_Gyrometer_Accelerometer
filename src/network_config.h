#include <Arduino.h>

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME  "kamranrasul"
#define IO_KEY       "aio_NAvk79i1OKqv0OFFAUotdxD5bskj"

// wifi credentials
#define WIFI_SSID       "Hidden_network"
#define WIFI_PASS       "pak.awan.pk"

#include "AdafruitIO_WiFi.h"   
// Beware, at the time of writting this, 
// the Adafruit library needs platform-espressif32 
// version 1.7.0, https://github.com/platformio/platform-espressif32/releases, specified in platform.io
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
