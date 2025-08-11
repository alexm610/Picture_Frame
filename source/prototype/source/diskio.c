#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "diskio.h"   // FatFs diskio header
#include <stdio.h>

#define SPI_PORT spi0
#define PIN_CS   22
#define PIN_MISO 16
#define PIN_MOSI 19
#define PIN_SCK  18

// SD card commands
#define CMD0   0x40  // GO_IDLE_STATE
#define CMD8   0x48  // SEND_IF_COND
#define CMD17  0x51  // READ_SINGLE_BLOCK
#define CMD55  0x77  // APP_CMD
#define ACMD41 0x69  // SD_SEND_OP_COND (ACMD)

static inline void cs_select()   { gpio_put(PIN_CS, 0); }
static inline void cs_deselect() { gpio_put(PIN_CS, 1); }

static uint8_t spi_transfer(uint8_t data) {
    uint8_t rx;
    spi_write_read_blocking(SPI_PORT, &data, &rx, 1);
    return rx;
}

static void send_clock_train() {
    cs_deselect();
    for (int i=0; i<10; i++) spi_transfer(0xFF);
}

// Send command packet to SD card and get response
static uint8_t sd_send_command(uint8_t cmd, uint32_t arg) {
    cs_deselect();
    spi_transfer(0xFF);
    cs_select();
    spi_transfer(0xFF);

    spi_transfer(cmd);
    spi_transfer((arg >> 24) & 0xFF);
    spi_transfer((arg >> 16) & 0xFF);
    spi_transfer((arg >> 8) & 0xFF);
    spi_transfer(arg & 0xFF);

    uint8_t crc = 0x01;  // default CRC + stop bit
    if (cmd == CMD0) crc = 0x95;  // Valid CRC for CMD0
    if (cmd == CMD8) crc = 0x87;  // Valid CRC for CMD8
    spi_transfer(crc);

    // Wait for response (response[7] == 0)
    for (int i=0; i<8; i++) {
        uint8_t resp = spi_transfer(0xFF);
        if ((resp & 0x80) == 0) return resp;
    }
    return 0xFF; // Timeout
}

DSTATUS disk_initialize(BYTE pdrv) {
    if (pdrv != 0) return STA_NOINIT;

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    cs_deselect();

    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);

    spi_init(SPI_PORT, 400000); // slow init speed

    send_clock_train();

    printf("CMD0...\n");
    if (sd_send_command(CMD0, 0) != 0x01) {
        printf("CMD0 failed\n");
        return STA_NOINIT;
    }

    printf("CMD8...\n");
    uint8_t r = sd_send_command(CMD8, 0x1AA);
    printf("CMD8 response: 0x%02X\n", r);

    if (r == 0x01) {
        // SD v2
        spi_transfer(0xFF); spi_transfer(0xFF); spi_transfer(0xFF); spi_transfer(0xFF);

        int timeout = 1000;
        do {
            sd_send_command(CMD55, 0);
            r = sd_send_command(ACMD41, 0x40000000);
            timeout--;
            sleep_ms(1);
            if (timeout <= 0) {
                printf("ACMD41 timeout\n");
                return STA_NOINIT;
            }
        } while (r != 0);
    } else {
        // Older card
        int timeout = 1000;
        do {
            sd_send_command(CMD55, 0);
            r = sd_send_command(ACMD41, 0);
            timeout--;
            sleep_ms(1);
            if (timeout <= 0) {
                printf("ACMD41 timeout (old card)\n");
                break;
            }
        } while (r != 0);

        if (r != 0) {
            timeout = 1000;
            do {
                r = sd_send_command(CMD8, 0);
                timeout--;
                sleep_ms(1);
                if (timeout <= 0) {
                    printf("CMD1 timeout\n");
                    return STA_NOINIT;
                }
            } while (r != 0);
        }
    }

    cs_deselect();
    spi_transfer(0xFF);

    spi_set_baudrate(SPI_PORT, 4000000); // speed up after init

    printf("SD card initialized successfully\n");
    return 0;
}


DSTATUS disk_status(BYTE pdrv) {
    if (pdrv != 0) return STA_NOINIT;
    return 0;
}

// Wait for data token 0xFE before reading a block
static int wait_for_token() {
    for (int i=0; i<10000; i++) {
        uint8_t token = spi_transfer(0xFF);
        if (token == 0xFE) return 0;
        sleep_us(10);
    }
    return -1;
}

DRESULT disk_read(BYTE pdrv, BYTE* buff, DWORD sector, UINT count) {
    if (pdrv != 0 || count == 0) return RES_PARERR;

    for (UINT i=0; i<count; i++) {
        if (sd_send_command(CMD17, sector + i) != 0x00) return RES_ERROR;
        if (wait_for_token() != 0) return RES_ERROR;

        // Read 512 bytes
        for (int j=0; j<512; j++) {
            buff[j] = spi_transfer(0xFF);
        }
        // Discard CRC
        spi_transfer(0xFF);
        spi_transfer(0xFF);
    }
    return RES_OK;
}

DRESULT disk_write(BYTE pdrv, const BYTE* buff, DWORD sector, UINT count) {
    // Write not implemented
    return RES_OK;
}

DWORD get_fattime(void) {
    // Return a fixed timestamp (e.g., 2023-01-01 00:00:00)
    return ((DWORD)(2023 - 1980) << 25) | (1 << 21) | (1 << 16);
}

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void* buff) {
    // For now, just return success or "not supported"
    if (pdrv != 0) return RES_PARERR;

    switch (cmd) {
        case CTRL_SYNC:
            // If you have nothing special to do to sync, just return OK
            return RES_OK;

        // You can add handling for other commands if you want,
        // or just return RES_PARERR or RES_OK as needed

        default:
            return RES_PARERR;
    }
}
