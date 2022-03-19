/*

SSD1306 - Screen module

Copyright (C) 2019 by Roel van Wanrooy (www.connectix.nl)


This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <Wire.h>
#include "SSD1306Wire.h"
#include "OLEDDisplay.h"
#include "images.h"
#include "fonts.h"

#define SCREEN_HEADER_HEIGHT    14

SSD1306Wire * display;
uint8_t _screen_line = SCREEN_HEADER_HEIGHT - 1;

void _screen_header() {
    char buffer[20];

    // Message count
    snprintf(buffer, sizeof(buffer), "#%03d", get_count() % 1000);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(0, 2, buffer);

//  RELAIS STATUS
  if (relais_on == true)
  {
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(65, 2, ("RELAIS ON"));
  }
  else
  {
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(65, 2, ("RELAIS OFF"));
  }

}

void screen_show_logo() {
    uint8_t x = (display->getWidth() - TTN_IMAGE_WIDTH) / 2;
    uint8_t y = SCREEN_HEADER_HEIGHT + (display->getHeight() - SCREEN_HEADER_HEIGHT - TTN_IMAGE_HEIGHT) / 2 + 1;
    display->drawXbm(x, y, TTN_IMAGE_WIDTH, TTN_IMAGE_HEIGHT, TTN_IMAGE);
}

void screen_off() {
    display->displayOff();
}

void screen_on() {
    display->displayOn();
}

void screen_clear() {
    display->clear();
}

void screen_print(const char * text, uint8_t x, uint8_t y, uint8_t alignment) {
    DEBUG_MSG(text);
    display->setTextAlignment((OLEDDISPLAY_TEXT_ALIGNMENT) alignment);
    display->drawString(x, y, text);
}

void screen_print(const char * text, uint8_t x, uint8_t y) {
    screen_print(text, x, y, TEXT_ALIGN_LEFT);
}

void screen_print(const char * text) {
    display->print(text);
    if (_screen_line + 8 > display->getHeight()) {
        // scroll
    }
    _screen_line += 8;
    screen_loop();
}

void screen_update() {
    display->display();
}

void screen_setup() {
    // Display instance
    display = new SSD1306Wire(SSD1306_ADDRESS, I2C_SDA, I2C_SCL);
    display->init();
    display->flipScreenVertically();
    display->setFont(Custom_ArialMT_Plain_10);

    // Scroll buffer
    display->setLogBuffer(5, 30);
}

void screen_loop() {
    display->clear();
    _screen_header();
    display->drawLogBuffer(0, SCREEN_HEADER_HEIGHT);
    display->display();
}
