#include <Arduino.h>
#include "config.h"
#include "display.h" 
#include "encoder.h"
#include "gps.h"
#include "screen_manager.h"
#include "screens/home_screen.h"
#include "screens/gps_screen.h"

Display myDisplay(DISPLAY_SCL_PIN, DISPLAY_SDA_PIN);
AppEncoder myEncoder(ENCODER_CLK_PIN, ENCODER_DT_PIN, ENCODER_SW_PIN);

ScreenManager screenManager;
HomeScreen homeScreen;
GPSScreen gpsScreen;
GpsManager myGps;

bool isBooting = true;
bool needsRedraw = true;

unsigned long lastMinuteTick = 0;
int simulatedMinutes = 0;
unsigned long lastDisplayRefresh = 0;

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    delay(500); 
    
    myDisplay.begin(DISPLAY_I2C_ADDRESS);
    myEncoder.begin();
    myGps.begin(GPS_RX_PIN, GPS_TX_PIN, GPS_BAUD_RATE);

    myDisplay.showBootScreen();
    delay(2000); 
    isBooting = false;

    screenManager.changeScreen(&homeScreen);
}

void loop() {
    myEncoder.tick();
    myGps.tick();

    if (isBooting) return;

    EncoderAction action = myEncoder.getAction();

    if (action != ENC_NONE) {
        screenManager.handleInput(action);
        needsRedraw = true;
    }

    if (millis() - lastDisplayRefresh >= 1000) {
        lastDisplayRefresh = millis();
        needsRedraw = true;
    }

    if (needsRedraw) {
        screenManager.draw(&myDisplay);
        needsRedraw = false; 
    }

    delay(2);
}