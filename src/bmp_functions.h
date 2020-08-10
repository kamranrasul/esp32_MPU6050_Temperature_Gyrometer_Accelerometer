#include <Arduino.h>
#include "settings.h"
#include "TFT_eSPI.h"     // ESP32 Hardware-specific library
#include "FS.h"

void drawBmp(const char *filename, int16_t x, int16_t y, TFT_eSPI* tft);
uint16_t read16(fs::File &f);
uint32_t read32(fs::File &f);