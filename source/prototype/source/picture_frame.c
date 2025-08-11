#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "pico/binary_info.h"
#include "lcd.h"
#include "christmas_time_2023.h"
#include "walk_on_seawall.h"
#include "victoria.h"
#include "ice_cream_seawall.h"
#include "lunch_victoria.h"

#define LED_DELAY_MS    500

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

// SPI and pins (adjust to your wiring)
#define SPI_PORT spi0
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_MISO 16
#define PIN_CS_TFT 17
#define PIN_DC     21
#define PIN_RST    20
#define PIN_CS_SD  22

#define TFT_WIDTH  130
#define TFT_HEIGHT 131
#define X_START    0
#define Y_START    0

// --- Low-level helpers ---
static inline void tft_cs_low()  { gpio_put(PIN_CS_TFT, 0); }
static inline void tft_cs_high() { gpio_put(PIN_CS_TFT, 1); }
static inline void tft_cmd_mode() { gpio_put(PIN_DC, 0); }
static inline void tft_data_mode(){ gpio_put(PIN_DC, 1); }

static void spi_write_byte(uint8_t b) {
    spi_write_blocking(SPI_PORT, &b, 1);
}
static void spi_write_bytes(const uint8_t *buf, size_t len) {
    spi_write_blocking(SPI_PORT, buf, len);
}

static void tft_write_cmd(uint8_t cmd) {
    tft_cmd_mode();
    tft_cs_low();
    spi_write_byte(cmd);
    tft_cs_high();
}

static void tft_write_data(uint8_t d) {
    tft_data_mode();
    tft_cs_low();
    spi_write_byte(d);
    tft_cs_high();
}

static void tft_write_data_buf(const uint8_t *buf, size_t len) {
    tft_data_mode();
    tft_cs_low();
    spi_write_bytes(buf, len);
    tft_cs_high();
}

// --- Address window ---
static void tft_set_addr_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    uint16_t xs = x0 + X_START;
    uint16_t xe = x1 + X_START;
    uint16_t ys = y0 + Y_START;
    uint16_t ye = y1 + Y_START;

    uint8_t buf[4];
    tft_write_cmd(0x2A); // CASET
    buf[0] = xs >> 8; buf[1] = xs & 0xFF; buf[2] = xe >> 8; buf[3] = xe & 0xFF;
    tft_write_data_buf(buf, 4);

    tft_write_cmd(0x2B); // RASET
    buf[0] = ys >> 8; buf[1] = ys & 0xFF; buf[2] = ye >> 8; buf[3] = ye & 0xFF;
    tft_write_data_buf(buf, 4);

    tft_write_cmd(0x2C); // RAMWR
}

// --- Draw single pixel ---
void tft_draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
    if (x >= TFT_WIDTH || y >= TFT_HEIGHT) return;

    tft_set_addr_window(x, y, x, y);

    uint8_t data[2] = { (uint8_t)(color >> 8), (uint8_t)(color & 0xFF) };

    tft_data_mode();
    tft_cs_low();
    spi_write_bytes(data, 2);
    tft_cs_high();
}

// --- Initialization sequence for ST7735 Red Tab ---
static void tft_init(void) {
    // Reset pin cycle
    gpio_put(PIN_RST, 0);
    sleep_ms(50);
    gpio_put(PIN_RST, 1);
    sleep_ms(50);

    tft_write_cmd(0x01); // Software reset
    sleep_ms(150);
    tft_write_cmd(0x11); // Sleep out
    sleep_ms(150);

    // Frame rate etc - condensed standard init sequence
    tft_write_cmd(0xB1); tft_write_data_buf((uint8_t[]){0x01,0x2C,0x2D}, 3);
    tft_write_cmd(0xB2); tft_write_data_buf((uint8_t[]){0x01,0x2C,0x2D}, 3);
    tft_write_cmd(0xB3); tft_write_data_buf((uint8_t[]){0x01,0x2C,0x2D,0x01,0x2C,0x2D}, 6);
    tft_write_cmd(0xB4); tft_write_data(0x07);

    tft_write_cmd(0xC0); tft_write_data_buf((uint8_t[]){0xA2,0x02,0x84}, 3);
    tft_write_cmd(0xC1); tft_write_data(0xC5);
    tft_write_cmd(0xC2); tft_write_data_buf((uint8_t[]){0x0A,0x00}, 2);
    tft_write_cmd(0xC3); tft_write_data_buf((uint8_t[]){0x8A,0x2A}, 2);
    tft_write_cmd(0xC4); tft_write_data_buf((uint8_t[]){0x8A,0xEE}, 2);
    tft_write_cmd(0xC5); tft_write_data(0x0E);

    tft_write_cmd(0x36);
    tft_write_data(0xC8); // rotation + BGR

    tft_write_cmd(0x3A);
    tft_write_data(0x05); // 16-bit color mode

    // Set column address
    tft_write_cmd(0x2A);
    tft_write_data_buf((uint8_t[]){0x00, X_START, 0x00, X_START + TFT_WIDTH - 1}, 4);

    // Set row address
    tft_write_cmd(0x2B);
    tft_write_data_buf((uint8_t[]){0x00, Y_START, 0x00, Y_START + TFT_HEIGHT - 1}, 4);

    tft_write_cmd(0x13); // Normal display mode

    tft_write_cmd(0x29); // Display ON
    sleep_ms(100);
}

// --- BMP parser and display ---
// Only supports 24-bit uncompressed BMP
#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

void draw_bmp_from_memory(const uint8_t *bmp_data, size_t bmp_len) {
    if (bmp_len < sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)) return;

    const BITMAPFILEHEADER *file_header = (const BITMAPFILEHEADER*)bmp_data;
    const BITMAPINFOHEADER *info_header = (const BITMAPINFOHEADER*)(bmp_data + sizeof(BITMAPFILEHEADER));

    if (file_header->bfType != 0x4D42) return; // 'BM'

    if (info_header->biBitCount != 24 || info_header->biCompression != 0) {
        // Only 24-bit uncompressed BMP supported
        return;
    }

    int width = info_header->biWidth;
    int height = info_header->biHeight;
    int row_size = ((width * 3 + 3) & ~3); // Row size padded to 4 bytes
    const uint8_t *pixel_array = bmp_data + file_header->bfOffBits;

    // BMP rows stored bottom-up
    for (int y = height - 1; y >= 0; y--) {
        const uint8_t *row = pixel_array + y * row_size;
        for (int x = 0; x < width; x++) {
            uint8_t b = row[x * 3 + 0];
            uint8_t g = row[x * 3 + 1];
            uint8_t r = row[x * 3 + 2];

            // Convert 24-bit RGB888 to 16-bit RGB565
            uint16_t color = ((r & 0xF8) << 8) |
                             ((g & 0xFC) << 3) |
                             (b >> 3);

            // Clip if image larger than display
            if ((uint16_t)x < TFT_WIDTH && (uint16_t)(height - 1 - y) < TFT_HEIGHT) {
                tft_draw_pixel(x, height - 1 - y, color);
            }
        }
    }
}

int main() {
    stdio_init_all();

    // Init SPI
    spi_init(SPI_PORT, 4 * 1000 * 1000);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);

    // Init control pins
    gpio_init(PIN_CS_TFT);
    gpio_set_dir(PIN_CS_TFT, GPIO_OUT);
    gpio_put(PIN_CS_TFT, 1);

    gpio_init(PIN_DC);
    gpio_set_dir(PIN_DC, GPIO_OUT);
    gpio_put(PIN_DC, 1);

    gpio_init(PIN_RST);
    gpio_set_dir(PIN_RST, GPIO_OUT);
    gpio_put(PIN_RST, 1);

    tft_init();

    //draw_bmp_from_memory(out_bmp, out_bmp_len);
    
    i2c_init(I2C_PORT, 100 * 1000);
 

    // Configure pins for I2C
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // initialize blinky
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);

     // Make the I2C pins available to picotool
    bi_decl( bi_2pins_with_func(4, 5, GPIO_FUNC_I2C));

    lcd_init();
    bool led = true;
    int i = 0;
    int image_counter = 0;
    while (true) {
        //pico_set_led(led);
        if (i % 2) {
            pico_set_led(true);
        } else {
            pico_set_led(false);
        }
        lcd_update();
        
        if (i % 3 == 0) {
            switch (image_counter)
            {
            case 0:
                draw_bmp_from_memory(christmas_time_2023_bmp, christmas_time_2023_bmp_len);
                image_counter = 1;
                break;
            case 1: 
                draw_bmp_from_memory(walk_on_seawall_bmp, walk_on_seawall_bmp_len);
                image_counter = 2;
                break; 
            case 2:
                draw_bmp_from_memory(lunch_victoria_bmp, lunch_victoria_bmp_len);
                image_counter = 3;
                break;
            case 3: 
                draw_bmp_from_memory(ice_cream_seawall_bmp, ice_cream_seawall_bmp_len);
                image_counter = 0;
                break;
            default:
                break;
            }
        }

        sleep_ms(1000);
        i++;
    }
}

