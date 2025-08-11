/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "lcd.h"

/* Example code to drive a 16x2 LCD panel via a I2C bridge chip (e.g. PCF8574)

   NOTE: The panel must be capable of being driven at 3.3v NOT 5v. The Pico
   GPIO (and therefor I2C) cannot be used at 5v.

   You will need to use a level shifter on the I2C lines if you want to run the
   board at 5v, otherwise it will still work, but it will be dimmer than usual.

   Connections on Raspberry Pi Pico board, other boards may vary.

   GPIO 4 (pin 6)-> SDA on LCD bridge board
   GPIO 5 (pin 7)-> SCL on LCD bridge board
   3.3v (pin 36) -> VCC on LCD bridge board
   GND (pin 38)  -> GND on LCD bridge board
*/
// By default these LCD display drivers are on bus address 0x27
static int addr = 0x27;
// commands
const int LCD_CLEARDISPLAY = 0x01;
const int LCD_RETURNHOME = 0x02;
const int LCD_ENTRYMODESET = 0x04;
const int LCD_DISPLAYCONTROL = 0x08;
const int LCD_CURSORSHIFT = 0x10;
const int LCD_FUNCTIONSET = 0x20;
const int LCD_SETCGRAMADDR = 0x40;
const int LCD_SETDDRAMADDR = 0x80;

// flags for display entry mode
const int LCD_ENTRYSHIFTINCREMENT = 0x01;
const int LCD_ENTRYLEFT = 0x02;

// flags for display and cursor control
const int LCD_BLINKON = 0x01;
const int LCD_CURSORON = 0x02;
const int LCD_DISPLAYON = 0x04;

// flags for display and cursor shift
const int LCD_MOVERIGHT = 0x04;
const int LCD_DISPLAYMOVE = 0x08;

// flags for function set
const int LCD_5x10DOTS = 0x04;
const int LCD_2LINE = 0x08;
const int LCD_8BITMODE = 0x10;

// flag for backlight control
const int LCD_BACKLIGHT = 0x08;

const int LCD_ENABLE_BIT = 0x04;
/* Quick helper function for single byte transfers */
void i2c_write_byte(uint8_t val) {
    i2c_write_blocking(I2C_PORT, addr, &val, 1, false);
}

void lcd_toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
#define DELAY_US 600
    sleep_us(DELAY_US);
    i2c_write_byte(val | LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
}

// The display is sent a byte as two separate nibble transfers
void lcd_send_byte(uint8_t val, int mode) {
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void) {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

// go to location on LCD
void lcd_set_cursor(int line, int position) {
    int line_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    int val = 0x80 + line_offsets[line] + position;
    lcd_send_byte(val, LCD_COMMAND);
}

static void inline lcd_char(char val) {
    lcd_send_byte(val, LCD_CHARACTER);
}

void lcd_string(const char *s) {
    while (*s) {
        lcd_char(*s++);
    }
}

void lcd_init() {
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x02, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND);
    lcd_clear();
}

void lcd_update() {
    static int line0 = 0;
    static int line1 = 0;
    static int line2 = 1;
    static int line3 = 4;
    static int line0_forward = 1;
    static int line1_forward = 1;
    static int line2_forward = 1;
    static int line3_forward = 1;
    static uint8_t *hello = "Hello Somya!";
    static uint8_t *love = "I love you so much,";
    static uint8_t *friend = "you're my soulmate!";
    static uint8_t *signature = "Love, Alex Manak";

    lcd_clear();
        
    // line 0
    lcd_set_cursor(0, line0);
    if (line0_forward) {
        if (line0 < MAX_LINE0) {
            line0++;
        } else {
            line0--;
            line0_forward = 0;
        }
    } else {
        if (line0 > 0) {
            line0--;
        } else {
            line0++;
            line0_forward = 1;
        }
    }
    lcd_string(hello);

    // line 1
    lcd_set_cursor(1, line1);
    if (line1_forward) {
        if (line1 < MAX_LINE1) {
            line1++;
        } else {
            line1--;
            line1_forward = 0;
        }
    } else {
        if (line1 > 0) {
            line1--;
        } else {
            line1++;
            line1_forward = 1;
        }
    }
    lcd_string(love);

    // line 2
    lcd_set_cursor(2, line2);
    if (line2_forward) {
        if (line2 < MAX_LINE2) {
            line2++;
        } else {
            line2--;
            line2_forward = 0;
        }
    } else {
        if (line2 > 0) {
            line2--;
        } else {
            line2++;
            line2_forward = 1;
        }
    }
    lcd_string(friend);

    // line 3
    lcd_set_cursor(3, line3);
    if (line3_forward) {
        if (line3 < MAX_LINE3) {
            line3++;
        } else {
            line3--;
            line3_forward = 0;
        }
    } else {
        if (line3 > 0) {
            line3--;
        } else {
            line3++;
            line3_forward = 1;
        }
    }
    lcd_string(signature);
}