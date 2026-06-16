#ifndef GPS_MANAGER_H
#define GPS_MANAGER_H

#include <Arduino.h>
#include <TinyGPSPlus.h>
#include <NimBLEDevice.h>

class GpsManager {
public:
    GpsManager();
    
    void begin(uint8_t rxPin, uint8_t txPin, uint32_t baud);
    
    void tick(); 

    bool isConnected();
    uint8_t getSatellites();
    double getLat();
    double getLng();
    double getAltitude();
    double getSpeed();

    // Bluetooth
    bool hasDestination();
    double getDistanceToDest();
    String getDestName();
    
    // Callback do Bluetooth
    void setDestination(double lat, double lng, const String& name);
    String getDistanceString();
    void updateBleDistanceMsg(const String& msg);
    String getDetailedStatus();
    String getSearchTime(); 

private:
    TinyGPSPlus _gps;
    HardwareSerial _gpsSerial;
    
    NimBLECharacteristic* _pCharDist;
    
    double _destLat;
    double _destLng;
    bool _hasDest;
    String _destName;

    unsigned long _lastUpdate;
    unsigned long _searchStartTime;
    
    // Lógica interna de extração da URL
    bool extrairCoordenadas(const String& url, double& lat, double& lng);
};

#endif