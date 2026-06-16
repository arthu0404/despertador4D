#ifndef CONFIG_H
#define CONFIG_H

// ========== DISPLAY (SSD1306 OLED) ==========
#define DISPLAY_SDA_PIN         8       // SDA
#define DISPLAY_SCL_PIN         9       // SCL
#define DISPLAY_I2C_ADDRESS     0x3C
#define DISPLAY_I2C_FREQ        100000  // 400kHz
#define DISPLAY_WIDTH           128
#define DISPLAY_HEIGHT          64

// ========== ENCODER ========== 
#define ENCODER_CLK_PIN 4
#define ENCODER_DT_PIN  5
#define ENCODER_SW_PIN  6

// ========== GPS (M8N) ==========
#define GPS_RX_PIN              10 
#define GPS_TX_PIN              11
#define GPS_BAUD_RATE           9600

// ========== BLUETOOTH (BLE) ==========
#define BLE_DEVICE_NAME         "Despertador-GPS"
#define BLE_SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define BLE_CHAR_LINK_UUID      "abcdefab-cdef-abcd-efab-cdefabcdefab"
#define BLE_CHAR_DIST_UUID      "abcdefab-cdef-abcd-efab-cdefabcdef00"

// ========== SERIAL/DEBUG ==========
#define SERIAL_BAUD_RATE        115200

// ========== GERAIS ==========
#define FIRMWARE_VERSION        "1.0.0"
#define DEVICE_NAME             "Despertador-4D"

#endif
