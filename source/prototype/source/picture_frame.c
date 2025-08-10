/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/binary_info.h"


#ifndef LED_DELAY_MS
#define LED_DELAY_MS 500
#endif
/*
#define I2C_PORT    i2c0
#define I2C_SDA     4
#define I2C_SCL     5
#define LCD_ADDR       0x27  // Change to your LCD’s I2C address
#define LCD_BACKLIGHT   0x08
#define LCD_ENABLE      0x04
#define LCD_COMMAND     0x00
#define LCD_CHAR        0x01
#define LCD_REG_SEL     0x01
#define LCD_ENTRY_LEFT  0x02
#define LCD_ENTRY_RIGHT 0x00
#define LCD_ENTRY_SHIFT_INC 0x01
#define LCD_ENTRY_SHIFT_DEC 0x00
#define LCD_DISPLAY_ON      0x04
#define LCD_CURSOR_ON       0x02
#define LCD_CURSOR_OFF      0x00
#define LCD_BLINK_ON        0x01
#define LCD_BLINK_OFF       0x00
#define LCD_MODE_8BIT       0x10
#define LCD_MODE_4BIT       0x00
#define LCD_LINE_1          0x00
#define LCD_LINE_2          0x08
#define LCD_DOTS_5x10       0x04
#define LCD_DOTS_5x8        0x00
#define LCD_ENTRY_MODE_SET  0x04
#define LCD_FUNCTION_SET    0x20
#define LCD_DISPLAY_CONTROL 0x08
#define LCD_CLEAR_DISPLAY   0x01
#define LCD_RETURN_HOME     0x02

*/
// Perform initialisation
int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}
/*
void i2c_write_byte(uint8_t byte) {
    uint8_t data;
    data = byte | LCD_BACKLIGHT;
    i2c_write_blocking(I2C_PORT, LCD_ADDR, &data, 1, false);
}

void i2c_pulse_enable(uint8_t byte) {
    sleep_us(600);
    i2c_write_byte(byte | LCD_ENABLE);
    sleep_us(600);
    i2c_write_byte(byte & ~LCD_ENABLE);
    sleep_us(600);
}

void i2c_lcd_send_nibble(uint8_t byte) {
    i2c_write_byte(byte);
    i2c_pulse_enable(byte);
}

void i2c_lcd_send_byte(uint8_t byte, uint8_t mode) {
    uint8_t high, low;

    high = byte & 0xF0;
    low = (byte << 4) & 0xF0;

    i2c_lcd_send_nibble(high | mode);
    i2c_lcd_send_nibble(low | mode);
}

void i2c_lcd_send_command(uint8_t byte) {
    i2c_lcd_send_byte(byte, LCD_COMMAND);
}

void i2c_lcd_send_char(uint8_t byte) {
    i2c_lcd_send_byte(byte, LCD_CHAR);
}

void i2c_lcd_send_register_select(uint8_t byte) {
    i2c_lcd_send_byte(byte, LCD_REG_SEL);
}

void i2c_lcd_display_on() {
    uint8_t display_control = LCD_DISPLAY_ON;
    i2c_lcd_send_command(LCD_DISPLAY_CONTROL | display_control);
}

void i2c_lcd_init() {
    uint8_t display_mode, display_function, display_control;

    display_mode = LCD_ENTRY_LEFT | LCD_ENTRY_SHIFT_DEC;
    display_function = LCD_MODE_4BIT | LCD_LINE_2 | LCD_DOTS_5x8;
    display_control = LCD_DISPLAY_ON | LCD_CURSOR_ON | LCD_BLINK_ON;

    i2c_lcd_send_command(0x03);
    i2c_lcd_send_command(0x03);
    i2c_lcd_send_command(0x03);
    i2c_lcd_send_command(0x02);
    i2c_lcd_send_command(LCD_ENTRY_MODE_SET | display_mode);
    i2c_lcd_send_command(LCD_FUNCTION_SET | display_function);
    i2c_lcd_send_command(LCD_CLEAR_DISPLAY);
    i2c_lcd_display_on();
    i2c_lcd_send_command(LCD_CLEAR_DISPLAY);
    i2c_lcd_send_command(LCD_RETURN_HOME);
    
}


*/


#define I2C_PORT i2c0
#define I2C_SDA     4
#define I2C_SCL     5

//
// Variables
//

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

// Modes for lcd_send_byte
const int LCD_CHARACTER = 1;
const int LCD_COMMAND = 0;

static int lcd_addr = 0x27;

//
// Functions
//

/* Quick helper function for single byte transfers */
void i2c_write_byte(uint8_t val) {
    i2c_write_blocking(I2C_PORT, lcd_addr, &val, 1, false);
}

void lcd_setAddr(uint8_t addr)
{
    lcd_addr = addr;
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
void lcd_send_byte(uint8_t val, uint8_t mode, uint8_t backlight) {
    uint8_t high;
    uint8_t low;

    if(backlight)
    {
        high = mode | (val & 0xF0) | LCD_BACKLIGHT;
        low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;
    }
    else {
        high = mode | (val & 0xF0);
        low = mode | ((val << 4) & 0xF0);
    }

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void) {
    lcd_send_byte(LCD_CLEARDISPLAY, LCD_COMMAND, 1);
}

// go to location on LCD
void lcd_setCursor(uint8_t line, uint8_t position) {
    uint8_t line_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    uint8_t val = 0x80 + line_offsets[line] + position;
    lcd_send_byte(val, LCD_COMMAND, 1);
}

void lcd_write(char val) {
    lcd_send_byte(val, LCD_CHARACTER, 1);
}

void lcd_print(const char *s) {
    while (*s) {
        lcd_write(*s++);
    }
}

void lcd_createChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x7; // we only have 8 locations 0-7
    lcd_send_byte(LCD_SETCGRAMADDR | (location << 3), LCD_COMMAND, 1);
    for (int i=0; i<8; i++) {
        lcd_send_byte(charmap[i], 1, 0);
    }
}

void lcd_home() {lcd_setCursor(0,0);}

void lcd_init(uint8_t sda, uint8_t scl) {
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);

    // Make the I2C pins available to picotool
    // bi_decl( bi_2pins_with_func(sda, scl, GPIO_FUNC_I2C)); For some reason this produces an error.

    lcd_send_byte(0x03, LCD_COMMAND, 1);
    lcd_send_byte(0x03, LCD_COMMAND, 1);
    lcd_send_byte(0x03, LCD_COMMAND, 1);
    lcd_send_byte(0x02, LCD_COMMAND, 1);

    lcd_send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND, 1);
    lcd_send_byte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND, 1);
    lcd_send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, LCD_COMMAND, 1);
    lcd_clear();
}


int main() {

    stdio_init_all();
    i2c_init(I2C_PORT, 100 * 1000);
    sleep_ms(2000);
    // Configure pins for I2C
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);

    lcd_init(I2C_SDA, I2C_SCL);

    lcd_home(); // or lcd_setCursor(0,0);
    lcd_print("Hello World!");
    while (true) {
        pico_set_led(true);
        sleep_ms(LED_DELAY_MS);
        pico_set_led(false);
        sleep_ms(LED_DELAY_MS);
    }
}
