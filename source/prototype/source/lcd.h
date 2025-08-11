#ifndef LCD_H_
#define LCD_H_



#define I2C_PORT    i2c0
#define I2C_SDA     4
#define I2C_SCL     5

// Modes for lcd_send_byte
#define LCD_CHARACTER  1
#define LCD_COMMAND    0

#define MAX_LINES       4
#define MAX_CHARS       20
#define MAX_LINE0       8
#define MAX_LINE1       1
#define MAX_LINE2       1
#define MAX_LINE3       4
void i2c_write_byte(uint8_t);
void lcd_toggle_enable(uint8_t);
void lcd_send_byte(uint8_t, int);
void lcd_clear(void);
void lcd_set_cursor(int, int);
static void inline lcd_char(char);
void lcd_string(const char *);
void lcd_init();
void lcd_update();



#endif /* LCD_H_ */