#include "gps.h"

GpsManager::GpsManager() : _gpsSerial(2) {
    _hasDest = false;
    _destLat = 0.0;
    _destLng = 0.0;
    _destName = "Nenhum";
    _lastUpdate = 0;
    _pCharDist = nullptr;
    _searchStartTime = millis();
}

void GpsManager::begin(uint8_t rxPin, uint8_t txPin, uint32_t baud) {
    _gpsSerial.begin(baud, SERIAL_8N1, rxPin, txPin);
}

void GpsManager::tick() {
    int maxBytes = 50;
    
    while (_gpsSerial.available() && maxBytes > 0) {
        char c = _gpsSerial.read();
        _gps.encode(c);
        maxBytes--;
    }
    
    if (isConnected()) {
        _searchStartTime = millis();
    }
}

bool GpsManager::isConnected() {
    // Consideramos conectado se houver comunicação válida e pelo menos 1 satélite
    return _gps.satellites.isValid() && _gps.satellites.value() > 0;
}

uint8_t GpsManager::getSatellites() {
    return _gps.satellites.isValid() ? _gps.satellites.value() : 0;
}

double GpsManager::getLat() {
    return _gps.location.isValid() ? _gps.location.lat() : 0.0;
}

double GpsManager::getLng() {
    return _gps.location.isValid() ? _gps.location.lng() : 0.0;
}

double GpsManager::getAltitude() {
    return _gps.altitude.isValid() ? _gps.altitude.meters() : 0.0;
}

double GpsManager::getSpeed() {
    return _gps.speed.isValid() ? _gps.speed.kmph() : 0.0;
}

bool GpsManager::hasDestination() {
    return _hasDest;
}

double GpsManager::getDistanceToDest() {
    if (!_hasDest || !_gps.location.isValid()) return 0.0;
    
    // calcula a distância em metros
    return TinyGPSPlus::distanceBetween(
        _gps.location.lat(),
        _gps.location.lng(),
        _destLat,
        _destLng
    );
}

String GpsManager::getDestName() {
    return _destName;
}

void GpsManager::setDestination(double lat, double lng, const String& name) {
    _destLat = lat;
    _destLng = lng;
    _hasDest = true;
    _destName = name;
}

String GpsManager::getDistanceString() {
    if (!_hasDest) return "Sem destino";
    if (!isConnected()) return "Sem sinal GPS";
    
    double dist = getDistanceToDest();
    char buf[32];
    if (dist < 1000.0) {
        snprintf(buf, sizeof(buf), "%.1f m", dist);
    } else {
        snprintf(buf, sizeof(buf), "%.2f km", dist / 1000.0);
    }
    return String(buf);
}

void GpsManager::updateBleDistanceMsg(const String& msg) {
    // Bluetooth removido por enquanto
}

bool GpsManager::extrairCoordenadas(const String& url, double& lat, double& lng) {
    return false;
}

String GpsManager::getDetailedStatus() {
    if (_gps.charsProcessed() == 0) {
        return "ERRO HW";
    }
    
    if (!isConnected()) {
        return "BUSCANDO"; 
    }
    
    return "ONLINE";
}

String GpsManager::getSearchTime() {
    if (isConnected() || _gps.charsProcessed() == 0) return "";
    
    unsigned long elapsed = (millis() - _searchStartTime) / 1000;
    unsigned int m = elapsed / 60;
    unsigned int s = elapsed % 60;
    
    char buf[16];
    snprintf(buf, sizeof(buf), "%02d:%02d", m, s);
    return String(buf);
}

    